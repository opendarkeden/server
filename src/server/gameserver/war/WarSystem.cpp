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
#include "GCSystemMessage.h"
#include "GCWarList.h"
#include "GCWarScheduleList.h"
#include "GCNoticeEvent.h"
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
{
	SAFE_DELETE(m_pRaceWarSchedule);
}

void WarSystem::init()
{
	__BEGIN_TRY

	load();

	prepareRaceWar();

	__END_CATCH
}

void WarSystem::prepareRaceWar()
{
	__BEGIN_TRY

	SAFE_DELETE(m_pRaceWarSchedule);

	// ���� ������ �غ��صд�.
	VSDateTime warStartTime = WarScheduler::getNextWarDateTime( WAR_RACE, VSDateTime::currentDateTime() );

	War* pRaceWar 		= new RaceWar( War::WAR_STATE_WAIT );
	pRaceWar->setWarStartTime( warStartTime );
	m_pRaceWarSchedule 	= new Schedule( pRaceWar, warStartTime );

	filelog("WarLog.txt", "[WarID=%d,Time=%s] ���� ������ �߰��մϴ�.", (int)pRaceWar->getWarID(), warStartTime.toString().c_str());

//	m_RaceWarTimeParam = ((DWORD)((DWORD)warStartTime.date().month() << 24)) | ((DWORD)((DWORD)warStartTime.date().day() << 16)) | ((DWORD)((DWORD)warStartTime.time().hour() << 8));
	VSDateTime sendStartTime = warStartTime.addDays(-7);
	m_RaceWarTimeParam = ((DWORD)((DWORD)(sendStartTime.date().year() - 2000))*1000000) + ((DWORD)((DWORD)sendStartTime.date().month())*10000)
					   + ((DWORD)((DWORD)sendStartTime.date().day())*100);//	   + ((DWORD)((DWORD)sendStartTime.time().hour()));

	cout << "�������� ��Ŷ ������ ��¥ : " << m_RaceWarTimeParam << endl;

	__END_CATCH
}


void WarSystem::load()
	
{
	__BEGIN_TRY

	// load�Ұ� ����.

	// �������� ������ load�ؾ� �Ѵ�.

	__END_CATCH
}

VSDateTime WarSystem::getWarEndTime(WarType_t warType) const
{
	int seconds = 0;
	switch (warType)
	{
		// ������� 1�ð�
		case WAR_GUILD :
			seconds = g_pVariableManager->getVariable( GUILD_WAR_TIME );
		break;

		// �������� 2�ð�
		case WAR_RACE :
			seconds = g_pVariableManager->getVariable( RACE_WAR_TIME );
		break;
	}

	VSDateTime dt(VSDateTime::currentDateTime());

	return dt.addSecs( seconds );
}

bool WarSystem::addWarDelayed(War* pWar)
	
{
	__BEGIN_TRY

	Assert(pWar!=NULL);

	if (hasActiveRaceWar() && pWar->getWarType()==WAR_RACE)
	{
		throw Error("�̹� ���� ������ �������Դϴ�.");
	}

	__ENTER_CRITICAL_SECTION(m_MutexWarQueue);

	m_WarQueue.push_back( pWar );

	__LEAVE_CRITICAL_SECTION(m_MutexWarQueue);
	
	return true;

	__END_CATCH
}

bool WarSystem::addQueuedWar()
	
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

// WarSystem �ȿ����� ȣ��Ǵ� �Լ��̹Ƿ� LOCK�ʿ����.
bool WarSystem::addWar(War* pWar)
	
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

	// �ϴ� ��� ���� �Ѹ���.
	if (makeGCWarList_LOCKED())
	{
		GCWarList gcWarList;

	    __ENTER_CRITICAL_SECTION(m_MutexWarList)

		gcWarList = m_GCWarList;

   	 	__LEAVE_CRITICAL_SECTION(m_MutexWarList)

		g_pZoneGroupManager->broadcast( &gcWarList );
	}

	// �̹� ���������. WarScheduler�� execute���� tinysave�߱� ���� Status�ٲ� �ʿ䵵 ����.
	//pWarSchedule->create();

	// ���� ���� ���� ����Ʈ�� �߰������ش�.
	// heartbeat()���� ���Ž����ش�.
	if (pWar->getWarType()==WAR_GUILD)
	{
#ifndef __OLD_GUILD_WAR__
		SiegeWar* pSiegeWar = dynamic_cast<SiegeWar*>(pWar);
#else
		GuildWar* pSiegeWar = dynamic_cast<GuildWar*>(pWar);
#endif
		Assert(pSiegeWar!=NULL);

		// ������ �ִ� ������ ���¸� Refresh ���ش�.
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

		// ������ �ִ� ������ ���¸� Refresh ���ش�.
		EventRefreshHolyLandPlayer* pEvent = new EventRefreshHolyLandPlayer( NULL );
		pEvent->setDeadline( 0 );
		g_pClientManager->addEvent( pEvent );

		// �ƴ��� ���� ������ ���� ���� ��ġ�� �����ش�.
		g_pShrineInfoManager->broadcastBloodBibleStatus();

		// ���� ���￡ �������� �ʴ� ������� ��������.
		g_pHolyLandManager->remainRaceWarPlayers();
	}

	return true;

	__END_CATCH
}


bool WarSystem::makeGCWarList_LOCKED()
	
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
			default : throw Error("WarType�� �߸��ƴ�.");
		}

		pWarSchedule->makeWarInfo( pWarInfo );

		m_GCWarList.addWarInfo( pWarInfo );
	}

    __LEAVE_CRITICAL_SECTION(m_MutexWarList)

	return true;

	__END_CATCH
}

bool WarSystem::makeGCWarList()
    
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
			// 20����
			if ( lastSec < 20 * 60 && !m_b20Minutes )
			{
				m_b20Minutes = true;

				// ������ �ִ� ������ ���¸� Refresh ���ش�.
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
		// �ð��� �� �ż� ���� ���￡ ���� ó��
		War* pWar = dynamic_cast<War*>(pWork);
		Assert(pWar!=NULL);

		// ��ü�δ� War::executeEnd()���� �� ���̴�.
		if (pWar->getWarType()==WAR_GUILD)
		{
#ifndef __OLD_GUILD_WAR__
			SiegeWar* pSiegeWar = dynamic_cast<SiegeWar*>(pWar);
#else
			GuildWar* pSiegeWar = dynamic_cast<GuildWar*>(pWar);
#endif
			Assert(pSiegeWar!=NULL);

			// ���� ���� ���� ����Ʈ���� ���Ž����ش�.
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

			// ������ �ִ� ������ ���¸� Refresh ���ش�.
			EventRefreshHolyLandPlayer* pEvent = new EventRefreshHolyLandPlayer( NULL );
			pEvent->setDeadline( 0 );
			g_pClientManager->addEvent( pEvent );

			m_b20Minutes = false;
		}

		SAFE_DELETE(pWork);
	}

   	// ���� ������ �ڵ����� ���� ��Ų��.
	if (m_pRaceWarSchedule!=NULL
		&& !m_bHasRaceWar
		&& g_pVariableManager->isAutoStartRaceWar())
	{
		checkStartRaceWar();
		m_bRaceWarToday = VSDateTime::currentDateTime().daysTo( m_pRaceWarSchedule->getScheduledTime() ) <= 4;
	}

	// WarList�� �������ش�.
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
	// deadlock(Zone�� EffectHasBloodBible::affect(Item)����, ������ �ְ����� -_-;) ������ ���Ͽ�
	// �������� ���￡ ���� ����Ʈ�� ���� ���� ó���Ѵ�.
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
			cout << "WarSystem�� ����ִ� Schedule�� Work��ü�� War�� �ƴϰų� NULL�Դϴ�. ��������~~~~" << endl;
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
	
{
	__BEGIN_TRY

	Assert(pItem!=NULL);
	Assert(pMonsterCorpse!=NULL);

	// pItem�� pMonsterCorpse�� ¦�� �´°�?
	// return pBloodBibleItem->getBibleMonsterType()==pMonsterCorpse->getMonter()->getMonsterType()

	return true;

	__END_CATCH
}

bool	WarSystem::isModifyCastleOwner( ZoneID_t castleZoneID, PlayerCreature* pPC )
	
{
	__BEGIN_TRY

	War* pWar = getActiveWar( castleZoneID );
	Assert(pWar!=NULL);

	return pWar->isModifyCastleOwner(pPC);

	__END_CATCH
}

// pPC�� castleZoneID�� ���õ� ���￡ �¸��ߴ�.
bool    WarSystem::endWar(PlayerCreature* pPC, ZoneID_t castleZoneID) 
	
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
			// ���� ����( �ð� �������� �ڵ����� �������� ����)
			pWarSchedule->setScheduledTime( VSDateTime::currentDateTime() );

			// heap�� �ٽ� �����ؾ� �Ѵ�.
			m_RecentSchedules.arrange();

			bEndWar = true;
		}
	}

    __LEAVE_CRITICAL_SECTION(m_Mutex)

	return bEndWar;

	__END_CATCH
}

// castleZoneID�� �������� ������ �����Ѵ�.
bool    WarSystem::removeWar(ZoneID_t castleZoneID) 
	
{
	__BEGIN_TRY

	bool bRemoved = false;

    __ENTER_CRITICAL_SECTION(m_Mutex)

	WarSchedule* pWarSchedule = getActiveWarSchedule_LOCKED( castleZoneID );

	if (pWarSchedule!=NULL)
	{
		// ���� ����( �ð� �������� �ڵ����� �������� ����)
		pWarSchedule->setScheduledTime( VSDateTime::currentDateTime() );

		// heap�� �ٽ� �����ؾ� �Ѵ�.
		m_RecentSchedules.arrange();

		bRemoved = true;
	}

    __LEAVE_CRITICAL_SECTION(m_Mutex)

	return bRemoved;

	__END_CATCH
}

// castleZoneID�� �������� ������ �����Ѵ�.
bool    WarSystem::removeRaceWar()
	
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
			// ���� ����( �ð� �������� �ڵ����� �������� ����)
			pSchedule->setScheduledTime( VSDateTime::currentDateTime() );

			// heap�� �ٽ� �����ؾ� �Ѵ�.
			m_RecentSchedules.arrange();
			
			bRemoved = true;
		}
	}

    __LEAVE_CRITICAL_SECTION(m_Mutex)

	return bRemoved;

	__END_CATCH
}

// Ư���� �÷��̾�� ���� �������� ������ ����Ʈ�� �����ش�.
void WarSystem::broadcastWarList( GamePlayer* pGamePlayer ) const
	
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
		msg << pWar->getWarName() << "�� "
			<< ( pSchedule->getScheduledTime() ).toString() << " ���� ����˴ϴ�.";
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
