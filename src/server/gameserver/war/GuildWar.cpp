///////////////////////////////////////////////////////////////////
// 전쟁에 대한 전반적인 정보 및 전쟁 시작 및 종료시 처리루틴 구현
///////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "Guild.h"
#include "GuildManager.h"
#include "GuildWar.h"
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
#include "CastleShrineInfoManager.h"
#include "ZoneInfoManager.h"
#include "PCManager.h"
#include "StringStream.h"

#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNoticeEvent.h"
#include "Gpackets/GCWarScheduleList.h"
#include "Cpackets/CGSay.h"
#include "GuildWarInfo.h"

//--------------------------------------------------------------------------------
//
// constructor / destructor
//
//--------------------------------------------------------------------------------
GuildWar::GuildWar( ZoneID_t castleZoneID, GuildID_t challenger, WarState warState, WarID_t warID )
: War( warState, warID ), 
	m_CastleZoneID(castleZoneID), m_ChallangerGuildID( challenger ), m_RegistrationFee( 0 )
{
	m_bModifyCastleOwner 	= false;
}

GuildWar::~GuildWar()
{
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
void GuildWar::executeStart()
	throw (Error)
{
	__BEGIN_TRY

	sendWarStartMessage();

	// 성 안의 안전지대를 끈다.
	ZoneID_t guardShrineZoneID = g_pCastleShrineInfoManager->getGuardShrineZoneID( m_CastleZoneID );
	Zone* pZone = getZoneByZoneID( guardShrineZoneID );
	Assert( pZone != NULL );

	/*
	// NPC를 모두 지운다.
	pZone->deleteNPCs( RACE_SLAYER );
	pZone->deleteNPCs( RACE_VAMPIRE );

	pZone->releaseSafeZone();
	*/

	// 이 부분은 나중에~~ CastleInfo로 넣는게 낫겠다.
	CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_CastleZoneID );
	Assert(pCastleInfo!=NULL);

	GuildID_t OwnerGuildID = pCastleInfo->getGuildID();
		
	// 공용성이 아닌 경우만 몬스터를 없애준다.
	if (OwnerGuildID!=SlayerCommon
		&& OwnerGuildID!=VampireCommon)
	{
		const list<ZoneID_t>& zoneIDs = pCastleInfo->getZoneIDList();

		list<ZoneID_t>::const_iterator itr = zoneIDs.begin();
		for (; itr!=zoneIDs.end(); itr++)
		{
			ZoneID_t targetZoneID = *itr;
			Zone* pTargetZone = getZoneByZoneID( targetZoneID );

			// 성이 아니고.. 던전 맵인 경우..
			if (targetZoneID!=m_CastleZoneID)
			{
				pTargetZone->killAllMonsters();
			}
		}
	}

	g_pCastleShrineInfoManager->removeShrineShield( pZone );

	// GuildWarHistory Table 에 기록
	recordGuildWarStart();

	__END_CATCH
}

void GuildWar::recordGuildWarStart()
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_CastleZoneID );

	// NULL 일리도 없지만 혹시나 하는 맘에 -_-;
	if ( pCastleInfo == NULL )	return;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("INSERT IGNORE INTO GuildWarHistory (WarID, GuildWarID, ServerID, CastleName, DefenseGuildID, DefenseGuildName, AttackGuildID, AttackGuildName) VALUES (%d, '%s', %d, '%s', %d, '%s', %d, '%s')", 
						(int)getWarID(),
						getWarStartTime().toStringforWeb().c_str(),
						g_pConfig->getPropertyInt("ServerID"),
						pCastleInfo->getName().c_str(),
						(int)pCastleInfo->getGuildID(),
						g_pGuildManager->getGuildName( pCastleInfo->getGuildID() ).c_str(),
						getChallangerGuildID(),
						g_pGuildManager->getGuildName( getChallangerGuildID() ).c_str() );

	}
	END_DB(pStmt)

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
// executeEnd
//
//--------------------------------------------------------------------------------
// 전쟁이 끝나는 시점에서 처리해야 될 것들
//--------------------------------------------------------------------------------
void GuildWar::executeEnd()
	throw (Error)
{
	__BEGIN_TRY

	//----------------------------------------------------------------------------
	// 전쟁 끝났다는 걸 알린다.
	//----------------------------------------------------------------------------
	sendWarEndMessage();

	//----------------------------------------------------------------------------
	// 성 주인 변경
	//----------------------------------------------------------------------------
	if (m_bModifyCastleOwner)
	{
		g_pCastleInfoManager->modifyCastleOwner(m_CastleZoneID, m_WinnerRace, m_WinnerGuildID);

		if ( g_pConfig->getPropertyInt("IsNetMarble") == 1 )
		{
			char sCommand[100];
			sprintf( sCommand, "*world *command setCastleOwnerGuild %u %u", m_CastleZoneID, m_WinnerGuildID );
			CGSayHandler::opworld( NULL, sCommand, 0, true );
		}
	}
	else 
	{
		// WinnerGuildID 를 지금 주인으로 셋팅해준다
		CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_CastleZoneID );
		m_WinnerGuildID = pCastleInfo->getGuildID();
	}

	//----------------------------------------------------------------------------
	// 성 상징을 되돌려준다.
	//----------------------------------------------------------------------------
	g_pCastleShrineInfoManager->returnAllCastleSymbol( m_CastleZoneID );

	//----------------------------------------------------------------------------
	// 성 안 안전지대 복구
	//----------------------------------------------------------------------------
	// 이 함수는 ClientManager와 같은 스레드에서 돌아가는 WarSystem에서 불러주므로
	// 성이 포함된 Zone의 락을 걸어줘야 된다.
	ZoneID_t guardShrineZoneID = g_pCastleShrineInfoManager->getGuardShrineZoneID( m_CastleZoneID );
	Zone* pZone = getZoneByZoneID( guardShrineZoneID );
	Assert(pZone!=NULL);

	/*
	CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_CastleZoneID );
	Assert(pCastleInfo!=NULL);

	__ENTER_CRITICAL_SECTION( (*pZone) )

	pZone->resetSafeZone();

	pZone->loadNPCs( pCastleInfo->getRace() );

	g_pShrineInfoManager->addShrineShield_LOCKED( pZone );
	
	__LEAVE_CRITICAL_SECTION( (*pZone) )
	*/

	g_pCastleShrineInfoManager->addShrineShield( pZone );

	//----------------------------------------------------------------------------
	// 전쟁 신청금을 성에 쌓는다. 
	// (우선 전쟁 결과에 따라서 성의 주인이 바뀌었다고 가정한다.)
	//----------------------------------------------------------------------------
	g_pCastleInfoManager->increaseTaxBalance( m_CastleZoneID, m_RegistrationFee );
	m_RegistrationFee = 0;
	//tinysave("전쟁신청금=0") <-- 할 필요 있을까?
	
	// GuildWarHistory Table 에 기록
	recordGuildWarEnd();

	__END_CATCH
}

void GuildWar::recordGuildWarEnd()
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("UPDATE GuildWarHistory SET WinnerGuildID = %d , WinnerGuildName = '%s' WHERE WarID = %d",
						(int)m_WinnerGuildID,
						g_pGuildManager->getGuildName( m_WinnerGuildID ).c_str(),
						(int)getWarID() );

	}
	END_DB(pStmt)

	// script 돌리기 ㅡ.,ㅡ system 함수를 쓰게 될 줄이야 !_!
	char cmd[100];
	sprintf(cmd, "/home/darkeden/vs/bin/script/recordGuildWarHistory.py %d %d %d ",
					(int)getWarID(), 
					g_pConfig->getPropertyInt("Dimension"),
					g_pConfig->getPropertyInt("WorldID") );

	filelog("script.log", cmd);
	system(cmd);

	__END_CATCH
}

string GuildWar::getWarName() const
	throw (Error)
{
	__BEGIN_TRY

	ZoneInfo* pZoneInfo = NULL;
	Guild* pGuild = NULL;

	try {
		pGuild = g_pGuildManager->getGuild( m_ChallangerGuildID );
		pZoneInfo = g_pZoneInfoManager->getZoneInfo( m_CastleZoneID );

		if (pGuild==NULL || pZoneInfo==NULL)
			return "길드 전쟁";

	} catch (Throwable& t) {
		return "길드 전쟁";
	}

	Assert(pZoneInfo!=NULL);
	Assert(pGuild!=NULL);

	StringStream msg;

	msg << pGuild->getName() << "길드가 ";
	msg << pZoneInfo->getFullName() << "을 공격하는 길드 전쟁";

	return msg.toString();

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
GuildWar::isModifyCastleOwner( PlayerCreature* pPC )
	throw (Error)
{
	__BEGIN_TRY

	Assert(pPC!=NULL);

	CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_CastleZoneID );
	Assert(pCastleInfo!=NULL);

	// 공용성 : 공격길드 --> 공격길드성
	// 공용성 : 일반 --> 원래 자리로
	// 길드성 : 공격길드 --> 공격길드성
	// 길드성 : 수비길드 --> 원래 자리로
	// 길드성 : 일반 --> 공용성

	// 길드전쟁인 경우 : 전쟁 신청한 길드이거나
	// 					 길드성인 경우는 일반인
	if (pPC->getGuildID() == m_ChallangerGuildID
		|| !pCastleInfo->isCommon() && pPC->getCommonGuildID()==pPC->getGuildID())
	{
		return true;
	}

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
GuildWar::getWinnerGuildID( PlayerCreature* pPC ) 
	throw(Error)
{
	__BEGIN_TRY

	Assert(pPC!=NULL);

	// 길드전쟁인 경우 : 전쟁신청 길드와 pPC의 길드가 같으면 pPC의 GuildID
	// 					 아니면 원래 성주인의 길드ID와 같으면 원래 성주인 GuildID
	//					 아니면 COMMON_GUILD_ID
	CastleInfo* pCastleInfo = g_pCastleInfoManager->getCastleInfo( m_CastleZoneID );
	Assert( pCastleInfo!=NULL );

	if (m_ChallangerGuildID==pPC->getGuildID()
		|| pPC->getGuildID()==pCastleInfo->getGuildID())
	{
		return pPC->getGuildID();
	}
		
	return pPC->getCommonGuildID();

	__END_CATCH
}

bool GuildWar::endWar(PlayerCreature* pPC)
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
void GuildWar::sendWarEndMessage() const
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

void    GuildWar::makeWarScheduleInfo( WarScheduleInfo* pWSI ) const
	throw(Error)
{
	__BEGIN_TRY

    pWSI->warType 				= getWarType();
    pWSI->challengerGuildID[0]		= getChallangerGuildID();
	for ( int i=1; i<5; ++i ) pWSI->challengerGuildID[i] = 0;
	pWSI->reinforceGuildID = 0;

    pWSI->challengerGuildName[0]	= g_pGuildManager->getGuildName( getChallangerGuildID() );

	__END_CATCH
}

void 	GuildWar::makeWarInfo(WarInfo* pWarInfo) const 
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
	GuildID_t challangerGuildID = getChallangerGuildID();

	pGuildWarInfo->addJoinGuild( ownGuildID ); 				// 현재 성 주인
	pGuildWarInfo->addJoinGuild( challangerGuildID );		// 성에 공격하는 길드
	pGuildWarInfo->setCastleID( getCastleZoneID() );

	// 공격 길드 이름
	static const string commonSlayerGuild("없음");
	static const string commonVampireGuild("없음");

	string attackGuildName;
	string defenseGuildName;

	if 		( challangerGuildID==SlayerCommon )		attackGuildName = commonSlayerGuild;
	else if ( challangerGuildID==VampireCommon ) 	attackGuildName = commonVampireGuild;
	else attackGuildName = g_pGuildManager->getGuildName( getChallangerGuildID() );
		
	if 		( ownGuildID==SlayerCommon ) 	defenseGuildName = commonSlayerGuild;
	else if ( ownGuildID==VampireCommon ) 	defenseGuildName = commonVampireGuild;
	else defenseGuildName = g_pGuildManager->getGuildName( ownGuildID );

	pGuildWarInfo->setAttackGuildName( attackGuildName );
	pGuildWarInfo->setDefenseGuildName( defenseGuildName );

	__END_CATCH
}


string GuildWar::toString() const
	throw (Error)
{
	__BEGIN_TRY

	StringStream msg;
	
	msg << "GuildWar("
		<< "WarID:" << (int)getWarID()
		<< ",State:" << (int)getState()
		<< ",CastleZoneID:" << (int)m_CastleZoneID
		<< ",WarType:" << getWarType2DBString()
		<< ",ChallengerGuildID:" << (int)m_ChallangerGuildID
		<< ",RegistrationFee:" << (int)m_RegistrationFee
		<< ")";

	return msg.toString();

	__END_CATCH
}
