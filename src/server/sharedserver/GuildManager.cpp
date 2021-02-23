////////////////////////////////////////////////////////////////////////
// Filename    : GuildManager.cpp
// Written By  : 김성민
// Description : 
////////////////////////////////////////////////////////////////////////

#include "Guild.h"
#include "GuildManager.h"
#include "StringStream.h"
#include "DB.h"
#include "Properties.h"

#ifdef __GAME_SERVER__
	#include "Zone.h"
	#include "ZoneInfoManager.h"
	#include "ZoneGroupManager.h"
	#include "PlayerCreature.h"
	#include "CastleInfoManager.h"
	#include "ZoneUtil.h"
	#include "war/WarScheduler.h"
	#include "GuildUnion.h"
#endif
#ifdef __SHARED_SERVER__
	#include "Spackets/SGGuildInfo.h"
	#include "Spackets/SGExpelGuildMemberOK.h"
	#include "GameServerManager.h"
#endif

#include "Gpackets/GCWaitGuildList.h"
#include "Gpackets/GCActiveGuildList.h"

////////////////////////////////////////////////////////////////////////
// global varible initialization
////////////////////////////////////////////////////////////////////////

GuildManager* g_pGuildManager = NULL;


////////////////////////////////////////////////////////////////////////
// class GuildManager member methods
////////////////////////////////////////////////////////////////////////

GuildManager::GuildManager()
	throw()
{
	__BEGIN_TRY

	m_Mutex.setName( "GuildManager" );

	__END_CATCH
}

GuildManager::~GuildManager()
	throw()
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION( m_Mutex )

	// 모든 길드 객체들을 메모리에서 삭제한다.
	hash_map<GuildID_t, Guild*>::iterator itr = m_Guilds.begin();
	for (; itr != m_Guilds.end(); itr++)
	{
		Guild* pGuild = itr->second;
		SAFE_DELETE(pGuild);
	}

	m_Guilds.clear();

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH
}


void GuildManager::init()
	throw()
{
#ifdef __SHARED_SERVER__

	__BEGIN_TRY

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	__ENTER_CRITICAL_SECTION( m_Mutex )

	BEGIN_DB
	{
		// 길드 ID는 최대값을 정해놓고, 새로운 길드가 생기면 최대값에다
		// 1을 더해서 할당하는 방식으로 운영된다. 그러므로 길드 매니저가
		// 초기화될 때, 현재 존재하는 길드 ID의 최대값을 읽어들여둔다.

		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT COUNT(*) FROM GuildInfo");

		// 테이블에 데이타가 하나도 없다면, 일단 맥스 아이디는 1로 세팅해준다.
		pResult->next();

		if (pResult->getInt(1) == 0)
		{
			Guild::setMaxGuildID( g_pConfig->getPropertyInt("Dimension") * 10000 + g_pConfig->getPropertyInt("WorldID") * 3000 + 100 );
		}
		else
		{
			// get & set MaxGuildID
			pResult = pStmt->executeQuery("SELECT MAX(GuildID) FROM GuildInfo");
			pResult->next();
			Guild::setMaxGuildID( pResult->getInt(1) );
		}

		pResult = pStmt->executeQuery( "SELECT COUNT(*) FROM GuildInfo WHERE GuildRace = %d", Guild::GUILD_RACE_SLAYER );
		pResult->next();

		if ( pResult->getInt(1) == 0 )
		{
			Guild::setMaxSlayerZoneID( Guild::getMaxSlayerZoneID() + 1 );
		}
		else
		{
			// get & set MaxSlayerZoneID
			pResult = pStmt->executeQuery( "SELECT MAX(GuildZoneID) FROM GuildInfo WHERE GuildRace = %d", Guild::GUILD_RACE_SLAYER );
			pResult->next();
			Guild::setMaxSlayerZoneID( max( pResult->getInt(1), Guild::getMaxSlayerZoneID() + 1 ) );
		}

		pResult = pStmt->executeQuery( "SELECT COUNT(*) FROM GuildInfo WHERE GuildRace = %d", Guild::GUILD_RACE_VAMPIRE );
		pResult->next();

		if ( pResult->getInt(1) == 0 )
		{
			Guild::setMaxVampireZoneID( Guild::getMaxVampireZoneID() + 1 );
		}
		else
		{
			// get & set MaxVampireZoneID
			pResult = pStmt->executeQuery( "SELECT MAX(GuildZoneID) FROM GuildInfo WHERE GuildRace = %d", Guild::GUILD_RACE_VAMPIRE );
			pResult->next();
			Guild::setMaxVampireZoneID( max( pResult->getInt(1), Guild::getMaxVampireZoneID() + 1 ) );
		}

		pResult = pStmt->executeQuery( "SELECT COUNT(*) FROM GuildInfo WHERE GuildRace = %d", Guild::GUILD_RACE_OUSTERS );
		pResult->next();

		if ( pResult->getInt(1) == 0 )
		{
			Guild::setMaxOustersZoneID( Guild::getMaxOustersZoneID() + 1 );
		}
		else
		{
			// get & set MaxOustersZoneID
			pResult = pStmt->executeQuery( "SELECT MAX(GuildZoneID) FROM GuildInfo WHERE GuildRace = %d", Guild::GUILD_RACE_OUSTERS );
			pResult->next();
			Guild::setMaxOustersZoneID( max( pResult->getInt(1), Guild::getMaxOustersZoneID() + 1 ) );
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	load();

	__END_CATCH

#endif
}


void GuildManager::load()
	throw()
{
	__BEGIN_TRY

	Statement*	pStmt	= NULL;
	Result*		pResult	= NULL;

	__ENTER_CRITICAL_SECTION( m_Mutex )

	BEGIN_DB
	{
		// 길드 정보를 DB로 부터 읽어온다.
		pStmt	= g_pDatabaseManager->getConnection( "DARKEDEN" )->createStatement();
		pResult	= pStmt->executeQuery( "SELECT GuildID, GuildName, GuildType, GuildRace, GuildState, ServerGroupID, GuildZoneID, Master, Date, Intro FROM GuildInfo WHERE GuildState IN ( %d, %d )",
										Guild::GUILD_STATE_WAIT, Guild::GUILD_STATE_ACTIVE );

		while ( pResult->next() )
		{
			GuildState_t state = pResult->getInt(5);

			// 현재 월드의 등록 대기중인 길드와 활동 중인 길드만 추가한다.
			if ( state == Guild::GUILD_STATE_WAIT || state == Guild::GUILD_STATE_ACTIVE )
			{
				Guild* pGuild = new Guild();

				pGuild->setID( pResult->getInt(1) );
				pGuild->setName( pResult->getString(2) );
				pGuild->setType( pResult->getInt(3) );
				pGuild->setRace( pResult->getInt(4) );
				pGuild->setState( state );
				pGuild->setServerGroupID( pResult->getInt(6) );
				pGuild->setZoneID( pResult->getInt(7) );
				pGuild->setMaster( pResult->getString(8) );
				pGuild->setDate( pResult->getString(9) );
				pGuild->setIntro( pResult->getString(10) );

				addGuild_NOBLOCKED( pGuild );
/*
#ifdef __GAME_SERVER__
				// 길드가 Active 이고 이 게임 서버에 아지트가 존재한다면 아지트 Zone을 만든다.
				if ( pGuild->getServerGroupID() == g_pConfig->getPropertyInt("ServerID") && state == Guild::GUILD_STATE_ACTIVE )
				{
					//////////////
					// Zone Info
					//////////////
					ZoneInfo* pZoneInfo = new ZoneInfo();
					pZoneInfo->setZoneID( pGuild->getZoneID() );
					pZoneInfo->setZoneGroupID( 6 );
					pZoneInfo->setZoneType( "NPC_SHOP" );
					pZoneInfo->setZoneLevel( 0 );
					pZoneInfo->setZoneAccessMode( "PUBLIC" );
					pZoneInfo->setZoneOwnerID( "" );
					pZoneInfo->setPayPlay( "" );
					if ( pGuild->getRace() == Guild::GUILD_RACE_SLAYER )
					{
						pZoneInfo->setSMPFilename( "team_hdqrs.smp" );
						pZoneInfo->setSSIFilename( "team_hdqrs.ssi" );
						string Name = "team - " + pGuild->getName();
						pZoneInfo->setFullName( Name );
						pZoneInfo->setShortName( Name );
					}
					else if ( pGuild->getRace() == Guild::GUILD_RACE_VAMPIRE )
					{
						pZoneInfo->setSMPFilename( "clan_hdqrs.smp" );
						pZoneInfo->setSSIFilename( "clan_hdqrs.ssi" );
						string Name = "clan - " + pGuild->getName();
						pZoneInfo->setFullName( Name );
						pZoneInfo->setShortName( Name );
					}

					g_pZoneInfoManager->addZoneInfo( pZoneInfo );

					/////////
					// Zone
					/////////
					Zone* pZone = new Zone( pGuild->getZoneID() );
					Assert( pZone != NULL );

					ZoneGroup* pZoneGroup = g_pZoneGroupManager->getZoneGroup(6);
					Assert( pZoneGroup != NULL );

					pZone->setZoneGroup( pZoneGroup );
					pZoneGroup->addZone( pZone );
					pZone->init();
				}
#endif
*/
			}
		}

		// 길드 멤버 정보를 DB로 부터 읽어온다.
		pResult = pStmt->executeQuery( "SELECT GuildID, Name, Rank, RequestDateTime, LogOn FROM GuildMember WHERE Rank IN ( 0, 1, 2, 3 )" );

		while ( pResult->next() )
		{
			GuildMember* pMember = new GuildMember();

			pMember->setGuildID( pResult->getInt(1) );
			pMember->setName( pResult->getString(2) );
			pMember->setRank( pResult->getInt(3) );

			if ( pMember->getRank() == GuildMember::GUILDMEMBER_RANK_WAIT )
				pMember->setRequestDateTime( pResult->getString(4) );

			pMember->setLogOn( pResult->getInt(5) );

			Guild* pGuild = getGuild_NOBLOCKED( pMember->getGuildID() );

			if ( pGuild != NULL )
				pGuild->addMember( pMember );
		}

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH
}


void GuildManager::addGuild(Guild* pGuild)
	throw (DuplicatedException)
{
	__BEGIN_TRY

	Assert(pGuild != NULL);

	__ENTER_CRITICAL_SECTION( m_Mutex )

	hash_map<GuildID_t, Guild*>::iterator itr = m_Guilds.find(pGuild->getID());
	if (itr != m_Guilds.end()) throw DuplicatedException();
	m_Guilds[pGuild->getID()] = pGuild;

	__LEAVE_CRITICAL_SECTION( m_Mutex )
	
	__END_CATCH
}


void GuildManager::addGuild_NOBLOCKED(Guild* pGuild)
	throw (DuplicatedException)
{
	__BEGIN_TRY

	Assert(pGuild != NULL);

	hash_map<GuildID_t, Guild*>::iterator itr = m_Guilds.find(pGuild->getID());
	if (itr != m_Guilds.end()) throw DuplicatedException();
	m_Guilds[pGuild->getID()] = pGuild;

	__END_CATCH
}


void GuildManager::deleteGuild(GuildID_t id)
	throw (NoSuchElementException)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION( m_Mutex )

	hash_map<GuildID_t, Guild*>::iterator itr = m_Guilds.find(id);
	if (itr == m_Guilds.end()) throw NoSuchElementException();

#ifdef __GAME_SERVER__

	list<CastleInfo*> pGuildCastleInfoList = g_pCastleInfoManager->getGuildCastleInfos( id );

	if ( !pGuildCastleInfoList.empty() )
	{
		// 성을 갖고 있는 길드다.. 공용성으로 바꿔줘야 된다.
		list<CastleInfo*>::iterator itr = pGuildCastleInfoList.begin();
		for ( ; itr != pGuildCastleInfoList.end() ; itr++ )
		{
			if ( (*itr)->getRace() == RACE_SLAYER )
				g_pCastleInfoManager->modifyCastleOwner( (*itr)->getZoneID(), RACE_SLAYER, 99 );
			else if ( (*itr)->getRace() == RACE_VAMPIRE )
				g_pCastleInfoManager->modifyCastleOwner( (*itr)->getZoneID(), RACE_VAMPIRE, 0 );
			else
				g_pCastleInfoManager->modifyCastleOwner( (*itr)->getZoneID(), RACE_OUSTERS, 66 );
		}
	}

	{
		const hash_map<ZoneID_t, CastleInfo*>& castleInfos = g_pCastleInfoManager->getCastleInfos();

		hash_map<ZoneID_t, CastleInfo*>::const_iterator itr = castleInfos.begin();
		hash_map<ZoneID_t, CastleInfo*>::const_iterator endItr = castleInfos.end();

		for ( ; itr != endItr ; ++itr )
		{
			Zone* pZone = getZoneByZoneID( itr->first );
			if ( pZone != NULL )
			{
				WarScheduler* pWarScheduler = pZone->getWarScheduler();
				if ( pWarScheduler != NULL && pWarScheduler->hasSchedule( id ) )
				{
					pWarScheduler->load();
				}
			}
		}
	}

	// GuildUnion 정보를 지워준다
/*	{

		// UnionManager->deleteGuild(xx);
		GuildUnionManager::Instance().removeMasterGuild(id);
	}
*/
#endif

	m_Guilds.erase(itr);

#ifdef __SHARED_SERVER__
	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		// DB에서 GuildInfo를 지운다.
		pStmt->executeQuery("DELETE FROM GuildInfo WHERE GuildID=%d", id);

		// GuildMember를 다 지운다.
		pStmt->executeQuery("DELETE FROM GuildMember WHERE GuildID=%d", id);

		// GuildUnionMember 에서 길드를 지운다
		pStmt->executeQuery( "DELETE FROM GuildUnionMember WHERE OwnerGuildID=%d", id );
		
		pStmt->executeQuery("UPDATE WarScheduleInfo SET Status='CANCEL' WHERE AttackGuildID=%d", id);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
#endif

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH
}


Guild* GuildManager::getGuild(GuildID_t id)
	throw ()
{
	__BEGIN_TRY

	// 리턴 할 길드 포인터
	Guild* pGuild;

	__ENTER_CRITICAL_SECTION( m_Mutex )

	hash_map<GuildID_t, Guild*>::iterator itr = m_Guilds.find(id);

	if (itr == m_Guilds.end())
	{
		m_Mutex.unlock();

		return NULL;
	}

	pGuild = itr->second;

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	return pGuild;

	__END_CATCH
}
	

Guild* GuildManager::getGuild_NOBLOCKED(GuildID_t id)
	throw ()
{
	__BEGIN_TRY

	// 리턴 할 길드 포인터
	Guild* pGuild;

	hash_map<GuildID_t, Guild*>::iterator itr = m_Guilds.find(id);

	if (itr == m_Guilds.end())
	{
		return NULL;
	}

	pGuild = itr->second;

	return pGuild;

	__END_CATCH
}


void GuildManager::clear()
	throw()
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION( m_Mutex )

	HashMapGuildItor itr = m_Guilds.begin();
	for ( ; itr != m_Guilds.end(); itr++ )
	{
		SAFE_DELETE( itr->second );
	}

	m_Guilds.clear();

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH
}

void GuildManager::clear_NOBLOCKED()
{
	__BEGIN_TRY

	HashMapGuildItor itr = m_Guilds.begin();
	for ( ; itr != m_Guilds.end(); itr++ )
	{
		SAFE_DELETE( itr->second );
	}

	m_Guilds.clear();

	__END_CATCH
}

#ifdef __SHARED_SERVER__
void GuildManager::makeSGGuildInfo( SGGuildInfo& sgGuildInfo )
	throw()
{
	__BEGIN_TRY
	
	__ENTER_CRITICAL_SECTION( m_Mutex )

	HashMapGuildConstItor itr = m_Guilds.begin();
	for ( ; itr != m_Guilds.end(); itr++ )
	{
		GuildInfo2* pGuildInfo = new GuildInfo2();
		itr->second->makeInfo( pGuildInfo );
		sgGuildInfo.addGuildInfo( pGuildInfo );
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )
	
	__END_CATCH
}
#endif

void GuildManager::makeWaitGuildList( GCWaitGuildList& gcWaitGuildList, GuildRace_t race )
	throw()
{
	__BEGIN_TRY
	
	__ENTER_CRITICAL_SECTION( m_Mutex )

	HashMapGuildConstItor itr = m_Guilds.begin();
	for ( ; itr != m_Guilds.end(); itr++ )
	{
		Guild* pGuild = itr->second;
		if ( pGuild->getState() == Guild::GUILD_STATE_WAIT && pGuild->getRace() == race )
		{
			GuildInfo* pGuildInfo = new GuildInfo();
			pGuild->makeInfo( pGuildInfo );

			gcWaitGuildList.addGuildInfo( pGuildInfo );
		}
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH

}

void GuildManager::makeActiveGuildList( GCActiveGuildList& gcActiveGuildList, GuildRace_t race )
	throw()
{
	__BEGIN_TRY
	
	__ENTER_CRITICAL_SECTION( m_Mutex )

	HashMapGuildConstItor itr = m_Guilds.begin();
	for ( ; itr != m_Guilds.end(); itr++ )
	{
		Guild* pGuild = itr->second;
		if ( pGuild->getState() == Guild::GUILD_STATE_ACTIVE && pGuild->getRace() == race )
		{
			GuildInfo* pGuildInfo = new GuildInfo();
			pGuild->makeInfo( pGuildInfo );

			gcActiveGuildList.addGuildInfo( pGuildInfo );
		}
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	__END_CATCH

}

void GuildManager::heartbeat()
	throw(Error)
{
	__BEGIN_TRY

#ifdef __SHARED_SERVER__
	Timeval currentTime;
	getCurrentTime( currentTime );

	////////////////////////////////////////////////////////
	// 길드 가입 신청 대기 시간이 넘어간 멤버를 지운다.
	////////////////////////////////////////////////////////
	if ( currentTime > m_WaitMemberClearTime )
	{
		__ENTER_CRITICAL_SECTION( m_Mutex )

		VSDateTime currentDateTime = VSDateTime::currentDateTime();

		HashMapGuildConstItor itr = m_Guilds.begin();
		for ( ; itr != m_Guilds.end(); itr++ )
		{
			Guild* pGuild = itr->second;

			list<string> mList;

			pGuild->expireTimeOutWaitMember( currentDateTime, mList );

			list<string>::const_iterator itr2 = mList.begin();

			for ( ; itr2 != mList.end(); itr2++ )
			{
				// 가입이 취소되었음을 게임서버에 알린다.
				SGExpelGuildMemberOK sgExpelGuildMemberOK;
				sgExpelGuildMemberOK.setGuildID( pGuild->getID() );
				sgExpelGuildMemberOK.setName( *itr2 );
				sgExpelGuildMemberOK.setSender( pGuild->getMaster() );

				g_pGameServerManager->broadcast( &sgExpelGuildMemberOK );
			}
		}

		m_WaitMemberClearTime.tv_sec = currentTime.tv_sec + 3600;			// 1시간 주기

		__LEAVE_CRITICAL_SECTION( m_Mutex )
	}
#endif

	__END_CATCH
}

string GuildManager::toString() const
	throw()
{
	__BEGIN_TRY

	StringStream msg;
	return msg.toString();

	__END_CATCH
}

bool GuildManager::isGuildMaster( GuildID_t guildID, PlayerCreature* pPC )
	throw(Error)
{
#ifdef __GAME_SERVER__
	__BEGIN_TRY

	Guild* pGuild = getGuild( guildID );

	if ( pGuild == NULL ) return false;

//	cout << "isGuildMaster : " << pGuild->getMaster() << ", " << pPC->getName() << endl;
	return ( pGuild->getMaster() == pPC->getName() );

	__END_CATCH
#else
	return false;
#endif
}

// 길드가 성을 가졌나?
bool GuildManager::hasCastle( GuildID_t guildID ) 
	throw(Error)
{
	__BEGIN_TRY

	bool bHasCastle = false;

#ifdef __GAME_SERVER__

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT count(*) FROM CastleInfo WHERE GuildID = %d", (int)guildID);

		if (pResult->next()) 
		{
			int count = pResult->getInt(1);

			if (count > 0)
			{
				bHasCastle = true;
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

#endif

	return bHasCastle;

	__END_CATCH
}

// 길드가 성을 가졌나?
bool GuildManager::hasCastle( GuildID_t guildID, ServerID_t& serverID, ZoneID_t& zoneID ) 
	throw(Error)
{
	__BEGIN_TRY

	bool bHasCastle = false;

#ifdef __GAME_SERVER__

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		Result* pResult = pStmt->executeQuery(
				"SELECT ServerID, ZoneID FROM CastleInfo WHERE GuildID = %d", (int)guildID);

		if (pResult->next()) 
		{
			serverID = pResult->getInt(1);
			zoneID = pResult->getInt(2);

			bHasCastle = true;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

#endif

	return bHasCastle;

	__END_CATCH
}

// 길드가 전쟁신청을 했나?
bool GuildManager::hasWarSchedule( GuildID_t guildID ) 
	throw(Error)
{
	__BEGIN_TRY

	bool bHasWarSchedule = false;

#ifdef __GAME_SERVER__

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
#ifndef __OLD_GUILD_WAR__
		Result* pResult = pStmt->executeQuery(
				"SELECT count(*) FROM WarScheduleInfo WHERE "
				"(AttackGuildID = %d OR AttackGuildID2 = %d OR AttackGuildID3 = %d OR AttackGuildID4 = %d OR AttackGuildID5 = %d) AND Status in ('WAIT', 'START')",
				(int)guildID, (int)guildID, (int)guildID, (int)guildID, (int)guildID);
#else
		Result* pResult = pStmt->executeQuery(
				"SELECT count(*) FROM WarScheduleInfo WHERE AttackGuildID = %d AND Status<>'END'", (int)guildID);
#endif

		if (pResult->next()) 
		{
			int count = pResult->getInt(1);

			if (count > 0)
			{
				bHasWarSchedule = true;
			}
		}

#ifndef __OLD_GUILD_WAR__
		pResult = pStmt->executeQuery("SELECT count(*) FROM ReinforceRegisterInfo, WarScheduleInfo WHERE ReinforceRegisterInfo.WarID = WarScheduleInfo.WarID AND WarScheduleInfo.Status in ('WAIT', 'START') AND ReinforceRegisterInfo.ReinforceGuildID = %d AND ReinforceRegisterInfo.Status<>'DENY'", (int)guildID);

		if (pResult->next()) 
		{
			int count = pResult->getInt(1);

			if (count > 0)
			{
				bHasWarSchedule = true;
			}
		}
#endif

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

#endif

	return bHasWarSchedule;

	__END_CATCH
}

bool GuildManager::hasActiveWar( GuildID_t guildID )
	throw(Error)
{
	__BEGIN_TRY

	bool bHasActiveWar = false;

#ifdef __GAME_SERVER__

	ServerID_t	serverID;
	ZoneID_t	zoneID;

	if ( hasCastle( guildID, serverID, zoneID ) )
	{
		// 성을 소유하고 있다면 그 성을 상대로 하는 길드 전쟁이 있는지 확인한다.
		Statement* pStmt = NULL;
		
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			Result* pResult = pStmt->executeQuery(
				"SELECT count(*) FROM WarScheduleInfo WHERE ServerID = %u AND ZoneID = %u AND Status = 'START'", serverID, zoneID );

			if ( pResult->next() )
			{
				int count = pResult->getInt(1);

				if ( count > 0 )
				{
					bHasActiveWar = true;
				}
			}

			SAFE_DELETE( pStmt );
		}
		END_DB( pStmt )
	}
	else
	{
		// 성을 소유하고 있지 않다면 그 길드가 어떤 성을 상대로 하는 길드 전쟁이 있는지 확인한다.
		Statement* pStmt = NULL;

		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			Result* pResult = pStmt->executeQuery(
					"SELECT count(*) FROM WarScheduleInfo WHERE AttackGuildID = %d AND Status = 'START'", (int)guildID);

			if (pResult->next()) 
			{
				int count = pResult->getInt(1);

				if (count > 0)
				{
					bHasActiveWar = true;
				}
			}

			SAFE_DELETE(pStmt);
		}
		END_DB(pStmt)
	}

#endif

	return bHasActiveWar;

	__END_CATCH
}


string GuildManager::getGuildName( GuildID_t guildID )
	throw (Error)
{
	__BEGIN_TRY

	Guild* pGuild = getGuild( guildID );

	if ( pGuild != NULL )
		return pGuild->getName();

	return "";

	__END_CATCH
}

