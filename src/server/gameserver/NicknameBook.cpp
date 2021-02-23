#include "NicknameBook.h"
#include "NicknameInfo.h"
#include "PlayerCreature.h"
#include "Gpackets/GCNicknameList.h"
#include "DB.h"
#include "LevelNickInfoManager.h"
#include "Guild.h"
#include "GuildManager.h"

#define CUSTOM_NICKNAME_ID 0
#define LEVEL_NICKNAME_BASE_ID 1
#define GUILD_MASTER_NICKNAME_ID 11

string getDBString(const string& str);

void NicknameBook::load() throw(Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	m_NextNicknameID = 10000;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery("SELECT nID, NickType, Nickname, NickIndex FROM NicknameBook WHERE OwnerID='%s'",
				m_pOwner->getName().c_str());

		while ( pResult->next() )
		{
			WORD nID = pResult->getInt(1);
			BYTE nType = pResult->getInt(2);

			if ( nType != NicknameInfo::NICK_NONE )
			{
				NicknameInfo* pNickname = new NicknameInfo;
				pNickname->setNicknameID( nID );
				pNickname->setNicknameType( nType );
				pNickname->setNickname( pResult->getString(3) );
				pNickname->setNicknameIndex( pResult->getInt(4) );

				setNicknameInfo(nID, pNickname);
				if ( nID >= m_NextNicknameID ) m_NextNicknameID = nID + 1;

				if ( nType == NicknameInfo::NICK_FORCED || nType == NicknameInfo::NICK_CUSTOM_FORCED )
				{
					m_pOwner->setNickname( pNickname );
				}
			}
		}

		if ( getNicknameInfo(CUSTOM_NICKNAME_ID) == NULL )
		{
			NicknameInfo* pLevelNickname = new NicknameInfo;
			pLevelNickname->setNicknameID( CUSTOM_NICKNAME_ID );
			pLevelNickname->setNicknameType( NicknameInfo::NICK_CUSTOM );
			pLevelNickname->setNickname( " " );
			setNicknameInfo( CUSTOM_NICKNAME_ID, pLevelNickname );

			pStmt->executeQuery( "INSERT IGNORE INTO NicknameBook (nID, OwnerID, NickType, Nickname, NickIndex, Time) VALUES "
					"(0, '%s', %u, ' ', 0, now())", m_pOwner->getName().c_str(), NicknameInfo::NICK_CUSTOM );
		}

		SAFE_DELETE( pStmt );
	}
	END_DB( pStmt )

/*	if ( m_pOwner->getLevel() >= 10 )
	{
		Level_t level = m_pOwner->getLevel();
		if ( level > 150 ) level=150;
		NicknameInfo* pLevelNickname = new NicknameInfo;
		pLevelNickname->setNicknameID( 1 );
		pLevelNickname->setNicknameType( NicknameInfo::NICK_BUILT_IN );
		pLevelNickname->setNicknameIndex( level/10 );
		setNicknameInfo( 1, pLevelNickname );

		cout << "닉네임 번호 : " << level/10 << endl;
	}*/
	
	if ( m_pOwner->getLevel() >= 10 )
	{
		Level_t level = m_pOwner->getLevel();
		vector<LevelNickInfo*>& infos = LevelNickInfoManager::Instance().getLevelNickInfo( level );
		vector<LevelNickInfo*>::iterator itr = infos.begin();
		vector<LevelNickInfo*>::iterator endItr = infos.end();
		int nid = LEVEL_NICKNAME_BASE_ID;

		for ( ; itr != endItr ; ++itr )
		{
			if ( !(*itr)->isFitRace(m_pOwner) ) continue;

			NicknameInfo* pLevelNickname = new NicknameInfo;
			pLevelNickname->setNicknameID( nid );
			pLevelNickname->setNicknameType( NicknameInfo::NICK_BUILT_IN );
			pLevelNickname->setNicknameIndex( (*itr)->getNickIndex() );
			setNicknameInfo( nid++, pLevelNickname );
		}
	}

	if ( m_pOwner->getGuildID() != m_pOwner->getCommonGuildID() )
	{
		// 길드를 가져온다.
		Guild* pGuild = g_pGuildManager->getGuild( m_pOwner->getGuildID() );

		// 플레이어가 길드의 마스터인지를 확인한다.
		if ( pGuild != NULL && pGuild->getMaster() == m_pOwner->getName() )
		{
			NicknameInfo* pLevelNickname = new NicknameInfo;
			pLevelNickname->setNicknameID( GUILD_MASTER_NICKNAME_ID );
			pLevelNickname->setNicknameType( NicknameInfo::NICK_BUILT_IN );
			pLevelNickname->setNicknameIndex( 47 );
			setNicknameInfo( GUILD_MASTER_NICKNAME_ID, pLevelNickname );
		}
	}

	__END_CATCH
}

Packet* NicknameBook::getNicknameBookListPacket() const
{
	GCNicknameList* pPacket = new GCNicknameList;

	vector<NicknameInfo*>& nickList = pPacket->getNicknames();

	hash_map<WORD, NicknameInfo*>::const_iterator itr = m_Nicknames.begin();
	hash_map<WORD, NicknameInfo*>::const_iterator endItr = m_Nicknames.end();

	for ( ; itr != endItr ; ++itr )
	{
		if ( itr->second != NULL ) nickList.push_back( itr->second );
	}

	return pPacket;
}

void NicknameBook::addNewNickname(const string& nick)
	throw(Error)
{
	__BEGIN_TRY

	NicknameInfo* pNickname = new NicknameInfo;
	pNickname->setNicknameID( popNicknameID() );
	pNickname->setNicknameType( NicknameInfo::NICK_CUSTOM );
	pNickname->setNickname( nick );

	setNicknameInfo( pNickname->getNicknameID(), pNickname );

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("INSERT INTO NicknameBook (nID, OwnerID, NickType, Nickname, Time) "
				"VALUES (%u, '%s', %u, '%s', now())",
				pNickname->getNicknameID(), m_pOwner->getName().c_str(), pNickname->getNicknameType(), getDBString(pNickname->getNickname()).c_str() );
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}
