#include "WarSchedule.h"
#include "WarScheduler.h"
#include "Assert.h"
#include "DB.h"
#include "Zone.h"
#include "Properties.h"
#include "GuildWar.h"
#include "SiegeWar.h"
#include "VariableManager.h"
#include <stdio.h>
#include "Gpackets/GCWarScheduleList.h"
#include "WarSystem.h"

// dt 이후의 월, 수, 금 오후 8시(~9시)
// dt 이후의 일요일 7시(~9시)
const int NextWarDay [2][8] =
{
	{ 0, 1, 7, 6, 5, 4, 3, 2 },	// 길드전
	//{ 0, 2, 1, 0, 3, 2, 1, 0 }	// RaceWar 휑,寧,랗,힛,愷,巧,짇,휑
	{ 0, 6, 5, 4, 3, 2, 1, 0 }	// RaceWar 휑,寧,랗,힛,愷,巧,짇,휑
};

// 테스트 서버에서..
const int NextWarHour [2][24] =
{
	//                               *     *              *     *
	// 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18  19  20  21  22  23
	{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 2, 1, 5, 4, 3, 2, 1, 2, 1, 15, 14, 13, 12, 11 },	// 길드전

	//                                           *                          *
	// 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18  19  20  21  22  23
	{ 14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 8, 7, 6, 5, 4, 3,   2,  1, 16, 15 }	// 종족전
};


WarScheduler::WarScheduler( Zone* pZone ) 
	
: m_pZone(pZone) 
{
	// Zone에 붙어서 돌아간다.
	// 그런데, cancelGuildSchedules()는 외부에서 불린다.
	m_Mutex.setName("WarSheduler");
}

WarScheduler::~WarScheduler()
	
{
}

bool WarScheduler::makeGCWarScheduleList(GCWarScheduleList* pGCWarScheduleList) const
	
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)	

	const RecentSchedules::container_type& Schedules = m_RecentSchedules.getSchedules();
	RecentSchedules::const_iterator itr = Schedules.begin();

	for (; itr!=Schedules.end(); itr++)
	{
		const WarSchedule* pWarSchedule = dynamic_cast<WarSchedule*>(*itr);
		Assert(pWarSchedule!=NULL);

		WarScheduleInfo* pWSI = new WarScheduleInfo;
		pWarSchedule->makeWarScheduleInfo( pWSI );

		pGCWarScheduleList->addWarScheduleInfo( pWSI );
	}

	// 자동으로 시작하는 기능이 설정되어 있다면, 종족 전쟁 정보는 무조건 넣어준다.
	if (g_pVariableManager->isAutoStartRaceWar())
	{
		WarScheduleInfo* pWSI = new WarScheduleInfo;
		if (g_pWarSystem->addRaceWarScheduleInfo( pWSI ))
		{
			pGCWarScheduleList->addWarScheduleInfo( pWSI );
		}
		else
		{
			SAFE_DELETE(pWSI);
		}
	}
	
	__LEAVE_CRITICAL_SECTION(m_Mutex)	

	__END_CATCH

	return true;
}

Work* WarScheduler::heartbeat() 
	
{
	__BEGIN_TRY
	
	Work* pWork = NULL;

	__ENTER_CRITICAL_SECTION(m_Mutex)	

	pWork = Scheduler::heartbeat();	

	__LEAVE_CRITICAL_SECTION(m_Mutex)	


	// 종족 전쟁인 경우는 다시 1주일 후 스케쥴을 넣어준다.
	/*
	if (pWork != NULL)
	{
		War* pWar = dynamic_cast<War*>(pWork);
		Assert(pWar!=NULL);

		if (pWar->getWarType()==WAR_RACE
			&& getWarTypeCount( WAR_RACE )==0)
		{
			War* pNewWar = new War( m_pZone->getZoneID(), WAR_RACE, 0, War::WAR_STATE_WAIT );

			addWar( pNewWar );

			filelog("WarLog.txt", "[%d][WarID=%d] 종족 전쟁이 시작되었으므로 다음 종족 전쟁을 추가합니다.", 
								(int)m_pZone->getZoneID(), (int)pWar->getWarID());
		}
	}
	*/

	return pWork;

	__END_CATCH
}

void WarScheduler::load()
	
{
	__BEGIN_TRY

	Statement*	pStmt = NULL;
	Result*		pResult = NULL;

	__ENTER_CRITICAL_SECTION(m_Mutex)	

	clear();

	//int numRaceWar = 0;

	VSDateTime currentDateTime( VSDateTime::currentDateTime() );

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery( 
#ifndef __OLD_GUILD_WAR__
				"SELECT WarID, WarType, AttackerCount, AttackGuildID, AttackGuildID2, AttackGuildID3, AttackGuildID4, AttackGuildID5, "
						"WarFee, StartTime FROM WarScheduleInfo "
#else
				"SELECT WarID, WarType, AttackGuildID, WarFee, StartTime FROM WarScheduleInfo "
#endif
						"WHERE ServerID = %u AND ZoneID = %u AND ( Status = 'WAIT' OR Status = 'START' ) "
						"ORDER BY StartTime",
						g_pConfig->getPropertyInt("ServerID"), 
						(int)m_pZone->getZoneID() 
		);

		if( pResult->getRowCount() > 0 )
		{
			WarID_t			warID;
			WarType_t		warType;
#ifndef __OLD_GUILD_WAR__
			uint			challengerNum;
			GuildID_t		challengerGuildID[5];
#else
			GuildID_t		challengerGuildID;
#endif
			Gold_t			warRegistrationFee;
			string			dateTemp;
			VSDateTime		warStartTime;
			
			while( pResult->next() )
			{
				int i=0;

				warID				= (WarID_t)		pResult->getInt( ++i );
				string warTypeStr	= pResult->getString( ++i );

				if (warTypeStr=="GUILD") 		warType = WAR_GUILD;
				else if (warTypeStr=="RACE") 	continue;//warType = WAR_RACE;
				else Assert(false);
#ifndef __OLD_GUILD_WAR__
				challengerNum = pResult->getInt( ++i );

				for ( int j=0 ; j<5; ++j )
				{
					challengerGuildID[j]	= (GuildID_t)	pResult->getInt( ++i );
				}
#else
				challengerGuildID	= (GuildID_t)	pResult->getInt( ++i );
#endif

				warRegistrationFee	= (Gold_t)		pResult->getInt( ++i );
				dateTemp			=				pResult->getString( ++i );
				warStartTime		= VSDateTime(dateTemp);

				// 이미 시작되었어야할 전쟁이라면 시작시간을 바꿔준다.
				if (warStartTime < currentDateTime)
				{
					warStartTime = currentDateTime;
				}

#ifndef __OLD_GUILD_WAR__
				SiegeWar* pWar = new SiegeWar( m_pZone->getZoneID(), War::WAR_STATE_WAIT, warID );
#else
				GuildWar* pWar = new GuildWar( m_pZone->getZoneID(), challengerGuildID, War::WAR_STATE_WAIT, warID );
#endif
				pWar->setWarStartTime( warStartTime );
				pWar->setRegistrationFee( warRegistrationFee );

#ifndef __OLD_GUILD_WAR__
				pResult = pStmt->executeQuery( "SELECT ReinforceGuildID FROM ReinforceRegisterInfo WHERE WarID=%u AND Status='ACCEPT'", warID );

				if ( pResult->next() )
				{
					pWar->setReinforceGuildID( pResult->getInt(1) );
				}

				for ( int j=0 ; j<challengerNum ; ++j )
				{
					pWar->addChallengerGuild(challengerGuildID[j]);
				}
#endif

				WarSchedule* pWarSchedule = new WarSchedule( pWar, warStartTime, Schedule::SCHEDULE_TYPE_ONCE );
				addSchedule( pWarSchedule );

				//cout << "WarScheduler: loading [" << pWarSchedule->toString().c_str() << "]" << endl;
				filelog("WarLog.txt", "[LOAD] %s", pWar->toString().c_str());

				//if (warType==WAR_RACE) numRaceWar++;
			}
		}

		SAFE_DELETE( pStmt );

	}
	END_DB( pStmt )

	// 종족 전쟁 설정된게 없으면 설정한다.
	/*
	if (numRaceWar==0)
	{
		VSDateTime warStartTime = getNextWarDateTime( WAR_RACE );

		War* pRaceWar = new War( m_pZone->getZoneID(), WAR_RACE, 0, War::WAR_STATE_WAIT );
		WarSchedule* pWarSchedule = new WarSchedule( pRaceWar, warStartTime, Schedule::SCHEDULE_TYPE_PERIODIC );
		addSchedule( pWarSchedule );

		filelog("WarLog.txt", "[%d][WarID=%d] 종족 전쟁이 없으므로 종족 전쟁을 추가합니다.", 
								(int)m_pZone->getZoneID(), (int)pRaceWar->getWarID());

		pWarSchedule->create();
	}
	*/

	__LEAVE_CRITICAL_SECTION(m_Mutex)	

	__END_CATCH
}

int WarScheduler::getWarTypeCount(WarType_t warType)
	
{
	__BEGIN_TRY

	int raceWarCount = 0;

	__ENTER_CRITICAL_SECTION(m_Mutex)	

	RecentSchedules::const_iterator itr = m_RecentSchedules.getSchedules().begin();

	for( ; itr != m_RecentSchedules.getSchedules().end() ; itr++ )
	{
		WarSchedule* pWarSchedule = dynamic_cast<WarSchedule*>( (*itr) );
		Assert(pWarSchedule!=NULL);

		War* pWar = dynamic_cast<War*>(pWarSchedule->getWork());
		Assert(pWar!=NULL);

		if (pWar->getWarType()==warType)
		{
			raceWarCount ++;
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)	

	return raceWarCount;

	__END_CATCH
}

void WarScheduler::tinysave( WarID_t warID, const string& query )
	
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_Mutex)	

	RecentSchedules::const_iterator itr = m_RecentSchedules.getSchedules().begin();

	for( ; itr != m_RecentSchedules.getSchedules().end() ; itr++ )
	{
		WarSchedule* pWarSchedule = dynamic_cast<WarSchedule*>( (*itr) );

		if( pWarSchedule->getWarID() == warID )
		{
			pWarSchedule->tinysave( query );
			m_Mutex.unlock();
			return;
		}
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)	

	filelog( "WarError.log", "WarScheduler::tinySave() DB에 WarID:%d 인 WarSchedule이 없습니다.", warID );

	__END_CATCH
}

VSDateTime
WarScheduler::getLastWarDateTime( WarType_t warType ) const
{
	const RecentSchedules::container_type& schedules = m_RecentSchedules.getSchedules();
	RecentSchedules::const_iterator itr = schedules.begin();

	bool bFound = false;
	VSDateTime dt = VSDateTime::currentDateTime();

	for( ; itr != schedules.end(); itr++ )
	{
		WarSchedule* pSchedule = dynamic_cast<WarSchedule*>(*itr);
		if( pSchedule->getWar()->getWarType() == warType )
		{
			if (bFound)
			{
				if ( dt < pSchedule->getScheduledTime() )
					dt = pSchedule->getScheduledTime();
			}
			else
			{
				dt = pSchedule->getScheduledTime();
				bFound = true;
			}
		}
	}

	return dt;
}

// dt 이후의 전쟁 시간을 알아온다.
VSDateTime
WarScheduler::getNextWarDateTime( WarType_t warType, const VSDateTime& dt )
{
	int startHour = 0;

	VSDateTime 	nextWarDateTime;
	VSTime		nextWarTime;

	if (g_pVariableManager->isWarPeriodWeek())	// 아 너무하자나 ㅜㅜ
	{
		switch (warType)
		{
			case WAR_GUILD :
				// dt 이후의 월, 수, 금 오후 8시(~9시)
				startHour = 20;
			break;

			case WAR_RACE :
				// dt 이후의 일요일 7시(~9시)
				startHour = 19;
			break;
		}

		nextWarDateTime = dt.addDays( NextWarDay[warType][dt.date().dayOfWeek()] );
 		nextWarTime 	= VSTime(startHour, 0, 0);
		nextWarDateTime.setTime( nextWarTime );

		if ( nextWarDateTime < VSDateTime::currentDateTime() )
		{
			//nextWarDateTime = nextWarDateTime.addDays( NextWarDay[warType][dt.addDays(1).date().dayOfWeek()] );
			nextWarDateTime = nextWarDateTime.addDays( 1 );
			nextWarDateTime = nextWarDateTime.addDays( NextWarDay[warType][nextWarDateTime.date().dayOfWeek()] );
		}
	}
	else
	{
		nextWarDateTime = dt.addSecs( NextWarHour[warType][dt.time().hour()]*60*60 );
 		nextWarTime 	= VSTime(nextWarDateTime.time().hour(), 0, 0);
		nextWarDateTime.setTime( nextWarTime );
	}

	return nextWarDateTime;
}

VSDateTime
WarScheduler::getNextWarDateTime( WarType_t warType ) const
{
	return getNextWarDateTime( warType, getLastWarDateTime(warType) );
}

bool WarScheduler::addWar( War* pWar ) 
	
{
	__BEGIN_TRY

	WarType_t warType = pWar->getWarType();
	VSDateTime warStartTime = getNextWarDateTime( warType );
	pWar->setWarStartTime( warStartTime );

	Schedule::ScheduleType scheduleType;
	
	if (warType==WAR_GUILD)
	{
		scheduleType = Schedule::SCHEDULE_TYPE_ONCE;
	}
	else// if (warType==WAR_RACE)
	{
		scheduleType = Schedule::SCHEDULE_TYPE_PERIODIC;
	}
	
	WarSchedule* pWarSchedule = new WarSchedule( pWar, warStartTime, scheduleType);

	__ENTER_CRITICAL_SECTION(m_Mutex)	

	addSchedule( pWarSchedule );

	filelog("WarLog.txt", "[%d][WarID=%d] %s 전쟁을 신청했으므로 스케쥴에 추가합니다.", 
				(int)m_pZone->getZoneID(), (int)pWar->getWarID(), 
				(pWar->getWarType()==WAR_GUILD? "길드":"종족") );

	pWarSchedule->create();

	__LEAVE_CRITICAL_SECTION(m_Mutex)	


	return true;

	__END_CATCH
}

bool WarScheduler::canAddWar( WarType_t warType ) 
	
{
	__BEGIN_TRY

	return getSize() < MaxWarSchedule;

	__END_CATCH

}

void
WarScheduler::cancelGuildSchedules() 
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery(
			"UPDATE WarScheduleInfo SET Status='CANCEL' WHERE ServerID = %d AND ZoneID = %d \
				AND WarType='GUILD' AND (Status='WAIT' OR Status='START')",
						g_pConfig->getPropertyInt("ServerID"),
						m_pZone->getZoneID());

		//pStmt->getAffectedRowCount()

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	// 다시 로드한다. ㅋㅋ - -;
	load();

	__END_CATCH
}

bool WarScheduler::hasSchedule( GuildID_t gID ) 
{
	__BEGIN_TRY

	const RecentSchedules::container_type& schedules = m_RecentSchedules.getSchedules();
	RecentSchedules::const_iterator itr = schedules.begin();

	for( ; itr != schedules.end(); itr++ )
	{
		WarSchedule* pSchedule = dynamic_cast<WarSchedule*>(*itr);
		if ( pSchedule == NULL ) continue;

		War* pWar = dynamic_cast<War*>(pSchedule->getWork());
		if ( pWar != NULL && pWar->getWarType() == WAR_GUILD )
		{
#ifndef __OLD_GUILD_WAR__
			SiegeWar* pSiegeWar = dynamic_cast<SiegeWar*>(pWar);
			if ( pSiegeWar != NULL && pSiegeWar->isWarParticipant(gID) && pSiegeWar->getState() == War::WAR_STATE_WAIT )
			{
				return true;
			}
#else
			GuildWar* pGuildWar = dynamic_cast<GuildWar*>(pWar);
			if ( pGuildWar != NULL && pGuildWar->getChallangerGuildID() == gID && pGuildWar->getState() == War::WAR_STATE_WAIT )
			{
				return true;
			}
#endif
		}
	}

	return false;

	__END_CATCH
}
