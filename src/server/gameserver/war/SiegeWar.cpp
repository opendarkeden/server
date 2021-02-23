///////////////////////////////////////////////////////////////////
// 전쟁에 대한 전반적인 정보 및 전쟁 시작 및 종료시 처리루틴 구현
///////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "Guild.h"
#include "GuildManager.h"
#include "SiegeWar.h"
#include "Mutex.h"
#include "WarSystem.h"
#include "Properties.h"
#include "DB.h"
#include "Assert.h"
#include "ZoneGroupManager.h"
#include "HolyLandRaceBonus.h"
#include "Zone.h"
#include "ZoneGroup.h"
#include "ZoneUtil.h"
#include "CastleInfoManager.h"
#include "ZoneInfoManager.h"
#include "PCManager.h"
#include "StringStream.h"
#include "SiegeManager.h"

#include "GameServerInfoManager.h"
#include "LoginServerManager.h"

#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNoticeEvent.h"
#include "Gpackets/GCWarScheduleList.h"
#include "Gpackets/GCNPCResponse.h"
#include "Cpackets/CGSay.h"
#include "Gpackets/GGCommand.h"
#include "GuildWarInfo.h"

//--------------------------------------------------------------------------------
//
// constructor / destructor
//
//--------------------------------------------------------------------------------
SiegeWar::SiegeWar( ZoneID_t castleZoneID, WarState warState, WarID_t warID )
: War( warState, warID ), 
	m_CastleZoneID(castleZoneID), m_RegistrationFee( 0 )
{
	m_bModifyCastleOwner 	= false;
	for ( int i=0; i<5; ++i ) m_ChallangerGuildID[i] = 0;

	m_ChallangerGuildCount = 0;
	m_ReinforceGuildID = 0;
	m_RecentReinforceCandidate = 0;
}

SiegeWar::~SiegeWar()
{
}

int SiegeWar::getGuildSide(GuildID_t guildID) const
{
	if ( guildID == m_ReinforceGuildID ) return 2;

	for ( int i=0; i<5; ++i )
	{
		if ( m_ChallangerGuildID[i] == guildID ) return 3 + i;
	}

	CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_CastleZoneID );
	Assert(pCastleInfo!=NULL);

	GuildID_t OwnerGuildID = pCastleInfo->getGuildID();
	if ( guildID == OwnerGuildID ) return 1;

	return 0;
}

bool SiegeWar::addChallengerGuild(GuildID_t gID)
{
	if ( m_ChallangerGuildCount > 5 ) return false;
	if ( gID == 0 || gID == 66 || gID == 99 ) return false;

	m_ChallangerGuildID[m_ChallangerGuildCount++] = gID;
	return true;
}

//--------------------------------------------------------------------------------
//
// executeStart
//
//--------------------------------------------------------------------------------
// 전쟁이 시작하는 시점에서 처리해야 될 것들
//
// (!) Zone에 붙어있는 WarScheduler에서 실행되는 부분이므로 
//     자신의 Zone(성)에 대한 처리는 lock이 필요없다.
//--------------------------------------------------------------------------------
void SiegeWar::executeStart()
	throw (Error)
{
	__BEGIN_TRY

	sendWarStartMessage();
	clearReinforceRegisters();

	// 이 부분은 나중에~~ CastleInfo로 넣는게 낫겠다.
	CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_CastleZoneID );
	Assert(pCastleInfo!=NULL);

	ZoneID_t siegeZoneID = SiegeManager::Instance().getSiegeZoneID( m_CastleZoneID );
	Assert(siegeZoneID != 0 );
/*
	GuildID_t OwnerGuildID = pCastleInfo->getGuildID();
	if ( !pCastleInfo->isCommon() )
	{
		SiegeManager::Instance().recallGuild( m_CastleZoneID, siegeZoneID, OwnerGuildID, 1, 200 );
		filelog("WarLog.txt", "%d 길드가 성 주인입니다.", OwnerGuildID);
	}

	if ( m_ReinforceGuildID != 0 )
	{
		SiegeManager::Instance().recallGuild( m_CastleZoneID, siegeZoneID, m_ReinforceGuildID, 2, 200 );
		filelog("WarLog.txt", "%d 길드가 수성 지원측입니다.", m_ReinforceGuildID);
	}

	for ( int i=0; i<m_ChallangerGuildCount; ++i )
	{
		if ( m_ChallangerGuildID[i] != 0 ) SiegeManager::Instance().recallGuild( m_CastleZoneID, siegeZoneID, m_ChallangerGuildID[i], 3+i, 200 );
		filelog("WarLog.txt", "%d 길드가 공격 %d번측입니다.", m_ChallangerGuildID[i], i);
	}*/

	SiegeManager::Instance().start( siegeZoneID );

	// SiegeWarHistory Table 에 기록
	recordSiegeWarStart();

	__END_CATCH
}

void SiegeWar::recordSiegeWarStart()
	throw (Error)
{
	__BEGIN_TRY

/*	Statement* pStmt = NULL;

	CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_CastleZoneID );

	// NULL 일리도 없지만 혹시나 하는 맘에 -_-;
	if ( pCastleInfo == NULL )	return;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("INSERT IGNORE INTO SiegeWarHistory (WarID, SiegeWarID, ServerID, CastleName, DefenseGuildID, DefenseGuildName, AttackGuildID, AttackGuildName) VALUES (%d, '%s', %d, '%s', %d, '%s', %d, '%s')", 
						(int)getWarID(),
						getWarStartTime().toStringforWeb().c_str(),
						g_pConfig->getPropertyInt("ServerID"),
						pCastleInfo->getName().c_str(),
						(int)pCastleInfo->getGuildID(),
						g_pGuildManager->getGuildName( pCastleInfo->getGuildID() ).c_str(),
						getChallangerGuildID(),
						g_pGuildManager->getGuildName( getChallangerGuildID() ).c_str() );

	}
	END_DB(pStmt)*/

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
// executeEnd
//
//--------------------------------------------------------------------------------
// 전쟁이 끝나는 시점에서 처리해야 될 것들
//--------------------------------------------------------------------------------
void SiegeWar::executeEnd()
	throw (Error)
{
	__BEGIN_TRY

	//----------------------------------------------------------------------------
	// 전쟁 끝났다는 걸 알린다.
	//----------------------------------------------------------------------------
	sendWarEndMessage();

	if (m_bModifyCastleOwner)
	{
		g_pCastleInfoManager->modifyCastleOwner(m_CastleZoneID, m_WinnerRace, m_WinnerGuildID);

/*		if ( g_pConfig->getPropertyInt("IsNetMarble") == 1 )
		{
			char sCommand[100];
			sprintf( sCommand, "*world *command setCastleOwnerGuild %u %u", m_CastleZoneID, m_WinnerGuildID );
			CGSayHandler::opworld( NULL, sCommand, 0, true );
		}*/

		char sCommand[100];
		sprintf( sCommand, "*command setCastleOwnerGuild %u %u", m_CastleZoneID, m_WinnerGuildID );
		GGCommand ggCommand;
		ggCommand.setCommand(sCommand);

		static int myWorldID = g_pConfig->getPropertyInt("WorldID");
		static int myServerID = g_pConfig->getPropertyInt("ServerID");

		HashMapGameServerInfo* pInfos = g_pGameServerInfoManager->getGameServerInfos()[myWorldID];
		int maxServerGroupID = g_pGameServerInfoManager->getMaxServerGroupID();

		for ( int groupID=0; groupID<maxServerGroupID; ++groupID )
		{
			HashMapGameServerInfo& gameServerInfo = pInfos[groupID];

			if (!gameServerInfo.empty())
			{
				HashMapGameServerInfo::const_iterator itr = gameServerInfo.begin();
				for (; itr != gameServerInfo.end(); itr++)
				{
					GameServerInfo* pGameServerInfo = itr->second;

					if (pGameServerInfo->getWorldID()==myWorldID)
					{
						// 현재 서버가 아닌 경우에만..(위에서 처리했으므로)
						if (pGameServerInfo->getGroupID()==myServerID)
						{
						}
						else if ( pGameServerInfo->getCastleFollowingServerID() == myServerID )
						{
							g_pLoginServerManager->sendPacket( pGameServerInfo->getIP(),
																pGameServerInfo->getUDPPort(),
																&ggCommand );
							cout << "send change castle packet to " << pGameServerInfo->getIP() << ", " << pGameServerInfo->getUDPPort() << endl;
						}
					}
				}
			}
		}
	}
	else 
	{
		// WinnerGuildID 를 지금 주인으로 셋팅해준다
		CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_CastleZoneID );
		m_WinnerGuildID = pCastleInfo->getGuildID();
	}

	//----------------------------------------------------------------------------
	// 전쟁 신청금을 성에 쌓는다. 
	// (우선 전쟁 결과에 따라서 성의 주인이 바뀌었다고 가정한다.)
	//----------------------------------------------------------------------------
	g_pCastleInfoManager->increaseTaxBalance( m_CastleZoneID, m_RegistrationFee );
	m_RegistrationFee = 0;
	//tinysave("전쟁신청금=0") <-- 할 필요 있을까?

	ZoneID_t siegeZoneID = SiegeManager::Instance().getSiegeZoneID( m_CastleZoneID );
	Assert(siegeZoneID != 0 );

	filelog("SiegeWar.log", "[%u] executeEnd : reset zone %u", getWarID(), siegeZoneID);
	SiegeManager::Instance().reset( siegeZoneID );

	// SiegeWarHistory Table 에 기록
	recordSiegeWarEnd();

	__END_CATCH
}

void SiegeWar::recordSiegeWarEnd()
	throw (Error)
{
	__BEGIN_TRY

/*	Statement* pStmt = NULL;

	BEGIN_DB
	{

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("UPDATE SiegeWarHistory SET WinnerGuildID = %d , WinnerGuildName = '%s' WHERE WarID = %d",
						(int)m_WinnerGuildID,
						g_pGuildManager->getGuildName( m_WinnerGuildID ).c_str(),
						(int)getWarID() );

	}
	END_DB(pStmt)

	// script 돌리기 ㅡ.,ㅡ system 함수를 쓰게 될 줄이야 !_!
	char cmd[100];
	sprintf(cmd, "/home/darkeden/vs/bin/script/recordSiegeWarHistory.py %d %d %d ",
					(int)getWarID(), 
					g_pConfig->getPropertyInt("Dimension"),
					g_pConfig->getPropertyInt("WorldID") );

	filelog("script.log", cmd);
	system(cmd);
*/
	__END_CATCH
}

string SiegeWar::getWarName() const
	throw (Error)
{
	__BEGIN_TRY

	return "공성전";

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
//	isModifyCastleOwner( PlayerCreature* pPC )
//
//--------------------------------------------------------------------------------
// 성의 주인이 바뀌는 경우
//--------------------------------------------------------------------------------
bool
SiegeWar::isModifyCastleOwner( PlayerCreature* pPC )
	throw (Error)
{
	__BEGIN_TRY

	Assert(pPC!=NULL);

	CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_CastleZoneID );
	Assert(pCastleInfo!=NULL);

	if ( pPC->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_1 ) ) return true;
	if ( pPC->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_2 ) ) return true;
	if ( pPC->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_3 ) ) return true;
	if ( pPC->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_4 ) ) return true;
	if ( pPC->isFlag( Effect::EFFECT_CLASS_SIEGE_ATTACKER_5 ) ) return true;

	return false;

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
// getWinnerGuildID( PlayerCreature* pPC ) 
//
//--------------------------------------------------------------------------------
// 전쟁에 승리한 길드의 GuildID를 넘겨준다.
//--------------------------------------------------------------------------------
GuildID_t       
SiegeWar::getWinnerGuildID( PlayerCreature* pPC ) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pPC!=NULL);

	// 길드전쟁인 경우 : 전쟁신청 길드와 pPC의 길드가 같으면 pPC의 GuildID
	// 					 아니면 원래 성주인의 길드ID와 같으면 원래 성주인 GuildID
	//					 아니면 COMMON_GUILD_ID
//	CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_CastleZoneID );
//	Assert( pCastleInfo!=NULL );

	return pPC->getGuildID();

	__END_CATCH
}

bool SiegeWar::endWar(PlayerCreature* pPC)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pPC!=NULL);

	// < 성 주인 변경 >
	if (isModifyCastleOwner( pPC ))
	{
		m_WinnerRace 			= pPC->getRace();
		m_WinnerGuildID 		= getWinnerGuildID( pPC );
		m_bModifyCastleOwner 	= true;

		return true;
	}

	return false;

	__END_CATCH
}

//--------------------------------------------------------------------------------
// 전쟁 끝날 때
//--------------------------------------------------------------------------------
void SiegeWar::sendWarEndMessage() const
    throw (ProtocolException, Error)
{
    __BEGIN_TRY

	War::sendWarEndMessage();

	// 안전지대 해제 확인? 패킷
	GCNoticeEvent gcNoticeEvent;
	gcNoticeEvent.setCode( NOTICE_EVENT_WAR_OVER );
	gcNoticeEvent.setParameter( m_CastleZoneID );
	g_pZoneGroupManager->broadcast( &gcNoticeEvent );

    __END_CATCH
}

void    SiegeWar::makeWarScheduleInfo( WarScheduleInfo* pWSI ) const
	throw(Error)
{
	__BEGIN_TRY

    pWSI->warType 				= getWarType();

	for ( int i=0; i<5; ++i )
	{
		pWSI->challengerGuildID[i] = m_ChallangerGuildID[i];
		if ( m_ChallangerGuildID[i] != 0 ) pWSI->challengerGuildName[i] = g_pGuildManager->getGuildName( m_ChallangerGuildID[i] );
	}

	pWSI->reinforceGuildID = m_ReinforceGuildID;
	if ( m_ReinforceGuildID != 0 ) pWSI->reinforceGuildName = g_pGuildManager->getGuildName( m_ReinforceGuildID );

	__END_CATCH
}

void 	SiegeWar::makeWarInfo(WarInfo* pWarInfo) const 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pWarInfo!=NULL);
	Assert(pWarInfo->getWarType()==WAR_GUILD);

	GuildWarInfo* pGuildWarInfo = dynamic_cast<GuildWarInfo*>(pWarInfo);
	Assert(pGuildWarInfo!=NULL);

	//---------------------------------------------------
	// 현재 성 주인 구하기
	//---------------------------------------------------
	CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( getCastleZoneID() );
	if (pCastleInfo==NULL) 
	{
		filelog("WarError.log", "CastleInfo가 없다(%d)", getCastleZoneID());
		return;
	}

	GuildID_t ownGuildID 		= pCastleInfo->getGuildID();

	pGuildWarInfo->addJoinGuild( ownGuildID ); 				// 현재 성 주인

	for ( int i=0; i<m_ChallangerGuildCount; ++i )
		pGuildWarInfo->addJoinGuild( m_ChallangerGuildID[i] );

	pGuildWarInfo->setCastleID( getCastleZoneID() );

	// 공격 길드 이름
	static const string commonGuild("없음");

	string attackGuildName;
	string defenseGuildName;

	attackGuildName = g_pGuildManager->getGuildName( m_ChallangerGuildID[0] );
	if ( m_ChallangerGuildCount > 1 ) 
	{
		char buffer[40];
		snprintf(buffer, 40, "%s외 %u개", attackGuildName.c_str(), m_ChallangerGuildCount-1);
		attackGuildName = buffer;
	}

	if 		( pCastleInfo->isCommon() )	defenseGuildName = commonGuild;
	else defenseGuildName = g_pGuildManager->getGuildName( ownGuildID );

	pGuildWarInfo->setAttackGuildName( attackGuildName );
	pGuildWarInfo->setDefenseGuildName( defenseGuildName );

	__END_CATCH
}


string SiegeWar::toString() const
	throw (Error)
{
	__BEGIN_TRY

	StringStream msg;
	
	msg << "SiegeWar("
		<< "WarID:" << (int)getWarID()
		<< ",State:" << (int)getState()
		<< ",CastleZoneID:" << (int)m_CastleZoneID
		<< ",WarType:" << getWarType2DBString()
		<< ",ChallengerGuildID:" << (int)m_ChallangerGuildID[0]
		<< ",RegistrationFee:" << (int)m_RegistrationFee
		<< ")";

	return msg.toString();

	__END_CATCH
}

BYTE SiegeWar::canReinforce(GuildID_t gID)
{
	if ( m_ReinforceGuildID != 0 ) return NPC_RESPONSE_ALREADY_REINFORCE_ACCEPTED;
	if ( g_pGuildManager->hasWarSchedule(gID) ) return NPC_RESPONSE_WAR_ALREADY_REGISTERED;

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("Darkeden")->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT COUNT(*) FROM ReinforceRegisterInfo WHERE WarID=%u AND ServerID=%u AND Status='WAIT'",
				getWarID(), g_pConfig->getPropertyInt("ServerID") );

		if ( pResult->next() )
		{
			if ( pResult->getInt(1) > 3 ) return NPC_RESPONSE_TOO_MANY_GUILD_REGISTERED;
		}

		pResult = pStmt->executeQuery( "SELECT COUNT(*) FROM ReinforceRegisterInfo WHERE WarID=%u AND ServerID=%u AND ReinforceGuildID=%u AND Status='DENY'",
				getWarID(), g_pConfig->getPropertyInt("ServerID"), gID );

		if ( pResult->next() )
		{
			if ( pResult->getInt(1) > 0 ) return NPC_RESPONSE_REINFORCE_DENYED;
		}

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	return NPC_RESPONSE_WAR_REGISTRATION_OK;
}

GuildID_t SiegeWar::recentReinforceGuild()
{
	GuildID_t ret = 0;
	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("Darkeden")->createStatement();
		Result* pResult = pStmt->executeQuery( "SELECT ReinforceGuildID FROM ReinforceRegisterInfo WHERE WarID=%u AND ServerID=%u AND Status='WAIT'",
				getWarID(), g_pConfig->getPropertyInt("ServerID") );

		if ( pResult->next() )
		{
			ret = pResult->getInt(1);
		}

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	m_RecentReinforceCandidate = ret;

	return ret;
}

BYTE SiegeWar::registerReinforce(GuildID_t gID)
{
	BYTE ret = canReinforce(gID);
	if ( ret != NPC_RESPONSE_WAR_REGISTRATION_OK ) return ret;

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("Darkeden")->createStatement();
		pStmt->executeQuery( "INSERT INTO ReinforceRegisterInfo (WarID, ServerID, ReinforceGuildID, Status) VALUES "
				"(%u, %u, %u, 'WAIT')",
				getWarID(), g_pConfig->getPropertyInt("ServerID"), gID );

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	return ret;
}

bool SiegeWar::acceptReinforce()
{
	bool ret = false;
	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("Darkeden")->createStatement();
		pStmt->executeQuery( "UPDATE ReinforceRegisterInfo SET Status='ACCEPT' WHERE WarID=%u AND ServerID=%u AND ReinforceGuildID=%u",
				getWarID(), g_pConfig->getPropertyInt("ServerID"), m_RecentReinforceCandidate );

		if ( pStmt->getAffectedRowCount() > 0 ) ret = true;
		if ( ret ) m_ReinforceGuildID = m_RecentReinforceCandidate;

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	return ret;
}

bool SiegeWar::denyReinforce()
{
	bool ret = false;
	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("Darkeden")->createStatement();
		pStmt->executeQuery( "UPDATE ReinforceRegisterInfo SET Status='DENY' WHERE WarID=%u AND ServerID=%u AND ReinforceGuildID=%u",
				getWarID(), g_pConfig->getPropertyInt("ServerID"), m_RecentReinforceCandidate );

		if ( pStmt->getAffectedRowCount() > 0 ) ret = true;

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)

	return ret;
}

void SiegeWar::clearReinforceRegisters()
{
	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("Darkeden")->createStatement();
		pStmt->executeQuery( "DELETE FROM ReinforceRegisterInfo WHERE WarID=%u AND ServerID=%u",
				getWarID(), g_pConfig->getPropertyInt("ServerID") );

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt)
}
