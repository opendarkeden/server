#include "GDRLairManager.h"
#include "ZoneUtil.h"
#include "Zone.h"
#include "EffectCastingTrap.h"
#include "Monster.h"
#include "MonsterAI.h"
#include "MonsterInfo.h"
#include "MonsterManager.h"
#include "Gpackets/GCNoticeEvent.h"
#include "Gpackets/GCSystemMessage.h"
#include "EffectKickOut.h"
#include "ZoneGroupManager.h"
#include "PacketUtil.h"
#include "ItemFactoryManager.h"
#include "Gpackets/GCCreateItem.h"
#include "PlayerCreature.h"
#include "Inventory.h"
#include "ItemUtil.h"
#include "Player.h"
#include "EffectGDRLairClose.h"
#include "VariableManager.h"
#include <cmath>
#include <cstdio>

#include "SXml.h"
#include "DB.h"
#include "Properties.h"

void GDRLairManager::init()
{
	cout << "Init GDR Lair Manager" << endl;

	m_pGDR = NULL;

	m_pZones[ILLUSIONS_WAY_1] = getZoneByZoneID(1410);
	m_pZones[ILLUSIONS_WAY_2] = getZoneByZoneID(1411);
	m_pZones[GDR_LAIR] = getZoneByZoneID(1412);
	m_pZones[GDR_LAIR_CORE] = getZoneByZoneID(1413);

	FlyweightStateFactory* pFactory = new FlyweightStateFactory();

	pFactory->registerState( new GDRLairIdle(getNextOpenTime()) );
	pFactory->registerState( new GDRLairEntrance() );
//	pFactory->registerState( new GDRLairIllusionsWayOnly() );
	pFactory->registerState( new GDRLairIcepole() );
	pFactory->registerState( new GDRLairScene1() );
	pFactory->registerState( new GDRLairSummonMonster() );
	pFactory->registerState( new GDRLairScene2() );
	pFactory->registerState( new GDRLairSummonGDRDup() );
	pFactory->registerState( new GDRLairScene3() );
	pFactory->registerState( new GDRLairGDRFight() );
	pFactory->registerState( new GDRLairScene4() );
	pFactory->registerState( new GDRLairAwakenedGDRFight() );
	pFactory->registerState( new GDRLairScene5() );
	pFactory->registerState( new GDRLairMinionFight() );
	pFactory->registerState( new GDRLairScene6() );
	pFactory->registerState( new GDRLairEnding() );
	pFactory->registerState( new GDRLairKillAll() );

	m_pStateFactory = pFactory;
	m_pCurrentState = m_pStateFactory->makeState( GDR_LAIR_IDLE );
	m_pCurrentState->start();

	m_ResetState = GDR_LAIR_IDLE;
	m_bCanEnter = false;
}

void GDRLairManager::run() throw()
{
	string host     = g_pConfig->getProperty("DB_HOST");
	string db       = g_pConfig->getProperty("DB_DB");
	string user     = g_pConfig->getProperty("DB_USER");
	string password = g_pConfig->getProperty("DB_PASSWORD");
	uint port		= 0;
	if ( g_pConfig->hasKey("DB_PORT") )
		port = g_pConfig->getPropertyInt("DB_PORT");

	Connection* pConnection = new Connection(host, db, user, password, port);
	g_pDatabaseManager->addConnection((int)Thread::self(), pConnection);
	cout << "******************************************************" << endl;
	cout << " GDR Lair THREAD CONNECT DB " << endl;
	cout << "******************************************************" << endl;

	Timeval dummyQueryTime;
	getCurrentTime( dummyQueryTime );

	while ( true )
	{
		Timeval currentTime;
		getCurrentTime( currentTime );

		heartbeat(currentTime);

		////////////////////////////////////////////////////////
		// dummy query
		////////////////////////////////////////////////////////
		if ( dummyQueryTime < currentTime )
		{
			g_pDatabaseManager->executeDummyQuery( pConnection );

			dummyQueryTime.tv_sec += ( 60 + rand() % 30 ) * 60;
		}

		usleep(100);
	}
}

VSDateTime GDRLairManager::getNextOpenTime() const
{
	static int OpenTime[4] = { 01, 14, 19, 23 };
	VSDateTime ret = VSDateTime::currentDateTime();
	VSTime time = ret.time();
/*	if ( time.setHMS(time.hour(), 0, 0) )
	{
		ret.setTime(time);
	}
*/
	int i;
	for ( i=0; i<4; ++i )
	{
		if ( time.hour() < OpenTime[i] ) break;
	}

	if ( i == 4 )
	{
		cout << "다음날로 넘어갑니다." << endl;
		ret = ret.addDays(1);
		i=0;
	}

	// 수,일요일엔 19시타임 없음
	if ( ( ret.date().dayOfWeek() == 7 || ret.date().dayOfWeek() == 3 ) && i==2) ++i;

	time.setHMS(OpenTime[i], 0, 0);
	ret.setTime(time);

/*	if ( time.hour()%2 )
		ret = ret.addSecs(3600);
	else
		ret = ret.addSecs(7200);*/

	cout << ret.toString() << "에 질드레 레어 다시 시작" << endl;
	filelog( "GDRLair.log", "%s 에 질드레 레어 다시 시작", ret.toString().c_str() );

	return ret;
}

void GDRLairIdle::start()
{
	filelog( "GDRLair.log", "Starting GDR Lair Idle State : %d", GDRLairManager::Instance().getTotalPCs() );

	Monster* pGDR = GDRLairManager::Instance().getGDR();
	if ( pGDR != NULL )
	{
		pGDR->removeFlag( Effect::EFFECT_CLASS_NO_DAMAGE );
		pGDR->setHP(0);
		GDRLairManager::Instance().setGDR(NULL);
	}

	for ( int i=GDRLairManager::ILLUSIONS_WAY_1 ; i < GDRLairManager::GDR_LAIR_MAX ; ++i )
	{
		Zone* pZone = GDRLairManager::Instance().getZone(i);
		if ( pZone != NULL )
		{
			__ENTER_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )
			pZone->getPCManager()->transportAllCreatures(0xffff);
			pZone->killAllMonsters_UNLOCK();
			pZone->deleteEffect_LOCKING(0);
			__LEAVE_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )
		}
	}

	setTimer( GDRLairManager::Instance().getNextOpenTime() );
	SetTimeState::start();
}

void GDRLairEntrance::start()
{
	TimerState::start();

	GCSystemMessage gcSM;
	gcSM.setMessage("훑댐흩契묵綠역폘.");
	g_pZoneGroupManager->broadcast( &gcSM );

	cout << "Starting GDR Lair Enter State" << endl;
	filelog( "GDRLair.log", "Starting GDR Lair Enter State : %d", GDRLairManager::Instance().getTotalPCs() );

	GDRLairManager::Instance().setCorrectPortal( (rand()%3) );
	cout << "맞는 포탈 : " << (int)GDRLairManager::Instance().getCorrectPortal() << endl;
	filelog( "GDRLair.log", "맞는 포탈 : %d", GDRLairManager::Instance().getCorrectPortal() );

	Zone* pIllusionsWay1 = getZoneByZoneID(1410);
	Zone* pIllusionsWay2 = getZoneByZoneID(1411);

	EffectKickOut* pEffectKickOut1 = new EffectKickOut( pIllusionsWay1, 20 );
//	pEffectKickOut1->setDeadline(12000);

	EffectKickOut* pEffectKickOut2 = new EffectKickOut( pIllusionsWay2, 20 );
//	pEffectKickOut2->setDeadline(12000);

	pIllusionsWay1->addEffect_LOCKING( pEffectKickOut1 );
	pIllusionsWay2->addEffect_LOCKING( pEffectKickOut2 );

	Zone* pLair = GDRLairManager::Instance().getZone( GDRLairManager::GDR_LAIR );
	Zone* pCore = GDRLairManager::Instance().getZone( GDRLairManager::GDR_LAIR_CORE );
	pEffectKickOut1 = new EffectKickOut( pLair, 115 );
	pEffectKickOut2 = new EffectKickOut( pCore, 115 );

	pLair->addEffect_LOCKING( pEffectKickOut1 );
	pCore->addEffect_LOCKING( pEffectKickOut2 );

	// 레어를 연다.
	cout << "질드레 레어를 엽니다." << endl;
	GDRLairManager::Instance().open();

	EffectGDRLairClose* pEffectClose = new EffectGDRLairClose(20);
//	// 5분
//	pEffectClose->setDeadline(3000);
	pIllusionsWay1->addEffect_LOCKING( pEffectClose );

	{
		EffectCastingIcicleTrap* pEffect = new EffectCastingIcicleTrap( Effect::EFFECT_CLASS_ICICLE_AUGER, pIllusionsWay1 );

		pEffect->setStartXY( 116, 66 );
		pEffect->setLength( 48 );
		pEffect->setTick( 5 );
		pEffect->setUnit( 6 );
		pEffect->setDir( 7 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay1->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingIcicleTrap* pEffect = new EffectCastingIcicleTrap( Effect::EFFECT_CLASS_ICICLE_AUGER, pIllusionsWay1 );

		pEffect->setStartXY( 63, 19 );
		pEffect->setLength( 48 );
		pEffect->setTick( 5 );
		pEffect->setUnit( 6 );
		pEffect->setDir( 1 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay1->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingIcicleTrap* pEffect = new EffectCastingIcicleTrap( Effect::EFFECT_CLASS_ICICLE_AUGER_LARGE, pIllusionsWay1 );

		pEffect->setStartXY( 15, 72 );
		pEffect->setLength( 47 );
		pEffect->setTick( 10 );
		pEffect->setUnit( 7 );
		pEffect->setDir( 3 );
		pEffect->setLarge( true );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay1->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingIcicleTrap* pEffect = new EffectCastingIcicleTrap( Effect::EFFECT_CLASS_ICICLE_AUGER_LARGE, pIllusionsWay1 );

		pEffect->setStartXY( 68, 119 );
		pEffect->setLength( 27 );
		pEffect->setTick( 10 );
		pEffect->setUnit( 5 );
		pEffect->setDir( 5 );
		pEffect->setLarge( true );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay1->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingSideTrap* pEffect = new EffectCastingSideTrap( pIllusionsWay1 );

		pEffect->setStartXY( 96, 84 );
		pEffect->setLength( 27 );
		pEffect->setTick( 20 );
		pEffect->setUnit( 2 );
		pEffect->setDir( 7 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay1->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingSideTrap* pEffect = new EffectCastingSideTrap( pIllusionsWay1 );

		pEffect->setStartXY( 60, 56 );
		pEffect->setLength( 10 );
		pEffect->setTick( 30 );
		pEffect->setUnit( 1 );
		pEffect->setDir( 1 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay1->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingSideTrap* pEffect = new EffectCastingSideTrap( pIllusionsWay1 );

		pEffect->setStartXY( 51, 73 );
		pEffect->setLength( 10 );
		pEffect->setTick( 30 );
		pEffect->setUnit( 1 );
		pEffect->setDir( 3 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay1->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingIcicleTrap* pEffect = new EffectCastingIcicleTrap( Effect::EFFECT_CLASS_ICICLE_DROP, pIllusionsWay2 );

		pEffect->setStartXY( 123, 57 );
		pEffect->setLength( 43 );
		pEffect->setTick( 10 );
		pEffect->setUnit( 10 );
		pEffect->setDir( 7 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay2->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingIcicleTrap* pEffect = new EffectCastingIcicleTrap( Effect::EFFECT_CLASS_ICICLE_DROP, pIllusionsWay2 );

		pEffect->setStartXY( 61, 32 );
		pEffect->setLength( 43 );
		pEffect->setTick( 10 );
		pEffect->setUnit( 10 );
		pEffect->setDir( 3 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay2->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingIcicleTrap* pEffect = new EffectCastingIcicleTrap( Effect::EFFECT_CLASS_ICICLE_AUGER_LARGE, pIllusionsWay2 );

		pEffect->setStartXY( 91, 97 );
		pEffect->setLength( 43 );
		pEffect->setTick( 10 );
		pEffect->setUnit( 2 );
		pEffect->setDir( 7 );
		pEffect->setLarge(true);
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay2->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingSideTrap* pEffect = new EffectCastingSideTrap( pIllusionsWay2 );

		pEffect->setStartXY( 33, 75 );
		pEffect->setLength( 35 );
		pEffect->setTick( 15 );
		pEffect->setUnit( 2 );
		pEffect->setDir( 3 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay2->addEffect_LOCKING( pEffect );
	}

/*	{
		EffectCastingSideTrap* pEffect = new EffectCastingSideTrap( pIllusionsWay2 );

		pEffect->setStartXY( 25, 67 );
		pEffect->setLength( 43 );
		pEffect->setTick( 10 );
		pEffect->setUnit( 5 );
		pEffect->setDir( 3 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay2->addEffect_LOCKING( pEffect );
	}*/

	{
		EffectCastingSideTrap* pEffect = new EffectCastingSideTrap( pIllusionsWay2 );

		pEffect->setStartXY( 49, 127 );
		pEffect->setLength( 30 );
		pEffect->setTick( 20 );
		pEffect->setUnit( 2 );
		pEffect->setDir( 7 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay2->addEffect_LOCKING( pEffect );
	}
/*	{
		EffectCastingIcicleTrap* pEffect = new EffectCastingIcicleTrap( Effect::EFFECT_CLASS_ICICLE_DROP, pIllusionsWay1 );

		pEffect->setStartXY( 116, 66 );
		pEffect->setLength( 48 );
		pEffect->setTick( 5 );
		pEffect->setUnit( 10 );
		pEffect->setDir( 7 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay1->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingIceWall* pEffect = new EffectCastingIceWall( pIllusionsWay1 );

		pEffect->setStartXY( 63, 19 );
		pEffect->setLength( 48 );
		pEffect->setWallLength( 5 );
		pEffect->setTick( 15 );
		pEffect->setDir( 1 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay1->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingIceWall* pEffect = new EffectCastingIceWall( pIllusionsWay1 );

		pEffect->setStartXY( 15, 72 );
		pEffect->setLength( 47 );
		pEffect->setWallLength( 5 );
		pEffect->setTick( 15 );
		pEffect->setDir( 3 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay1->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingSideTrap* pEffect = new EffectCastingSideTrap( pIllusionsWay1 );

		pEffect->setStartXY( 68, 119 );
		pEffect->setLength( 27 );
		pEffect->setTick( 10 );
		pEffect->setUnit( 5 );
		pEffect->setDir( 5 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay1->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingSideTrap* pEffect = new EffectCastingSideTrap( pIllusionsWay1 );

		pEffect->setStartXY( 96, 84 );
		pEffect->setLength( 27 );
		pEffect->setTick( 10 );
		pEffect->setUnit( 5 );
		pEffect->setDir( 7 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay1->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingSideTrap* pEffect = new EffectCastingSideTrap( pIllusionsWay1 );

		pEffect->setStartXY( 60, 56 );
		pEffect->setLength( 10 );
		pEffect->setTick( 10 );
		pEffect->setUnit( 5 );
		pEffect->setDir( 1 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay1->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingSideTrap* pEffect = new EffectCastingSideTrap( pIllusionsWay1 );

		pEffect->setStartXY( 51, 73 );
		pEffect->setLength( 10 );
		pEffect->setTick( 10 );
		pEffect->setUnit( 5 );
		pEffect->setDir( 3 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay1->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingIcicleTrap* pEffect = new EffectCastingIcicleTrap( Effect::EFFECT_CLASS_ICICLE_AUGER, pIllusionsWay2 );

		pEffect->setStartXY( 123, 57 );
		pEffect->setLength( 43 );
		pEffect->setTick( 5 );
		pEffect->setUnit( 10 );
		pEffect->setDir( 7 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay2->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingIcicleTrap* pEffect = new EffectCastingIcicleTrap( Effect::EFFECT_CLASS_ICICLE_AUGER_LARGE, pIllusionsWay2 );

		pEffect->setStartXY( 61, 32 );
		pEffect->setLength( 43 );
		pEffect->setTick( 10 );
		pEffect->setUnit( 15 );
		pEffect->setDir( 3 );
		pEffect->setLarge(true);
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay2->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingIcicleTrap* pEffect = new EffectCastingIcicleTrap( Effect::EFFECT_CLASS_ICICLE_AUGER_LARGE, pIllusionsWay2 );

		pEffect->setStartXY( 91, 97 );
		pEffect->setLength( 43 );
		pEffect->setTick( 10 );
		pEffect->setUnit( 15 );
		pEffect->setDir( 7 );
		pEffect->setLarge(true);
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay2->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingSideTrap* pEffect = new EffectCastingSideTrap( pIllusionsWay2 );

		pEffect->setStartXY( 25, 67 );
		pEffect->setLength( 43 );
		pEffect->setTick( 10 );
		pEffect->setUnit( 5 );
		pEffect->setDir( 3 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay2->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingSideTrap* pEffect = new EffectCastingSideTrap( pIllusionsWay2 );

		pEffect->setStartXY( 25, 67 );
		pEffect->setLength( 43 );
		pEffect->setTick( 10 );
		pEffect->setUnit( 5 );
		pEffect->setDir( 3 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay2->addEffect_LOCKING( pEffect );
	}

	{
		EffectCastingSideTrap* pEffect = new EffectCastingSideTrap( pIllusionsWay2 );

		pEffect->setStartXY( 55, 132 );
		pEffect->setLength( 43 );
		pEffect->setTick( 10 );
		pEffect->setUnit( 5 );
		pEffect->setDir( 7 );
		pEffect->setNextTime(0);
		pEffect->setDeadline(12000);
		pIllusionsWay2->addEffect_LOCKING( pEffect );
	}*/
}

DWORD GDRLairEntrance::heartbeat(Timeval currentTime)
{
	Zone* pZone = GDRLairManager::Instance().getZone( GDRLairManager::GDR_LAIR );

	__ENTER_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

	const PCManager* pPM = pZone->getPCManager();
	int limit = g_pVariableManager->getVariable(GDR_LAIR_PC_LIMIT);
	// 0이면 인원 무제한
	if ( limit != 0 && pPM->getSize() >= limit )
	{
		pZone->getZoneGroup()->unlock();
		return GDR_LAIR_ICEPOLE;
	}

	__LEAVE_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

	return TimerState::heartbeat(currentTime);
}

/*void GDRLairIllusionsWayOnly::start()
{
	TimerState::start();
	filelog( "GDRLair.log", "Starting Illusions Way State" );
	cout << "일루젼스 웨이만 활성화되어이뜸" << endl;
}*/

//void GDRLairIllusionsWayOnly::end()
//{
//	Zone* pIllusionsWay1 = getZoneByZoneID(1410);
//	Zone* pIllusionsWay2 = getZoneByZoneID(1411);

/*	__ENTER_CRITICAL_SECTION( (*pIllusionsWay1) )
	pIllusionsWay1->getPCManager()->transportAllCreatures(0xffff);
	__LEAVE_CRITICAL_SECTION( (*pIllusionsWay1) )
	__ENTER_CRITICAL_SECTION( (*pIllusionsWay2) )
	pIllusionsWay2->getPCManager()->transportAllCreatures(0xffff);
	__LEAVE_CRITICAL_SECTION( (*pIllusionsWay2) )*/
//}

/*DWORD GDRLairIllusionsWayOnly::heartbeat(Timeval currentTime)
{
	Zone* pZone = GDRLairManager::Instance().getZone( GDRLairManager::GDR_LAIR );

	__ENTER_CRITICAL_SECTION( (*pZone) )

	const PCManager* pPM = pZone->getPCManager();
	if ( pPM->getSize() > 0 )
	{
		pZone->unlock();
		return GDR_LAIR_ICEPOLE;
	}

	__LEAVE_CRITICAL_SECTION( (*pZone) )

	return TimerState::heartbeat(currentTime);
}*/

void GDRLairIcepole::start()
{
	filelog( "GDRLair.log", "Starting Ice Pole State : %d", GDRLairManager::Instance().getTotalPCs() );
	cout << "얼음기둥 활성화모드" << endl;
	getCurrentTime( m_BroadcastTime );

	Zone* pIllusionsWay1 = getZoneByZoneID(1410);
	Zone* pIllusionsWay2 = getZoneByZoneID(1411);

	// 일루젼스웨이에서는 몽땅 쫓아내버린다.
	GCSystemMessage gcSM;
	gcSM.setMessage("청콘繫법뼙얾裂쨌.10취빈盧땡돕릿삶뒈듐.");

	pIllusionsWay1->getPCManager()->transportAllCreatures(0xffff);
	pIllusionsWay1->deleteEffect_LOCKING(0);

	__ENTER_CRITICAL_SECTION( (*(pIllusionsWay1->getZoneGroup())) )
		pIllusionsWay1->broadcastPacket(&gcSM);
	__LEAVE_CRITICAL_SECTION( (*(pIllusionsWay1->getZoneGroup())) )

	pIllusionsWay2->getPCManager()->transportAllCreatures(0xffff);
	pIllusionsWay2->deleteEffect_LOCKING(0);

	__ENTER_CRITICAL_SECTION( (*(pIllusionsWay2->getZoneGroup())) )
		pIllusionsWay1->broadcastPacket(&gcSM);
	__LEAVE_CRITICAL_SECTION( (*(pIllusionsWay2->getZoneGroup())) )
}

DWORD GDRLairIcepole::heartbeat(Timeval currentTime)
{
	if ( GDRLairManager::Instance().getTotalPCs() < 1 )
	{
		return GDR_LAIR_IDLE;
	}

	Zone* pZone = GDRLairManager::Instance().getZone( GDRLairManager::GDR_LAIR );

/*	int illPCNum = pIllusionsWay1->getPCManager()->getSize() + pIllusionsWay2->getPCManager()->getSize();
	if ( illPCNum > 0 )
	{
		if ( currentTime > m_BroadcastTime )
		{
			GCSystemMessage gcSM;
			char buf[255];
			sprintf(buf, "일루젼스 웨이에 %d 명이 있습니다. 모든 사람이 일루젼스 웨이를 통과해야 질드레 레어가 활성화됩니다.", illPCNum);
			gcSM.setMessage( buf );

			__ENTER_CRITICAL_SECTION( (*pZone) )

			pZone->broadcastPacket( &gcSM );

			__LEAVE_CRITICAL_SECTION( (*pZone) )

			m_BroadcastTime = currentTime;
			m_BroadcastTime.tv_sec += 60;
		}

		return 0;
	}
*/

	__ENTER_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

	const PCManager* pPM = pZone->getPCManager();
	const hash_map<ObjectID_t, Creature*>& pCL = pPM->getCreatures();

	hash_map<ObjectID_t, Creature*>::const_iterator itr = pCL.begin();
	hash_map<ObjectID_t, Creature*>::const_iterator endItr = pCL.end();

	for ( ; itr != endItr; ++itr )
	{
		Creature* pCreature = itr->second;

		if ( abs( (int)(pCreature->getX()) - 78 ) < 13 && abs( (int)(pCreature->getY()) - 89 ) < 13 )
		{
			pZone->getZoneGroup()->unlock();
			return GDR_LAIR_SCENE_1;
		}
	}

	__LEAVE_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

	return 0;
}

void GDRLairScene1::start()
{
	filelog( "GDRLair.log", "Starting Scene 1 State : %d", GDRLairManager::Instance().getTotalPCs() );
	cout << "질드레 레어 1번 씬" << endl;
	Monster* pGDR = new Monster(717);
	pGDR->setName("질드레");
	pGDR->setFlag( Effect::EFFECT_CLASS_NO_DAMAGE );
	pGDR->setTreasure(false);

//	MonsterAI* pAI = pGDR->getBrain();
	pGDR->setBrain(NULL);
//	SAFE_DELETE( pAI );

	Assert( getGDR() == NULL );
	setGDR(pGDR);

	Zone* pLair = GDRLairManager::Instance().getZone( GDRLairManager::GDR_LAIR );
	Assert( pLair != NULL );

	__ENTER_CRITICAL_SECTION( (*(pLair->getZoneGroup())) )

	pLair->addCreature( pGDR, 78, 89, 1 );

	__LEAVE_CRITICAL_SECTION( (*(pLair->getZoneGroup())) )

	m_ActionList.clear();

	m_ActionList.push_back( new ActionEffect( pGDR, Effect::EFFECT_CLASS_SUMMON_GDR, 15 ) );
	m_ActionList.push_back( new ActionWait(pGDR, 30) );
	m_ActionList.push_back( new ActionSay(pGDR, 331) );
	m_ActionList.push_back( new ActionWait(pGDR, 50) );
	m_ActionList.push_back( new ActionSay(pGDR, 332) );
	m_ActionList.push_back( new ActionWait(pGDR, 50) );
	m_ActionList.push_back( new ActionSay(pGDR, 333) );
	m_ActionList.push_back( new ActionWait(pGDR, 80) );
	m_ActionList.push_back( new ActionSay(pGDR, 334) );
	m_ActionList.push_back( new ActionWalk( pGDR, 74, 85, 9 ) );
	m_ActionList.push_back( new ActionWalk( pGDR, 75, 86, 9 ) );
	
	GDRScene::start();
}

void GDRLairScene1::end()
{
	cout << "1번 씬 끝" << endl;

	list<Action*>::iterator itr = m_ActionList.begin();

	for ( ; itr != m_ActionList.end(); ++itr )
	{
		SAFE_DELETE( (*itr) );
	}

	m_ActionList.clear();
}

GDRLairSummonMonster::GDRLairSummonMonster() : MonsterSummonState( GDRLairManager::Instance().getZone(GDRLairManager::GDR_LAIR), GDR_LAIR_SCENE_2, GDR_LAIR_KILL_ALL ) { }

void GDRLairSummonMonster::start()
{
	filelog( "GDRLair.log", "Starting Summon Monster State : %d", GDRLairManager::Instance().getTotalPCs() );
	cout << toString() << endl;
	MonsterSummonState::start();

	GroupSummonInfo* pGSI = new GroupSummonInfo;

	pGSI->getSummonInfos().push_back( new SummonInfo( 467, 20, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 471, 10, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 584, 10, 78, 89 ) );
	m_GroupSummonInfos.push_back( pGSI );

	pGSI = new GroupSummonInfo;
	pGSI->getSummonInfos().push_back( new SummonInfo( 586, 20, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 587, 10, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 589, 20, 78, 89 ) );
	m_GroupSummonInfos.push_back( pGSI );

	pGSI = new GroupSummonInfo;
	pGSI->getSummonInfos().push_back( new SummonInfo( 590, 20, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 592, 20, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 318, 20, 78, 89 ) );
	m_GroupSummonInfos.push_back( pGSI );

	pGSI = new GroupSummonInfo;
	pGSI->getSummonInfos().push_back( new SummonInfo( 596, 10, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 595, 20, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 407, 10, 78, 89 ) );
	m_GroupSummonInfos.push_back( pGSI );

	pGSI = new GroupSummonInfo;
	pGSI->getSummonInfos().push_back( new SummonInfo( 597, 10, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 598, 5, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 437, 20, 78, 89 ) );
	m_GroupSummonInfos.push_back( pGSI );

	pGSI = new GroupSummonInfo;
	pGSI->getSummonInfos().push_back( new SummonInfo( 604, 20, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 600, 10, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 483, 20, 78, 89 ) );
	m_GroupSummonInfos.push_back( pGSI );

	pGSI = new GroupSummonInfo;
	pGSI->getSummonInfos().push_back( new SummonInfo( 504, 10, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 503, 20, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 614, 5, 78, 89 ) );
	m_GroupSummonInfos.push_back( pGSI );

	pGSI = new GroupSummonInfo;
	pGSI->getSummonInfos().push_back( new SummonInfo( 624, 10, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 614, 10, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 600, 10, 78, 89 ) );
	m_GroupSummonInfos.push_back( pGSI );

	pGSI = new GroupSummonInfo;
	pGSI->getSummonInfos().push_back( new SummonInfo( 602, 4, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 493, 10, 78, 89 ) );
	m_GroupSummonInfos.push_back( pGSI );

	pGSI = new GroupSummonInfo;
//	pGSI->getSummonInfos().push_back( new SummonInfo( 493, 5, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 599, 1, 78, 89 ) );
//	pGSI->getSummonInfos().push_back( new SummonInfo( 624, 10, 78, 89 ) );
	pGSI->getSummonInfos().push_back( new SummonInfo( 603, 3, 78, 89 ) );
	m_GroupSummonInfos.push_back( pGSI );

	m_CurrentSummonInfo = m_GroupSummonInfos.begin();
}

void GDRLairSummonMonster::end()
{
	list<GroupSummonInfo*>::iterator itr = m_GroupSummonInfos.begin();
	list<GroupSummonInfo*>::iterator endItr = m_GroupSummonInfos.end();

	for ( ; itr != endItr ; ++itr )
	{
		SAFE_DELETE( (*itr) );
	}

	m_GroupSummonInfos.clear();
}

void GDRLairScene2::start()
{
	cout << "2번 씬" << endl;
	filelog( "GDRLair.log", "Starting Scene 2 State : %d", GDRLairManager::Instance().getTotalPCs() );
	Monster* pGDR = getGDR();

	m_ActionList.clear();

	m_ActionList.push_back( new ActionSay( pGDR, 335 ) );
	m_ActionList.push_back( new ActionWait( pGDR, 50 ) );
	m_ActionList.push_back( new ActionSay( pGDR, 336 ) );
	m_ActionList.push_back( new ActionWait( pGDR, 50 ) );
	m_ActionList.push_back( new ActionWalk( pGDR, 68, 80, 9 ) );
	m_ActionList.push_back( new ActionSay( pGDR, 361 ) );
	m_ActionList.push_back( new ActionWalk( pGDR, 56, 66, 9 ) );
//	m_ActionList.push_back( new ActionWait( pGDR, 50 ) );
	m_ActionList.push_back( new ActionSay( pGDR, 337 ) );
	m_ActionList.push_back( new ActionWalk( pGDR, 46, 47, 9 ) );
//	m_ActionList.push_back( new ActionWait( pGDR, 50 ) );
	m_ActionList.push_back( new ActionSay( pGDR, 338 ) );
	m_ActionList.push_back( new ActionWalk( pGDR, 35, 39, 9 ) );
//	m_ActionList.push_back( new ActionWait( pGDR, 30 ) );
	m_ActionList.push_back( new ActionSay( pGDR, 339 ) );
	m_ActionList.push_back( new ActionWait( pGDR, 50 ) );
	m_ActionList.push_back( new ActionSay( pGDR, 340 ) );
	m_ActionList.push_back( new ActionWait( pGDR, 50 ) );
	m_ActionList.push_back( new ActionSay( pGDR, 362 ) );
	m_ActionList.push_back( new ActionWait( pGDR, 60 ) );

//	m_ActionList.push_back( new ActionEffect( pGDR, Effect::EFFECT_CLASS_GDR_SATELLITE, 1200 ) );
//	m_ActionList.push_back( new ActionEffect( pGDR, Effect::EFFECT_CLASS_GDR_FLOATING, 1200 ) );

//	m_ActionList.push_back( new ActionWalk( pGDR, 58, 69, 9 ) );
//	m_ActionList.push_back( new ActionWalk( pGDR, 54, 56, 9 ) );
//	m_ActionList.push_back( new ActionWalk( pGDR, 33, 37, 9 ) );
//	m_ActionList.push_back( new ActionWalk( pGDR, 34, 38, 9 ) );
	
//	m_ActionList.push_back( new ActionRemoveEffect( pGDR, Effect::EFFECT_CLASS_GDR_SATELLITE ) );
//	m_ActionList.push_back( new ActionRemoveEffect( pGDR, Effect::EFFECT_CLASS_GDR_FLOATING ) );

//	m_ActionList.push_back( new ActionWait( pGDR, 30 ) );
	m_ActionList.push_back( new ActionSay( pGDR, 363 ) );
	m_ActionList.push_back( new ActionWait( pGDR, 20 ) );
	m_ActionList.push_back( new ActionEffect( pGDR, Effect::EFFECT_CLASS_COMA, 50 ) );
	m_ActionList.push_back( new ActionWait( pGDR, 60 ) );
	m_ActionList.push_back( new ActionSay( pGDR, 341 ) );
	m_ActionList.push_back( new ActionWait( pGDR, 50 ) );
	m_ActionList.push_back( new ActionSay( pGDR, 342 ) );
	m_ActionList.push_back( new ActionWait( pGDR, 50 ) );
//	m_ActionList.push_back( new ActionWalk( pGDR, 32, 36, 9 ) );

	GDRScene::start();
}

void GDRLairScene2::end()
{
	cout << "2번 씬 끝" << endl;

	list<Action*>::iterator itr = m_ActionList.begin();

	for ( ; itr != m_ActionList.end(); ++itr )
	{
		SAFE_DELETE( (*itr) );
	}

	m_ActionList.clear();
}

GDRLairSummonGDRDup::GDRLairSummonGDRDup() : MonsterSummonState( GDRLairManager::Instance().getZone(GDRLairManager::GDR_LAIR), GDR_LAIR_SCENE_3, GDR_LAIR_KILL_ALL ) { }

void GDRLairSummonGDRDup::start()
{
	filelog( "GDRLair.log", "Starting GDR Dup State : %d", GDRLairManager::Instance().getTotalPCs() );
	cout << toString() << endl;
	MonsterSummonState::start();

	GroupSummonInfo* pGSI = new GroupSummonInfo;

	// 5마리
	pGSI->getSummonInfos().push_back( new SummonInfo( 721, 5, 38, 43 ) );
	m_GroupSummonInfos.push_back( pGSI );

	m_CurrentSummonInfo = m_GroupSummonInfos.begin();
}

void GDRLairSummonGDRDup::end()
{
	list<GroupSummonInfo*>::iterator itr = m_GroupSummonInfos.begin();
	list<GroupSummonInfo*>::iterator endItr = m_GroupSummonInfos.end();

	for ( ; itr != endItr ; ++itr )
	{
		SAFE_DELETE( (*itr) );
	}

	m_GroupSummonInfos.clear();
}

void GDRLairScene3::start()
{
	filelog( "GDRLair.log", "Starting Scene 3 State : %d", GDRLairManager::Instance().getTotalPCs() );
	cout << "3번 씬" << endl;
	Monster* pGDR = getGDR();

	m_ActionList.clear();

	m_ActionList.push_back( new ActionSay( pGDR, 343 ) );
	m_ActionList.push_back( new ActionWait( pGDR, 50 ) );
	m_ActionList.push_back( new ActionSay( pGDR, 344 ) );
	m_ActionList.push_back( new ActionWait( pGDR, 50 ) );

	m_ActionList.push_back( new ActionEffect( pGDR, Effect::EFFECT_CLASS_GDR_SATELLITE, 9999999 ) );

	GDRScene::start();
}

void GDRLairScene3::end()
{
	cout << "3번 씬 끝" << endl;

	list<Action*>::iterator itr = m_ActionList.begin();

	for ( ; itr != m_ActionList.end(); ++itr )
	{
		SAFE_DELETE( (*itr) );
	}

	m_ActionList.clear();
}

void GDRLairGDRFight::start()
{
	filelog( "GDRLair.log", "Starting GDR Fight State : %d", GDRLairManager::Instance().getTotalPCs() );
	cout << "질드레 등장~~" << endl;

	Monster* pGDR = GDRLairManager::Instance().getGDR();
	Assert( pGDR != NULL );
	Zone* pZone = pGDR->getZone();
	Assert( pZone != NULL );

	__ENTER_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )
	
	pGDR->removeFlag( Effect::EFFECT_CLASS_NO_DAMAGE );
	const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo( pGDR->getMonsterType() );

	uint aitype = pMonsterInfo->getAIType();
	MonsterAI* pBrain = new MonsterAI(pGDR, aitype);
	pGDR->setBrain( pBrain );

	__LEAVE_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )
}

DWORD GDRLairGDRFight::heartbeat(Timeval currentTime)
{
	Zone* pZone = GDRLairManager::Instance().getZone( GDRLairManager::GDR_LAIR );
	int msize, psize;

	__ENTER_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

	MonsterManager* pMM = pZone->getMonsterManager();
	msize = pMM->getSize();

	const PCManager* pPM = pZone->getPCManager();
	psize = pPM->getSize();

	__LEAVE_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

	if ( psize < 1 )
	{
		return GDR_LAIR_KILL_ALL;
	}
	else if ( msize < 1 )
	{
		return GDR_LAIR_SCENE_4;
	}
	else
	{
		return 0;
	}
}

void GDRLairGDRFight::end()
{
	GDRLairManager::Instance().setGDR(NULL);

	GCNoticeEvent gcNE;
	gcNE.setCode( NOTICE_EVENT_GDR_LAIR_ENDING_1 );

	Zone* pZone = GDRLairManager::Instance().getZone( GDRLairManager::GDR_LAIR );

	__ENTER_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

	pZone->broadcastPacket( &gcNE );

	__LEAVE_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )
}

void GDRLairScene4::start()
{
	filelog( "GDRLair.log", "Starting Scene 4 State : %d", GDRLairManager::Instance().getTotalPCs() );
	cout << "질드레 레어 4번 씬" << endl;
	Zone* pGDRLair = GDRLairManager::Instance().getZone( GDRLairManager::GDR_LAIR );
	Zone* pGDRCore = GDRLairManager::Instance().getZone( GDRLairManager::GDR_LAIR_CORE );

	__ENTER_CRITICAL_SECTION( (*(pGDRLair->getZoneGroup())) )

	pGDRLair->getPCManager()->transportAllCreatures( pGDRCore->getZoneID(), 38, 43, defaultRaceValue, 15 );

	__LEAVE_CRITICAL_SECTION( (*(pGDRLair->getZoneGroup())) )

	// 질드레 각성
	Monster* pGDR = new Monster(723);

	pGDR->setName("질드레");
	pGDR->setTreasure(false);
	pGDR->setFlag( Effect::EFFECT_CLASS_NO_DAMAGE );

	pGDR->setBrain(NULL);

	Assert( getGDR() == NULL );
	setGDR( pGDR );

	__ENTER_CRITICAL_SECTION( (*(pGDRCore->getZoneGroup())) )

	pGDRCore->addCreature( pGDR, 34, 38, 1 );

	__LEAVE_CRITICAL_SECTION( (*(pGDRCore->getZoneGroup())) )

	m_ActionList.clear();
	m_ActionList.push_back( new ActionEffect(pGDR, Effect::EFFECT_CLASS_COMA, 120) );
	m_ActionList.push_back( new ActionWait(pGDR, 120) );
	m_ActionList.push_back( new ActionRemoveEffect(pGDR, Effect::EFFECT_CLASS_COMA) );
	m_ActionList.push_back( new ActionEffect(pGDR, Effect::EFFECT_CLASS_GDR_FLOATING, 100) );
	m_ActionList.push_back( new ActionWait(pGDR, 130) );
	m_ActionList.push_back( new ActionSay(pGDR, 364) );
	m_ActionList.push_back( new ActionWait(pGDR, 50) );
	m_ActionList.push_back( new ActionSay(pGDR, 365) );
	m_ActionList.push_back( new ActionWait(pGDR, 50) );
	m_ActionList.push_back( new ActionSay(pGDR, 366) );
	m_ActionList.push_back( new ActionWait(pGDR, 50) );
	m_ActionList.push_back( new ActionSay(pGDR, 367) );
	m_ActionList.push_back( new ActionWait(pGDR, 50) );
	m_ActionList.push_back( new ActionHollywood(pGDR) );
	m_ActionList.push_back( new ActionWait(pGDR, 10) );
	m_ActionList.push_back( new ActionHollywood(pGDR) );
	m_ActionList.push_back( new ActionWait(pGDR, 10) );
	m_ActionList.push_back( new ActionHollywood(pGDR) );
	m_ActionList.push_back( new ActionWait(pGDR, 10) );
	m_ActionList.push_back( new ActionHollywood(pGDR) );
	m_ActionList.push_back( new ActionWait(pGDR, 10) );
	m_ActionList.push_back( new ActionHollywood(pGDR) );
	m_ActionList.push_back( new ActionWait(pGDR, 30) );
	m_ActionList.push_back( new ActionSay(pGDR, 368) );
	m_ActionList.push_back( new ActionWait(pGDR, 60) );
	m_ActionList.push_back( new ActionSay(pGDR, 347) );
	m_ActionList.push_back( new ActionWait(pGDR, 50) );
	m_ActionList.push_back( new ActionSay(pGDR, 369) );
	m_ActionList.push_back( new ActionWait(pGDR, 30) );

	GDRScene::start();
}

void GDRLairAwakenedGDRFight::start()
{
	filelog( "GDRLair.log", "Starting Awakened GDR Fight State : %d", GDRLairManager::Instance().getTotalPCs() );
	cout << "질드레 각성체 등장~~" << endl;

	Monster* pGDR = GDRLairManager::Instance().getGDR();
	Assert( pGDR != NULL );
	Zone* pZone = pGDR->getZone();
	Assert( pZone != NULL );

	__ENTER_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )
	
	pGDR->removeFlag( Effect::EFFECT_CLASS_NO_DAMAGE );
	const MonsterInfo* pMonsterInfo = g_pMonsterInfoManager->getMonsterInfo( pGDR->getMonsterType() );

	uint aitype = pMonsterInfo->getAIType();
	MonsterAI* pBrain = new MonsterAI(pGDR, aitype);
	pGDR->setBrain( pBrain );

	__LEAVE_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )
}

DWORD GDRLairAwakenedGDRFight::heartbeat(Timeval currentTime)
{
	Zone* pZone = GDRLairManager::Instance().getZone( GDRLairManager::GDR_LAIR_CORE );

//	Zone* pZone = pGDR->getZone();
	Assert( pZone != NULL );

	int msize;
	int psize;

	// 승명~ 여기서 pZone 안에 m_pZoneGroup 이 NULL 이어서 죽은 코어가 있다. slayer5
	// 확인해 보셈...아~ 잠와~
	__ENTER_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

	MonsterManager* pMM = pZone->getMonsterManager();
	msize = pMM->getSize();

	const PCManager* pPM = pZone->getPCManager();
	psize = pPM->getSize();

	__LEAVE_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

	if ( psize < 1 )
	{
		m_bGDRDamaged = false;
		return GDR_LAIR_KILL_ALL;
	}

	if ( msize < 1 )
	{
		m_bGDRDamaged = false;
		// 오오 끝났당
		return GDR_LAIR_ENDING;
	}

	if ( !m_bGDRDamaged )
	{
		HP_t currentHP;
		HP_t maxHP;

		__ENTER_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

		Monster* pGDR = GDRLairManager::Instance().getGDR();
		Assert( pGDR != NULL );
		currentHP = pGDR->getHP(ATTR_CURRENT);
		maxHP = pGDR->getHP(ATTR_MAX);

		__LEAVE_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

		if ( currentHP < maxHP/2 )
		{
			m_bGDRDamaged = true;
			return GDR_LAIR_SCENE_5;
		}
	}

	return 0;
}

void GDRLairScene5::start()
{
	filelog( "GDRLair.log", "Starting Scene 5 State : %d", GDRLairManager::Instance().getTotalPCs() );
	cout << "질드레 레어 5번 씬" << endl;

	Monster* pGDR = getGDR();
	Zone* pZone = pGDR->getZone();

	__ENTER_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

	pGDR->setBrain(NULL);
	pGDR->setFlag( Effect::EFFECT_CLASS_NO_DAMAGE );

	__LEAVE_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

	m_ActionList.clear();
	m_ActionList.push_back( new ActionSay(pGDR, 348) );
	m_ActionList.push_back( new ActionWait(pGDR, 50) );
	m_ActionList.push_back( new ActionSay(pGDR, 349) );
	m_ActionList.push_back( new ActionWait(pGDR, 50) );
	m_ActionList.push_back( new ActionSay(pGDR, 350) );
	m_ActionList.push_back( new ActionWait(pGDR, 50) );
	m_ActionList.push_back( new ActionSay(pGDR, 370) );
	m_ActionList.push_back( new ActionWait(pGDR, 50) );

	int direction = (rand()%2);

	if ( direction == 0 )
	{
		m_ActionList.push_back( new ActionWalk( pGDR, 79, 24, 9 ) );
		m_ActionList.push_back( new ActionWalk( pGDR, 134, 84, 9 ) );
	}
	else
	{
		m_ActionList.push_back( new ActionWalk( pGDR, 19, 83, 9 ) );
		m_ActionList.push_back( new ActionWalk( pGDR, 74, 140, 9 ) );
		m_ActionList.push_back( new ActionWalk( pGDR, 80, 140, 9 ) );
	}

	m_ActionList.push_back( new ActionWait(pGDR, 50) );
	m_ActionList.push_back( new ActionSay(pGDR, 351) );
	m_ActionList.push_back( new ActionWait(pGDR, 50) );
	m_ActionList.push_back( new ActionSay(pGDR, 355) );
	m_ActionList.push_back( new ActionWait(pGDR, 30) );

	GDRScene::start();
}

GDRLairMinionFight::GDRLairMinionFight()
	: MonsterSummonState( GDRLairManager::Instance().getZone(GDRLairManager::GDR_LAIR_CORE), GDR_LAIR_SCENE_6, GDR_LAIR_KILL_ALL ) { }

void GDRLairMinionFight::start()
{
	filelog( "GDRLair.log", "Starting Minion Fight State : %d", GDRLairManager::Instance().getTotalPCs() );
	cout << toString() << endl;
	MonsterSummonState::start();

	GroupSummonInfo* pGSI = new GroupSummonInfo;

	Monster* pGDR = GDRLairManager::Instance().getGDR();

	if ( pGDR->getX() > pGDR->getY() )
	{
		pGSI->getSummonInfos().push_back( new SummonInfo( 724, 3, 136, 86 ) );
	}
	else
	{
		pGSI->getSummonInfos().push_back( new SummonInfo( 725, 3, 83, 139 ) );
	}
	
	m_GroupSummonInfos.push_back( pGSI );

	m_CurrentSummonInfo = m_GroupSummonInfos.begin();
}

void GDRLairMinionFight::end()
{
	list<GroupSummonInfo*>::iterator itr = m_GroupSummonInfos.begin();
	list<GroupSummonInfo*>::iterator endItr = m_GroupSummonInfos.end();

	for ( ; itr != endItr ; ++itr )
	{
		SAFE_DELETE( (*itr) );
	}

	m_GroupSummonInfos.clear();
}

void GDRLairScene6::start()
{
	filelog( "GDRLair.log", "Starting Scene 6 State : %d", GDRLairManager::Instance().getTotalPCs() );
	cout << "질드레 레어 6번 씬" << endl;
	Monster* pGDR = getGDR();
	Zone* pZone = pGDR->getZone();

	// 비쥬 주자
	const PCManager* pPCManager = pZone->getPCManager();
	const hash_map< ObjectID_t, Creature* > & creatures = pPCManager->getCreatures();
	hash_map< ObjectID_t, Creature* >::const_iterator itr;

	for (itr=creatures.begin(); itr!=creatures.end(); itr++)
	{
		Creature* pCreature = itr->second;

		if (pCreature->isPC())
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Inventory* pInventory = pPC->getInventory();
			Item* pItem = NULL;

			ItemType_t itemType = 8;
			filelog( "GDRLair.log", "%s 가 비쥬를 받았습니다.", pPC->getName().c_str() );
//				itemType = ((goodOneIndex[1]==i||goodOneIndex[2]==i)? 9:8);

			list<OptionType_t> nullList;
			pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_QUEST_ITEM, itemType, nullList);
	 
			(pZone->getObjectRegistry()).registerObject(pItem);

			// 인벤토리의 빈 곳을 찾는다.
			_TPOINT p;
			if (pInventory->getEmptySlot(pItem, p))
			{
				// 인벤토리에 추가한다.
				pInventory->addItem(p.x, p.y, pItem);

	            pItem->create(pCreature->getName(), STORAGE_INVENTORY, 0, p.x, p.y);

				// ItemTrace 에 Log 를 남긴다
				if ( pItem != NULL && pItem->isTraceItem() )
				{
					remainTraceLog( pItem, "GDRLair", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
					remainTraceLogNew( pItem, pCreature->getName(), ITL_GET, ITLD_EVENTNPC, pZone->getZoneID() );
				}

				// 인벤토리에 아이템 생성 패킷을 보내준다.
				GCCreateItem gcCreateItem;

				makeGCCreateItem( &gcCreateItem, pItem, p.x, p.y );

				pCreature->getPlayer()->sendPacket(&gcCreateItem);
			}
			else
			{
				filelog( "GDRLair.log", "근데 인벤에 자리가 없습니다." );
				SAFE_DELETE( pItem );
			}
		}
	}

	// 6초있다가 날라간다.
	__ENTER_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

	pGDR->setBrain(NULL);
	pZone->getPCManager()->transportAllCreatures( pZone->getZoneID(), 82, 93, defaultRaceValue, 15 );

	__LEAVE_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )

	// 그 15초 사이에 다 떠들어야 된다.
	m_ActionList.clear();
	m_ActionList.push_back( new ActionSay(pGDR, 356) );
	m_ActionList.push_back( new ActionWait(pGDR, 50) );
	m_ActionList.push_back( new ActionSay(pGDR, 357) );
	m_ActionList.push_back( new ActionWait(pGDR, 50) );
	m_ActionList.push_back( new ActionSay(pGDR, 371) );
	m_ActionList.push_back( new ActionWait(pGDR, 50) );
	m_ActionList.push_back( new ActionWarp(pGDR, 78, 89) );
	// 로드하는데 5초쯤 기다려준다.
	m_ActionList.push_back( new ActionWait(pGDR, 50) );

	m_ActionList.push_back( new ActionSay(pGDR, 358) );
	m_ActionList.push_back( new ActionWait(pGDR, 30) );
	m_ActionList.push_back( new ActionSay(pGDR, 359) );
	m_ActionList.push_back( new ActionWait(pGDR, 30) );

	GDRScene::start();
}

void GDRLairEnding::start()
{
	filelog( "GDRLair.log", "Starting Ending State : %d", GDRLairManager::Instance().getTotalPCs() );
	cout << "우와.. 엔딩이다 -o-" << endl;
	TimerState::start();

	Zone* pZone = GDRLairManager::Instance().getZone( GDRLairManager::GDR_LAIR_CORE );

	const PCManager* pPCManager = pZone->getPCManager();
	const hash_map< ObjectID_t, Creature* > & creatures = pPCManager->getCreatures();
	hash_map< ObjectID_t, Creature* >::const_iterator itr;

	int CoreZapNum = 2;
	int PendentNum = 3;

	int totalNum = creatures.size();
	int* rewardType = new int[totalNum];

	for ( int i=0; i<totalNum; ++i )
	{
		if ( CoreZapNum + PendentNum > 0 )
		{
			int value = rand()%(totalNum-i);
			if ( value < CoreZapNum )
			{
				rewardType[i] = 0;
				CoreZapNum--;
			}
			else if ( value - CoreZapNum < PendentNum )
			{
				rewardType[i] = 1;
				PendentNum--;
			}
			else rewardType[i] = 2;
		}
		else rewardType[i] = 2;
	}

	ItemType_t itemType;
	Grade_t grade;
	int i;
	for (i=0, itr=creatures.begin(); itr!=creatures.end(); i++, itr++)
	{
		Creature* pCreature = itr->second;

		if (pCreature->isPC())
		{
			PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
			Inventory* pInventory = pPC->getInventory();
			Item* pItem = NULL;

			if ( rewardType[i] == 0 )
			{
				int value = rand()%100;
				static int iTypeRatio[4] = { 5, 25, 35, 35 };
				for ( itemType = 0 ; itemType < 4; ++itemType )
				{
					value -= iTypeRatio[itemType];
					if ( value < 0 ) break;
				}
				if ( itemType >= 4 ) itemType = 3;

				value = rand()%1000;
				static int gradeRatio[5] = { 340, 490, 148, 20, 2 };
				for ( grade = 0 ; grade < 5; ++grade )
				{
					value -= gradeRatio[grade];
					if (value < 0 ) break;
				}
				if ( grade >= 5 ) grade = 4;
				grade++;

				list<OptionType_t> nullList;
				pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_CORE_ZAP, itemType, nullList);
				pItem->setGrade(grade);
				filelog( "GDRLair.log", "%s 가 코어잽을 받았습니다. : %d/%d", pPC->getName().c_str(), itemType, grade );
			}
			else
			{
				if ( rewardType[i] == 1 )
				{
					itemType = 9;
					filelog( "GDRLair.log", "%s 가 펜던트를 받았습니다.", pPC->getName().c_str() );
					list<OptionType_t> nullList;
					pItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_QUEST_ITEM, itemType, nullList);
				}
				else
				{
//					itemType = 8;
//					filelog( "GDRLair.log", "%s 가 비쥬를 받았습니다.", pPC->getName().c_str() );
					// 비쥬는 진작에 줬다.
					continue;
				}
//				itemType = ((goodOneIndex[1]==i||goodOneIndex[2]==i)? 9:8);

			}
	 
			(pZone->getObjectRegistry()).registerObject(pItem);

			// 인벤토리의 빈 곳을 찾는다.
			_TPOINT p;
			if (pInventory->getEmptySlot(pItem, p))
			{
				// 인벤토리에 추가한다.
				pInventory->addItem(p.x, p.y, pItem);

	            pItem->create(pCreature->getName(), STORAGE_INVENTORY, 0, p.x, p.y);

				// ItemTrace 에 Log 를 남긴다
				if ( pItem != NULL && pItem->isTraceItem() )
				{
					remainTraceLog( pItem, "GDRLair", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
					remainTraceLogNew( pItem, pCreature->getName(), ITL_GET, ITLD_EVENTNPC );
				}

				// 인벤토리에 아이템 생성 패킷을 보내준다.
				GCCreateItem gcCreateItem;

				makeGCCreateItem( &gcCreateItem, pItem, p.x, p.y );

				pCreature->getPlayer()->sendPacket(&gcCreateItem);
			}
			else
			{
				SAFE_DELETE( pItem );
			}
		}
	}

}

void GDRLairEnding::end()
{
	cout << "여기도 엔딩이다 ㅋㅋ" << endl;

//	Monster* pGDR = GDRLairManager::Instance().getGDR();
//	SAFE_DELETE( pGDR );
	GDRLairManager::Instance().setGDR(NULL);

	for ( int i=GDRLairManager::ILLUSIONS_WAY_1 ; i < GDRLairManager::GDR_LAIR_MAX ; ++i )
	{
		Zone* pZone = GDRLairManager::Instance().getZone(i);
		if ( pZone != NULL )
		{
			__ENTER_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )
			pZone->getPCManager()->transportAllCreatures(0xffff);
			pZone->killAllMonsters_UNLOCK();
			pZone->deleteEffect_LOCKING(0);
			__LEAVE_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )
		}
	}

	TimerState::end();
}

void GDRLairKillAll::start()
{
	filelog( "GDRLair.log", "Starting Killall State : %d", GDRLairManager::Instance().getTotalPCs() );
	cout << "다주거써~@!" << endl;

	GCSystemMessage gcSM;
	gcSM.setMessage("질드레 레어 공략에 실패했습니다. 10초 후에 부활 위치로 이동됩니다.");

	for ( int i=GDRLairManager::ILLUSIONS_WAY_1 ; i < GDRLairManager::GDR_LAIR_MAX ; ++i )
	{
		Zone* pZone = GDRLairManager::Instance().getZone(i);
		if ( pZone != NULL )
		{
			__ENTER_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )
			pZone->broadcastPacket( &gcSM );
			__LEAVE_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )
		}
	}
}

void GDRLairKillAll::end()
{
	filelog( "GDRLair.log", "Ending Killall State : %d", GDRLairManager::Instance().getTotalPCs() );
	cout << "다주겄냥?" << endl;

	Monster* pGDR = GDRLairManager::Instance().getGDR();
	if ( pGDR != NULL )
	{
		pGDR->removeFlag( Effect::EFFECT_CLASS_NO_DAMAGE );
		pGDR->setHP(0);
	}
//	SAFE_DELETE( pGDR );
	GDRLairManager::Instance().setGDR(NULL);

	for ( int i=GDRLairManager::ILLUSIONS_WAY_1 ; i < GDRLairManager::GDR_LAIR_MAX ; ++i )
	{
		Zone* pZone = GDRLairManager::Instance().getZone(i);
		if ( pZone != NULL )
		{
			__ENTER_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )
			pZone->getPCManager()->transportAllCreatures(0xffff);
			pZone->killAllMonsters_UNLOCK();
			pZone->deleteEffect_LOCKING(0);
			__LEAVE_CRITICAL_SECTION( (*(pZone->getZoneGroup())) )
		}
	}
}

int	GDRLairManager::getTotalPCs() const
{
	int ret = 0;
	for ( int i=ILLUSIONS_WAY_1; i<GDR_LAIR_MAX; ++i )
	{
		ret += m_pZones[i]->getPCManager()->getSize();
	}
	return ret;
}

bool GDRLairManager::isGDRLairZone(ZoneID_t ZoneID) const
{
	for ( int i=ILLUSIONS_WAY_1; i<GDR_LAIR_MAX; ++i )
	{
		if (m_pZones[i]->getZoneID() == ZoneID) return true;
	}

	return false;
}
