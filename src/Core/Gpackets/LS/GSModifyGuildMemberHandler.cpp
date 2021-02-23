//----------------------------------------------------------------------
//
// Filename    : GSModifyGuildMemberHandler.cpp
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

// include files
#include "GSModifyGuildMember.h"
#include "Assert.h"

#ifdef __SHARED_SERVER__
	
	#include "Guild.h"
	#include "GuildManager.h"
	#include "GameServerManager.h"
	#include "Properties.h"
	#include "DB.h"
	#include "StringPool.h"

	#include <stdio.h>

	#include "Spackets/SGModifyGuildMemberOK.h"

#endif

//----------------------------------------------------------------------
// 
// GSModifyGuildMemberHandler::execute()
// 
//----------------------------------------------------------------------
void GSModifyGuildMemberHandler::execute ( GSModifyGuildMember* pPacket, Player* pPlayer )
	 throw ( ProtocolException , Error )
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __SHARED_SERVER__
	//cout << "GSModifyGuildMember received" << endl;

	Assert( pPacket != NULL );

	// 길드를 가져온다.
	Guild* pGuild = g_pGuildManager->getGuild( pPacket->getGuildID() );
	//try { Assert( pGuild != NULL ); } catch ( Throwable& ) { return; }
	if (pGuild==NULL) return;

	// 길드의 멤버인지 확인한다.
	GuildMember* pGuildMember = pGuild->getMember( pPacket->getName() );
	//try { Assert( pGuildMember != NULL ); } catch ( Throwable& ) { return; }
	if (pGuildMember==NULL) return;

	// 보낸사람이 길드 마스터인지 확인한다. ( 길드 마스터를 바꿀때는 예외 )
	if ( pGuild->getMaster() != pPacket->getSender() 
		&& pPacket->getGuildMemberRank() != GuildMember::GUILDMEMBER_RANK_MASTER )
		return;

	if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_WAIT &&
		 pPacket->getGuildMemberRank() == GuildMember::GUILDMEMBER_RANK_NORMAL )
	{
		///////////////////////////////////////////////////////////////////////////////////////
		// 길드 멤버 가입을 승인한 경우, DB에 Slayer, Vampire, Ousters 테이블의 GuildID 를 바꾼다.
		///////////////////////////////////////////////////////////////////////////////////////
		Statement* pStmt = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
			
			if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
			{
				pStmt->executeQuery( "UPDATE Slayer SET GuildID = %d WHERE Name = '%s'", pGuild->getID(), pGuildMember->getName().c_str() );
				pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_TEAM_JOIN_ACCEPT ) );
			}
			else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
			{
				pStmt->executeQuery( "UPDATE Vampire SET GuildID = %d WHERE Name = '%s'", pGuild->getID(), pGuildMember->getName().c_str() );
				pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_CLAN_JOIN_ACCEPT ) );
			}
			else if ( pGuild->getRace() == Guild::GUILD_RACE_OUSTERS )
			{
				pStmt->executeQuery( "UPDATE Ousters SET GuildID = %d WHERE Name = '%s'", pGuild->getID(), pGuildMember->getName().c_str() );
				pStmt->executeQuery( "INSERT INTO Messages ( Receiver, Message ) VALUES ( '%s', '%s' )", pGuildMember->getName().c_str(), g_pStringPool->c_str( STRID_CLAN_JOIN_ACCEPT ) );
			}

			SAFE_DELETE( pStmt );
		}
		END_DB(pStmt)

		// Guild Member 정보를 변경한다.
		pGuild->modifyMemberRank( pGuildMember->getName(), pPacket->getGuildMemberRank() );
	}
	else if ( pGuildMember->getRank() != GuildMember::GUILDMEMBER_RANK_MASTER
			&& pPacket->getGuildMemberRank() == GuildMember::GUILDMEMBER_RANK_MASTER )
	{
		// 길드마스터의 랭크를 새로 길드마스터가 되는 멤버의 원래 랭크로 바꿔준다.
		pGuild->modifyMemberRank( pGuild->getMaster(), pGuildMember->getRank() );
		// 새 길드마스터의 랭크를 세팅한다.
		pGuild->modifyMemberRank( pGuildMember->getName(), pPacket->getGuildMemberRank() );
		// 길드 오브젝트에 새 길드 마스트로 세팅한다.
		pGuild->setMaster( pGuildMember->getName() );

		// DB에 저장한다.
		char field[30];
		sprintf( field, "Master='%s'", pGuildMember->getName().c_str() );
		pGuild->tinysave( field );
	}
	else if ( pGuildMember->getRank() == GuildMember::GUILDMEMBER_RANK_NORMAL
			&& pPacket->getGuildMemberRank() == GuildMember::GUILDMEMBER_RANK_SUBMASTER )
	{
		// 새 부길드마스터의 랭크를 세팅한다.
		pGuild->modifyMemberRank( pGuildMember->getName(), pPacket->getGuildMemberRank() );
	}
	else
	{
		return;
	}

	// 게임 서버로 보낼 패킷을 만든다.
	SGModifyGuildMemberOK sgModifyGuildMemberOK;
	sgModifyGuildMemberOK.setGuildID( pGuild->getID() );
	sgModifyGuildMemberOK.setName( pPacket->getName() );
	sgModifyGuildMemberOK.setGuildMemberRank( pGuildMember->getRank() );
	sgModifyGuildMemberOK.setSender( pPacket->getSender() );

	// 게임 서버로 패킷을 보낸다.
	g_pGameServerManager->broadcast( &sgModifyGuildMemberOK );

#endif
		
	__END_DEBUG_EX __END_CATCH
}
