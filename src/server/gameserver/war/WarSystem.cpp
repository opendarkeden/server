#include "WarSystem.h"
#include "Assert.h"
#include "War.h"
#include "RaceWar.h"
#include "WarSchedule.h"
#include "WarScheduler.h"
#include "Player.h"
#include "GamePlayer.h"
#include "ZoneGroupManager.h"
#include "CastleInfoManager.h"
#include "StringStream.h"
#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCWarList.h"
#include "Gpackets/GCWarScheduleList.h"
#include "Gpackets/GCNoticeEvent.h"
#include "VariableManager.h"
#include "GuildWar.h"
#include "SiegeWar.h"
#include "RaceWarInfo.h"
#include "GuildWarInfo.h"
#include "EventRefreshHolyLandPlayer.h"
#include "ShrineInfoManager.h"
#include "ClientManager.h"
#include "HolyLandManager.h"
#include "StringPool.h"

#include <algorithm>
#include <stdio.h>

WarID_t WarSystem::s_WarIDSuccessor = 0;

WarSystem* g_pWarSystem = NULL;

WarSystem::WarSystem()
	throw(Error)
{
	__BEGIN_TRY

	m_Mutex.setName("WarSystem");
	m_MutexWarQueue.setName("WarSystemQueue");
	m_MutexActiveWars.setName("ActiveWars");
    m_MutexWarList.setName("WarList");

	m_bHasRaceWar = false;
	m_bRaceWarToday = false;

	m_pRaceWarSchedule = NULL;

	m_b5Minutes = false;
	m_b20Minutes = false;

	__END_CATCH
}

WarSystem::~WarSystem()
	throw(Error)
{
	__BEGIN_TRY

	SAFE_DELETE(m_pRaceWarSchedule);

	__END_CATCH
}

void WarSystem::init()
	throw (Error)
{
	__BEGIN_TRY

	load();

	prepareRaceWar();

	__END_CATCH
}

void WarSystem::prepareRaceWar()
	throw (Error)
{
	__BEGIN_TRY

	SAFE_DELETE(m_pRaceWarSchedule);

	// 종족 전쟁을 준비해둔다.
	VSDateTime warStartTime = WarScheduler::getNextWarDateTime( WAR_RACE, VSDateTime::currentDateTime() );

	War* pRaceWar 		= new RaceWar( War::WAR_STATE_WAIT );
	pRaceWar->setWarStartTime( warStartTime );
	m_pRaceWarSchedule 	= new Schedule( pRaceWar, warStartTime );

	filelog("WarLog.txt", "[WarID=%d,Time=%s] 종족 전쟁을 추가합니다.", (int)pRaceWar->getWarID(), warStartTime.toString().c_str());

//	m_RaceWarTimeParam = ((DWORD)((DWORD)warStartTime.date().month() << 24)) | ((DWORD)((DWORD)warStartTime.date().day() << 16)) | ((DWORD)((DWORD)warStartTime.time().hour() << 8));
	VSDateTime sendStartTime = warStartTime.addDays(-7);
	m_RaceWarTimeParam = ((DWORD)((DWORD)(sendStartTime.date().year() - 2000))*1000000) + ((DWORD)((DWORD)sendStartTime.date().month())*10000)
					   + ((DWORD)((DWORD)sendStartTime.date().day())*100);//	   + ((DWORD)((DWORD)sendStartTime.time().hour()));

	cout << "종족전쟁 패킷 보내는 날짜 : " << m_RaceWarTimeParam << endl;

	__END_CATCH
}


void WarSystem::load()
	throw (Error)
{
	__BEGIN_TRY

	// load할거 없다.

	// 진행중인 전쟁을 load해야 한다.

	__END_CATCH
}

VSDateTime WarSystem::getWarEndTime(WarType_t warType) const
{
	int seconds = 0;
	switch (warType)
	{
		// 길드전은 1시간
		case WAR_GUILD :
			seconds = g_pVariableManager->getVariable( GUILD_WAR_TIME );
		break;

		// 종족전은 2시간
		case WAR_RACE :
			seconds = g_pVariableManager->getVariable( RACE_WAR_TIME );
		break;
	}

	VSDateTime dt(VSDateTime::currentDateTime());

	return dt.addSecs( seconds );
}

bool WarSystem::addWarDelayed(War* pWar)
	throw (Error)
{
	__BEGIN_TRY

	Assert(pWar!=NULL);

	if (hasActiveRaceWar() && pWar->getWarType()==WAR_RACE)
	{
		throw Error("이미 종족 전쟁이 진행중입니다.");
	}

	__ENTER_CRITICAL_SECTION(m_MutexWarQueue);

	m_WarQueue.push_back( pWar );

	__LEAVE_CRITICAL_SECTION(m_MutexWarQueue);
	
	return true;

	__END_CATCH
}

bool WarSystem::addQueuedWar()
	throw (Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_MutexWarQueue);

	while (!m_WarQueue.empty())
	{
		War* pWar = m_WarQueue.front();
		Assert(pWar!=NULL);

		m_WarQueue.pop_front();

		addWar( pWar );
	}

	__LEAVE_CRITICAL_SECTION(m_MutexWarQueue);

	return true;
	
	__END_CATCH
}

// WarSystem 안에서만 호출되는 함수이므로 LOCK필요없다.
bool WarSystem::addWar(War* pWar)
	throw (Error)
{
	__BEGIN_TRY

	Assert(pWar!=NULL);
	Assert(pWar->getState()==War::WAR_STATE_CURRENT);

	WarType_t 	warType 	= pWar->getWarType();
	VSDateTime 	warEndTime 	= getWarEndTime( warType );

	Schedule::ScheduleType scheduleType;
	
	scheduleType = Schedule::SCHEDULE_TYPE_ONCE;
		
	WarSchedule* pWarSchedule = new WarSchedule( pWar, warEndTime, scheduleType);

	addSchedule( pWarSchedule );

	// 일단 모든 존에 뿌린다.
	if (makeGCWarList_LOCKED())
	{
		GCWarList gcWarList;

	    __ENTER_CRITICAL_SECTION(m_MutexWarList)

		gcWarList = m_GCWarList;

   	 	__LEAVE_CRITICAL_SECTION(m_MutexWarList)

		g_pZoneGroupManager->broadcast( &gcWarList );
	}

	// 이미 만들어졌다. WarScheduler의 execute에서 tinysave했기 때메 Status바꿀 필요도 없다.
	//pWarSchedule->create();

	// 진행 중인 전쟁 리스트에 추가시켜준다.
	// heartbeat()에서 제거시켜준다.
	if (pWar->getWarType()==WAR_GUILD)
	{
#ifndef __OLD_GUILD_WAR__
		SiegeWar* pSiegeWar = dynamic_cast<SiegeWar*>(pWar);
#else
		GuildWar* pSiegeWar = dynamic_cast<GuildWar*>(pWar);
#endif
		Assert(pSiegeWar!=NULL);

		// 성지에 있는 유저의 상태를 Refresh 해준다.
		EventRefreshHolyLandPlayer* pEvent = new EventRefreshHolyLandPlayer( NULL );
		pEvent->setDeadline( 0 );
		g_pClientManager->addEvent( pEvent );

		__ENTER_CRITICAL_SECTION(m_MutexActiveWars)

		m_ActiveWars.push_back( ActiveWarInfo(pSiegeWar->getCastleZoneID(), pSiegeWar->getChallangerGuildID() ) );

		__LEAVE_CRITICAL_SECTION(m_MutexActiveWars)
	}
	else if (pWar->getWarType()==WAR_RACE)
	{
		m_bHasRaceWar = true;

		// 성지에 있는 유저의 상태를 Refresh 해준다.
		EventRefreshHolyLandPlayer* pEvent = new EventRefreshHolyLandPlayer( NULL );
		pEvent->setDeadline( 0 );
		g_pClientManager->addEvent( pEvent );

		// 아담의 성지 전역에 피의 성서 위치를 보내준다.
		g_pShrineInfoManager->broadcastBloodBibleStatus();

		// 종족 전쟁에 참가하지 않는 사람들을 내보낸다.
		g_pHolyLandManager->remainRaceWarPlayers();
	}

	return true;

	__END_CATCH
}


bool WarSystem::makeGCWarList_LOCKED()
	throw (Error)
{
	__BEGIN_TRY

    __ENTER_CRITICAL_SECTION(m_MutexWarList)

	m_GCWarList.clear();

	if (isEmpty())
	{
		m_MutexWarList.unlock();
		return false;
	}

	const RecentSchedules::container_type& Schedules = m_RecentSchedules.getSchedules();
	RecentSchedules::const_iterator itr = Schedules.begin();

	for (; itr!=Schedules.end(); itr++)
	{
		Schedule* pSchedule = *itr;

		WarSchedule* pWarSchedule = dynamic_cast<WarSchedule*>(pSchedule);
		Assert(pWarSchedule!=NULL);

		War* pWar = pWarSchedule->getWar();
		Assert(pWar!=NULL);

		WarInfo* pWarInfo = NULL;
		
		switch (pWar->getWarType())
		{
			case WAR_GUILD : pWarInfo = new GuildWarInfo; break;
			case WAR_RACE  : pWarInfo = new RaceWarInfo; break;
			default : throw Error("WarType이 잘못됐다.");
		}

		pWarSchedule->makeWarInfo( pWarInfo );

		m_GCWarList.addWarInfo( pWarInfo );
	}

    __LEAVE_CRITICAL_SECTION(m_MutexWarList)

	return true;

	__END_CATCH
}

bool WarSystem::makeGCWarList()
    throw (Error)
{
    __BEGIN_TRY

	bool ret = false;

    __ENTER_CRITICAL_SECTION(m_Mutex)

    ret = makeGCWarList_LOCKED();

    __LEAVE_CRITICAL_SECTION(m_Mutex)

	return ret;

    __END_CATCH

    return false;
}

void WarSystem::sendGCWarList(Player* pPlayer)
    throw (Error)
{
    __BEGIN_TRY

    __ENTER_CRITICAL_SECTION(m_MutexWarList)

	if (!m_GCWarList.isEmpty())
	{
		pPlayer->sendPacket( &m_GCWarList );
		//cout << m_GCWarList.toString().c_str() << endl;
	}

    __LEAVE_CRITICAL_SECTION(m_MutexWarList)

	__END_CATCH
}

Work* WarSystem::heartbeat() 
	throw(Error)
{
    __BEGIN_TRY

	Work* pWork = NULL;

    __ENTER_CRITICAL_SECTION(m_Mutex)

	addQueuedWar();

	Schedule* pSchedule = m_pRaceWarSchedule;
	if ( pSchedule != NULL )
	{
		War* pWar = dynamic_cast<War*>(pSchedule->getWork());
		if ( pWar != NULL && pWar->getWarType() == WAR_RACE )
		{
			int lastSec = VSDateTime::currentDateTime().secsTo( pSchedule->getScheduledTime() );
			// 20분전
			if ( lastSec < 20 * 60 && !m_b20Minutes )
			{
				m_b20Minutes = true;

				// 성지에 있는 유저의 상태를 Refresh 해준다.
				EventRefreshHolyLandPlayer* pEvent = new EventRefreshHolyLandPlayer( NULL );
				pEvent->setDeadline( 0 );
				g_pClientManager->addEvent( pEvent );

				GCNoticeEvent gcNE;
				gcNE.setCode( NOTICE_EVENT_RACE_WAR_IN_20 );
				g_pZoneGroupManager->broadcast( &gcNE );
			}
			else if ( lastSec < 5 * 60 && !m_b5Minutes )
			{
				m_b5Minutes = true;

				GCNoticeEvent gcNE;
				gcNE.setCode( NOTICE_EVENT_RACE_WAR_IN_5 );
				g_pZoneGroupManager->broadcast( &gcNE );
			}
			if ( m_b20Minutes && !g_pVariableManager->isAutoStartRaceWar() )
			{
				if ( lastSec > 20 * 60 ) m_b20Minutes = m_b5Minutes = false;
			}

			if ( lastSec < 0 && !g_pVariableManager->isAutoStartRaceWar() )
			{
				GCNoticeEvent gcNE;
				gcNE.setCode( NOTICE_EVENT_RACE_WAR_STARTED_IN_OTHER_SERVER );
				g_pZoneGroupManager->broadcast( &gcNE );

				VSDateTime warStartTime = WarScheduler::getNextWarDateTime( WAR_RACE, VSDateTime::currentDateTime() );
				dynamic_cast<RaceWar*>(m_pRaceWarSchedule->getWork())->setWarStartTime( warStartTime );
				m_pRaceWarSchedule->setScheduledTime(warStartTime);
			}
		}
	}

	pWork = Scheduler::heartbeat();

	if (pWork!=NULL)
	{
		// 시간이 다 돼서 끝난 전쟁에 대한 처리
		War* pWar = dynamic_cast<War*>(pWork);
		Assert(pWar!=NULL);

		// 대체로는 War::executeEnd()에서 할 것이다.
		if (pWar->getWarType()==WAR_GUILD)
		{
#ifndef __OLD_GUILD_WAR__
			SiegeWar* pSiegeWar = dynamic_cast<SiegeWar*>(pWar);
#else
			GuildWar* pSiegeWar = dynamic_cast<GuildWar*>(pWar);
#endif
			Assert(pSiegeWar!=NULL);

			// 진행 중인 전쟁 리스트에서 제거시켜준다.
			__ENTER_CRITICAL_SECTION(m_MutexActiveWars)

			list<ActiveWarInfo>::iterator itr = find( m_ActiveWars.begin(), 
													m_ActiveWars.end(), 
													ActiveWarInfo( pSiegeWar->getCastleZoneID() ) );
			Assert (itr!=m_ActiveWars.end());

			m_ActiveWars.erase( itr );

			__LEAVE_CRITICAL_SECTION(m_MutexActiveWars)
		}
		else if (pWar->getWarType()==WAR_RACE)
		{
			m_bHasRaceWar = false;

			// 성지에 있는 유저의 상태를 Refresh 해준다.
			EventRefreshHolyLandPlayer* pEvent = new EventRefreshHolyLandPlayer( NULL );
			pEvent->setDeadline( 0 );
			g_pClientManager->addEvent( pEvent );

			m_b20Minutes = false;
		}

		SAFE_DELETE(pWork);
	}

   	// 종족 전쟁을 자동으로 시작 시킨다.
	if (m_pRaceWarSchedule!=NULL
		&& !m_bHasRaceWar
		&& g_pVariableManager->isAutoStartRaceWar())
	{
		checkStartRaceWar();
		m_bRaceWarToday = VSDateTime::currentDateTime().daysTo( m_pRaceWarSchedule->getScheduledTime() ) <= 4;
	}

	// WarList를 갱신해준다.
	static Timeval nextTime = {0,0};
	Timeval currentTime;
	getCurrentTime( currentTime );

	if (currentTime > nextTime)
	{
		makeGCWarList_LOCKED();
		nextTime.tv_sec = currentTime.tv_sec + 10;
	}

	__LEAVE_CRITICAL_SECTION(m_Mutex)

	return pWork;

	__END_CATCH
}

bool
WarSystem::checkStartRaceWar()
	throw (Error)
{
	__BEGIN_TRY

	if (m_pRaceWarSchedule->heartbeat())
	{
		Work* pWork = m_pRaceWarSchedule->popWork();
		Assert(pWork!=NULL);

		War* pRaceWar = dynamic_cast<War*>(pWork);
		addWarDelayed( pRaceWar );

		prepareRaceWar();
		m_b5Minutes = false;

		return true;
	}

	return false;

	__END_CATCH
}

bool WarSystem::getAttackGuildID( ZoneID_t zoneID, GuildID_t& guildID ) const 
	throw(Error)
{
	__BEGIN_TRY
	
	bool bHasCastleActiveWar = false;

    __ENTER_CRITICAL_SECTION(m_MutexActiveWars)

	list<ActiveWarInfo>::const_iterator itr = find( m_ActiveWars.begin(), m_ActiveWars.end(), ActiveWarInfo(zoneID) );

	if (itr!=m_ActiveWars.end())
	{
		bHasCastleActiveWar = true;
		guildID = (*itr).AttackGuildID;
	}

    __LEAVE_CRITICAL_SECTION(m_MutexActiveWars)

	return bHasCastleActiveWar;

	__END_CATCH
}

bool WarSystem::hasCastleActiveWar( ZoneID_t zoneID ) const
	throw(Error)
{
	__BEGIN_TRY
	
	bool bHasCastleActiveWar = false;

    __ENTER_CRITICAL_SECTION(m_MutexActiveWars)

	list<ActiveWarInfo>::const_iterator itr = find( m_ActiveWars.begin(), m_ActiveWars.end(), ActiveWarInfo(zoneID) );

	if (itr!=m_ActiveWars.end())
	{
		bHasCastleActiveWar = true;
	}

    __LEAVE_CRITICAL_SECTION(m_MutexActiveWars)

	/*
	// deadlock(Zone의 EffectHasBloodBible::affect(Item)에서, 딴데도 있겠지만 -_-;) 문제로 인하여
	// 실행중인 전쟁에 대한 리스트를 따로 갖고 처리한다.
    __ENTER_CRITICAL_SECTION(m_Mutex)

	const RecentSchedules::container_type& schedules = m_RecentSchedules.getSchedules();
	RecentSchedules::const_iterator itr = schedules.begin();

	for( ; itr != schedules.end(); itr++ )
	{
		War* pWar = dynamic_cast<War*>( (*itr)->getWork() );
		if( pWar == NULL ) continue;

		if( pWar->getCastleZoneID() == zoneID )
		{
			m_Mutex.unlock();
			return true;
		}
	}

    __LEAVE_CRITICAL_SECTION(m_Mutex)
	*/

	return bHasCastleActiveWar;

	__END_CATCH
}

WarSchedule* WarSystem::getActiveWarSchedule( ZoneID_t zoneID )
	throw(Error)
{
	__BEGIN_TRY

    WarSchedule* pWarSchedule = NULL;

	__ENTER_CRITICAL_SECTION(m_Mutex)

	pWarSchedule =  getActiveWarSchedule_LOCKED( zoneID );

    __LEAVE_CRITICAL_SECTION(m_Mutex)

	return pWarSchedule;

	__END_CATCH
}

 
WarSchedule* WarSystem::getActiveWarSchedule_LOCKED( ZoneID_t zoneID )
	throw(Error)
{
	__BEGIN_TRY

	const RecentSchedules::container_type& schedules = m_RecentSchedules.getSchedules();
	RecentSchedules::const_iterator itr = schedules.begin();

	for( ; itr != schedules.end(); itr++ )
	{
		WarSchedule* pWarSchedule = dynamic_cast<WarSchedule*>(*itr);
		Assert(pWarSchedule!=NULL);

		War* pWar = dynamic_cast<War*>( pWarSchedule->getWork() );
		if( pWar == NULL )
		{
			cout << "WarSystem에 들어있는 Schedule의 Work객체가 War가 아니거나 NULL입니다. 삽질삽질~~~~" << endl;
			continue;
		}

		if (pWar->getWarType()==WAR_GUILD)
		{
#ifndef __OLD_GUILD_WAR__
			SiegeWar* pSiegeWar = dynamic_cast<SiegeWar*>(pWar);
#else
			GuildWar* pSiegeWar = dynamic_cast<GuildWar*>(pWar);
#endif
			Assert(pSiegeWar!=NULL);

			if( pSiegeWar->getCastleZoneID() == zoneID )
			{
				return pWarSchedule;
			}
		}
	}

	return NULL;

	__END_CATCH
}

War* WarSystem::getActiveWar( ZoneID_t zoneID ) const
	throw(Error)
{
	__BEGIN_TRY

    __ENTER_CRITICAL_SECTION(m_Mutex)

	const RecentSchedules::container_type& schedules = m_RecentSchedules.getSchedules();
	RecentSchedules::const_iterator itr = schedules.begin();

	for( ; itr != schedules.end(); itr++ )
	{
		War* pWar = dynamic_cast<War*>( (*itr)->getWork() );
		if( pWar == NULL ) continue;

		if (pWar->getWarType()==WAR_GUILD)
		{
#ifndef __OLD_GUILD_WAR__
			SiegeWar* pSiegeWar = dynamic_cast<SiegeWar*>(pWar);
#else
			GuildWar* pSiegeWar = dynamic_cast<GuildWar*>(pWar);
#endif
			Assert(pSiegeWar!=NULL);

			if( pSiegeWar->getCastleZoneID() == zoneID )
			{
				m_Mutex.unlock();
				return pWar;
			}
		}
	}

    __LEAVE_CRITICAL_SECTION(m_Mutex)

	return NULL;

	__END_CATCH
}

bool    WarSystem::isEndCondition(Item* pItem, MonsterCorpse* pMonsterCorpse) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pItem!=NULL);
	Assert(pMonsterCorpse!=NULL);

	// pItem과 pMonsterCorpse의 짝이 맞는가?
	// return pBloodBibleItem->getBibleMonsterType()==pMonsterCorpse->getMonter()->getMonsterType()

	return true;

	__END_CATCH
}

bool	WarSystem::isModifyCastleOwner( ZoneID_t castleZoneID, PlayerCreature* pPC )
	throw (Error)
{
	__BEGIN_TRY

	War* pWar = getActiveWar( castleZoneID );
	Assert(pWar!=NULL);

	return pWar->isModifyCastleOwner(pPC);

	__END_CATCH
}

// pPC가 castleZoneID와 관련된 전쟁에 승리했다.
bool    WarSystem::endWar(PlayerCreature* pPC, ZoneID_t castleZoneID) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pPC!=NULL);

	bool bEndWar = false;

    __ENTER_CRITICAL_SECTION(m_Mutex)

	WarSchedule* pWarSchedule = getActiveWarSchedule_LOCKED( castleZoneID );

	if (pWarSchedule!=NULL)
	{
		Work* pWork = pWarSchedule->getWork();
		Assert(pWork!=NULL);

		War* pWar = dynamic_cast<War*>(pWork);
		Assert(pWar!=NULL);

		if (pWar->endWar(pPC))
		{
			// 전쟁 제거( 시간 수정으로 자동으로 빠지도록 하자)
			pWarSchedule->setScheduledTime( VSDateTime::currentDateTime() );

			// heap을 다시 구성해야 한다.
			m_RecentSchedules.arrange();

			bEndWar = true;
		}
	}

    __LEAVE_CRITICAL_SECTION(m_Mutex)

	return bEndWar;

	__END_CATCH
}

// castleZoneID의 진행중인 전쟁을 제거한다.
bool    WarSystem::removeWar(ZoneID_t castleZoneID) 
	throw (Error)
{
	__BEGIN_TRY

	bool bRemoved = false;

    __ENTER_CRITICAL_SECTION(m_Mutex)

	WarSchedule* pWarSchedule = getActiveWarSchedule_LOCKED( castleZoneID );

	if (pWarSchedule!=NULL)
	{
		// 전쟁 제거( 시간 수정으로 자동으로 빠지도록 하자)
		pWarSchedule->setScheduledTime( VSDateTime::currentDateTime() );

		// heap을 다시 구성해야 한다.
		m_RecentSchedules.arrange();

		bRemoved = true;
	}

    __LEAVE_CRITICAL_SECTION(m_Mutex)

	return bRemoved;

	__END_CATCH
}

// castleZoneID의 진행중인 전쟁을 제거한다.
bool    WarSystem::removeRaceWar()
	throw (Error)
{
	__BEGIN_TRY

	bool bRemoved = false;

    __ENTER_CRITICAL_SECTION(m_Mutex)

	const RecentSchedules::container_type& schedules = m_RecentSchedules.getSchedules();
	RecentSchedules::const_iterator itr = schedules.begin();

	for( ; itr != schedules.end(); itr++ )
	{
		Schedule* pSchedule = *itr;
		War* pWar = dynamic_cast<War*>( pSchedule->getWork() );
		if( pWar == NULL ) continue;

		if( pWar->getWarType() == WAR_RACE )
		{
			// 전쟁 제거( 시간 수정으로 자동으로 빠지도록 하자)
			pSchedule->setScheduledTime( VSDateTime::currentDateTime() );

			// heap을 다시 구성해야 한다.
			m_RecentSchedules.arrange();
			
			bRemoved = true;
		}
	}

    __LEAVE_CRITICAL_SECTION(m_Mutex)

	return bRemoved;

	__END_CATCH
}

// 특정한 플레이어에게 현재 진행중인 전쟁의 리스트를 보내준다.
void WarSystem::broadcastWarList( GamePlayer* pGamePlayer ) const
	throw (Error)
{
	__BEGIN_TRY

    __ENTER_CRITICAL_SECTION(m_Mutex)

	const RecentSchedules::container_type& schedules = m_RecentSchedules.getSchedules();
	RecentSchedules::const_iterator itr = schedules.begin();

	GCSystemMessage gcSystemMessage;
	bool warExist = false;

	if ( isEmpty() ) 
	{
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NO_WAR_IN_ACTIVE ) );
		pGamePlayer->sendPacket( &gcSystemMessage );

		m_Mutex.unlock();
		return;
	}

	for( ; itr != schedules.end(); itr++ )
	{
		WarSchedule* pSchedule = dynamic_cast<WarSchedule*>( *itr );
		if( pSchedule == NULL ) continue;

		War* pWar = dynamic_cast<War*>( pSchedule->getWork() );
		if( pWar == NULL ) continue;

		warExist = true;

/*		StringStream msg;
		msg << pWar->getWarName() << "이 "
			<< ( pSchedule->getScheduledTime() ).toString() << " 까지 진행됩니다.";
*/

		char msg[100];
		sprintf( msg, g_pStringPool->c_str( STRID_WAR_STATUS ),
						pWar->getWarName().c_str(), ( pSchedule->getScheduledTime() ).toString().c_str() );
		gcSystemMessage.setMessage( msg );
		pGamePlayer->sendPacket( &gcSystemMessage );
	}

	if ( !warExist ) 
	{
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NO_WAR_IN_ACTIVE ) );
		pGamePlayer->sendPacket( &gcSystemMessage );
	}

    __LEAVE_CRITICAL_SECTION(m_Mutex)

	__END_CATCH
}

War* WarSystem::getActiveRaceWar() const
	throw(Error)
{
	__BEGIN_TRY

	War* pWar = NULL;

	__ENTER_CRITICAL_SECTION( m_Mutex )

	pWar = getActiveRaceWarAtSameThread();

	__LEAVE_CRITICAL_SECTION( m_Mutex )

	return pWar;

	__END_CATCH
}

bool WarSystem::startRaceWar()
	throw(Error)
{
	__BEGIN_TRY

	if ( hasActiveRaceWar() ) return false;

	__ENTER_CRITICAL_SECTION( m_Mutex );

	if (m_pRaceWarSchedule!=NULL)
	{
		if ( m_b5Minutes )
		{
			m_pRaceWarSchedule->setScheduledTime( VSDateTime::currentDateTime() );
		}
		else if ( m_b20Minutes )
		{
			m_pRaceWarSchedule->setScheduledTime( VSDateTime::currentDateTime().addSecs(60*5) );
		}
		else
		{
			m_pRaceWarSchedule->setScheduledTime( VSDateTime::currentDateTime().addSecs(60*20) );
		}

		checkStartRaceWar();
	}

	__LEAVE_CRITICAL_SECTION( m_Mutex );

	return true;
	
	__END_CATCH
}

War* WarSystem::getActiveRaceWarAtSameThread() const
	throw(Error)
{
	__BEGIN_TRY

	const RecentSchedules::container_type& schedules = m_RecentSchedules.getSchedules();
	RecentSchedules::const_iterator itr = schedules.begin();

	for( ; itr != schedules.end(); itr++ )
	{
		War* pWar = dynamic_cast<War*>( (*itr)->getWork() );
		if( pWar == NULL ) continue;
		if( pWar->getWarType() == WAR_RACE )
		{
			return pWar;
		}
	}

	return NULL;

	__END_CATCH
}

bool    WarSystem::addRaceWarScheduleInfo(WarScheduleInfo* pWSI) 
	throw (Error)
{
	__BEGIN_TRY

	if (m_pRaceWarSchedule==NULL) return false;

	Assert(pWSI!=NULL);

	__ENTER_CRITICAL_SECTION( m_Mutex );

	const VSDateTime& DT = m_pRaceWarSchedule->getScheduledTime();

	Work* pWork = m_pRaceWarSchedule->getWork();
	Assert(pWork!=NULL);

	War* pWar = dynamic_cast<War*>(pWork);
	Assert(pWar!=NULL);

	pWar->makeWarScheduleInfo( pWSI );
	pWSI->year    = DT.date().year();
	pWSI->month   = DT.date().month();
	pWSI->day     = DT.date().day();
	pWSI->hour    = DT.time().hour();

	__LEAVE_CRITICAL_SECTION( m_Mutex );

	return true;

	__END_CATCH
}
