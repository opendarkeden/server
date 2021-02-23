#include "WarSchedule.h"
#include "GuildManager.h"
#include "Properties.h"
#include "War.h"
#include "DB.h"
#include "Zone.h"
#include <stdio.h>
#include "CastleInfoManager.h"
#include "GuildWar.h"
#include "SiegeWar.h"
#include "Gpackets/GCWarScheduleList.h"
#include "Gpackets/GCWarList.h"

WarSchedule::WarSchedule( Work* pWork, const VSDateTime& Time, ScheduleType type = SCHEDULE_TYPE_ONCE ) 
	throw(Error)
: Schedule(pWork, Time, type)
{
	__BEGIN_TRY
	__END_CATCH
}

WarSchedule::~WarSchedule()
	throw (Error)
{
}

void    
WarSchedule::makeWarScheduleInfo( WarScheduleInfo* pWSI ) const
	throw (Error)
{
	__BEGIN_TRY

	Assert(m_pWork!=NULL);

	War* pWar = dynamic_cast<War*>(m_pWork);
	Assert(pWar!=NULL);
	
	pWar->makeWarScheduleInfo( pWSI );
    pWSI->year					= m_ScheduledTime.date().year();
    pWSI->month					= m_ScheduledTime.date().month();
    pWSI->day					= m_ScheduledTime.date().day();
    pWSI->hour					= m_ScheduledTime.time().hour();

	__END_CATCH
}

void
WarSchedule::makeWarInfo(WarInfo* pWarInfo) const
	throw (Error)
{
	__BEGIN_TRY

	Assert(pWarInfo!=NULL);

	const Work* pWork = getWork();
	Assert(pWork!=NULL);

	const War* pWar = dynamic_cast<const War*>(pWork);
	Assert(pWar!=NULL);

	//---------------------------------------------------
	// 남은 전쟁 시간 구하기.. -_-; 따로 빼야돼...
	//---------------------------------------------------
	VSDateTime dt(VSDateTime::currentDateTime());
	int endHour = m_ScheduledTime.time().hour();
	int endMin = m_ScheduledTime.time().minute();
	int endSec = m_ScheduledTime.time().second();
	int curHour = dt.time().hour();
	int curMin = dt.time().minute();
	int curSec = dt.time().second();
	int endSecs = endHour*60*60 + endMin*60 + endSec;
	int curSecs = curHour*60*60 + curMin*60 + curSec;

	int remainSec = 0;
	if (endSecs > curSecs) remainSec = endSecs - curSecs;

//	cout << "makeWarInfo : " << m_ScheduledTime.toString() << endl;
	DWORD startTime = ((DWORD)((DWORD)(m_ScheduledTime.date().year()-2000))*1000000) + ((DWORD)((DWORD)m_ScheduledTime.date().month())*10000)
					   + ((DWORD)((DWORD)m_ScheduledTime.date().day())*100) + ((DWORD)((DWORD)m_ScheduledTime.time().hour()));

//	cout << "startTime : " << startTime << endl;

	//---------------------------------------------------
	// WarInfo 값 설정
	//---------------------------------------------------
	pWar->makeWarInfo( pWarInfo );
	pWarInfo->setRemainTime( remainSec );
	pWarInfo->setStartTime( startTime );

//	cout << "after set : " << pWarInfo->getStartTime() << endl;

	__END_CATCH
}

void WarSchedule::create()
	throw(Error)
{
	__BEGIN_TRY

	War* pWar = dynamic_cast<War*>(m_pWork);
	Assert(pWar!=NULL);

	if (pWar->getWarType()!=WAR_GUILD)
		return;

#ifndef __OLD_GUILD_WAR__
	SiegeWar* pSiegeWar = dynamic_cast<SiegeWar*>(pWar);
	Assert(pSiegeWar!=NULL);
#else
	GuildWar* pSiegeWar = dynamic_cast<GuildWar*>(pWar);
	Assert(pSiegeWar!=NULL);
#endif

	Statement*	pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery(
				"INSERT IGNORE INTO WarScheduleInfo ( WarID, ServerID, ZoneID, WarType, AttackGuildID, WarFee, StartTime, Status ) \
				VALUES ( %u, %u, %u, '%s', %u, %u, '%s', '%s' )",
						(int)pSiegeWar->getWarID(), 
						g_pConfig->getPropertyInt( "ServerID" ), 
						(int)pSiegeWar->getCastleZoneID(),
						pSiegeWar->getWarType2DBString().c_str(), 
						(int)pSiegeWar->getChallangerGuildID(), 
						(int)pSiegeWar->getRegistrationFee(), 
						m_ScheduledTime.toDateTime().c_str(),
						pSiegeWar->getState2DBString().c_str() );

		if( pStmt->getAffectedRowCount() == 0 )
		{
			filelog( "WarError.log", "WarSchedule::create() : 이미 테이블에 War 정보가 있거나 테이블이 잘못되었습니다." );
			SAFE_DELETE(pStmt);
			return;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB( pStmt )

	__END_CATCH
}

#ifndef __OLD_GUILD_WAR__
void WarSchedule::save()
	throw(Error)
{
	__BEGIN_TRY

	War* pWar = dynamic_cast<War*>(m_pWork);
	Assert(pWar!=NULL);

	if (pWar->getWarType()!=WAR_GUILD)
		return;

	SiegeWar* pSiegeWar = dynamic_cast<SiegeWar*>(pWar);
	Assert(pSiegeWar!=NULL);

	Statement*	pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery(
				"REPLACE INTO WarScheduleInfo ( WarID, ServerID, ZoneID, WarType, AttackerCount, "
				"AttackGuildID, AttackGuildID2, AttackGuildID3, AttackGuildID4, AttackGuildID5, WarFee, StartTime, Status ) \
				VALUES ( %u, %u, %u, '%s', %u, %u, %u, %u, %u, %u, %u, '%s', '%s' )",
						(int)pSiegeWar->getWarID(), 
						g_pConfig->getPropertyInt( "ServerID" ), 
						(int)pSiegeWar->getCastleZoneID(),
						pSiegeWar->getWarType2DBString().c_str(), 
						(int)pSiegeWar->getChallengerGuildCount(),
						(int)pSiegeWar->getChallangerGuildID(0), 
						(int)pSiegeWar->getChallangerGuildID(1), 
						(int)pSiegeWar->getChallangerGuildID(2), 
						(int)pSiegeWar->getChallangerGuildID(3), 
						(int)pSiegeWar->getChallangerGuildID(4), 
						(int)pSiegeWar->getRegistrationFee(), 
						m_ScheduledTime.toDateTime().c_str(),
						pSiegeWar->getState2DBString().c_str() );

		if( pStmt->getAffectedRowCount() == 0 )
		{
			filelog( "WarError.log", "WarSchedule::create() : 이미 테이블에 War 정보가 있거나 테이블이 잘못되었습니다." );
			SAFE_DELETE(pStmt);
			return;
		}

		SAFE_DELETE(pStmt);
	}
	END_DB( pStmt )

	__END_CATCH
}
#endif

void WarSchedule::tinysave( const string& query )
	throw(Error)
{
	__BEGIN_TRY

	War* pWar = dynamic_cast<War*>(m_pWork);
	Assert(pWar!=NULL);

	Statement*	pStmt = NULL;
	//Result*		pResult = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery(
				"UPDATE WarScheduleInfo SET %s WHERE WarID = %d AND ServerID = %d",
							query.c_str(), 
							pWar->getWarID(), 
							g_pConfig->getPropertyInt( "ServerID" )
				);

/*		if( pStmt->getAffectedRowCount() == 0 )
		{
			filelog( "WarError.log", "WarSchedule::tinySave() DB에 WarSchedule이 없거나 정보가 잘못되었습니다. ZoneID:%d, WarID:%d, Query:%s",
					pWarScheduler->getZone()->getZoneID(), pWar->getWarID(), query.c_str() );
			SAFE_DELETE(pStmt);
			return;
		}*/
	}
	END_DB( pStmt )

	SAFE_DELETE(pStmt);

	__END_CATCH
}

bool WarSchedule::heartbeat()
	throw(Error)
{
	__BEGIN_TRY

	if (Schedule::heartbeat())
	{
		// pSchedule가 실행되었다.
		if (m_pWork!=NULL)
		{
			War* pWar = dynamic_cast<War*>(m_pWork);
			Assert(pWar!=NULL);

			char pState[20];
			sprintf(pState, "Status='%s'", pWar->getState2DBString().c_str());
			tinysave( string(pState) );
		}

		return true;
	}

	return false;

	__END_CATCH
}
