#include "FlagWar.h"
#include "FlagManager.h"
#include "ItemFactoryManager.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "ZoneInfoManager.h"
#include "GlobalItemPositionLoader.h"
#include "MonsterSummonInfo.h"

#include "ZoneGroupManager.h"
#include "Gpackets/GCNoticeEvent.h"

list<FlagWar::FlagGenZone> FlagWar::m_FlagGenInfo;

void FlagWar::execute() 
{
	__BEGIN_TRY

	switch ( getState() )
	{
		case STATE_WAIT :
			filelog( "FlagWar.log", "FlagWar Ready.." );
			executeReady();
			setState( STATE_READY );
			break;
		case STATE_READY :
			filelog( "FlagWar.log", "FlagWar Start.." );
			executeStart();
			setState( STATE_START );
			break;
		case STATE_START :
			filelog( "FlagWar.log", "FlagWar Finising.." );
			executeFinish();
			setState( STATE_FINISH );
			break;
		case STATE_FINISH :
			filelog( "FlagWar.log", "FlagWar End.." );
			executeEnd();
			setState( STATE_WAIT );
			break;
		default :
			filelog( "FlagWar.log", "이상한 FlagWar 상태.." );
			break;
	}

	__END_CATCH
}

void FlagWar::executeReady() 
{
	__BEGIN_TRY


	GCNoticeEvent gcNE;
	gcNE.setCode( NOTICE_EVENT_FLAG_WAR_READY );

	VSDateTime current = VSDateTime::currentDateTime();
	gcNE.setParameter( ((DWORD)((DWORD)(current.date().year() - 2000))*1000000) + ((DWORD)((DWORD)current.date().month())*10000)
					   + ((DWORD)((DWORD)current.date().day())*100) + ((DWORD)((DWORD)current.time().hour())) );

	g_pZoneGroupManager->broadcast( &gcNE );

	// 5분있다가 시작하자
	g_pFlagManager->addSchedule( new Schedule( this, VSDateTime::currentDateTime().addSecs(300) ) );

	__END_CATCH
}

void FlagWar::addFlagsRandom( ZoneID_t zoneID, uint no )
{
	Zone* pZone = getZoneByZoneID( zoneID );
	Assert( pZone != NULL );
	VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);
	BPOINT pt;

	pZone->lock();

	for ( uint i=0; i<no; ++i )
	{
		pt.x = rand()%pZone->getWidth();
		pt.y = rand()%pZone->getHeight();

		while ( !rect.ptInRect(pt.x, pt.y) || pZone->getTile(pt.x, pt.y).hasItem() || pZone->getTile(pt.x, pt.y).isBlocked(Creature::MOVE_MODE_WALKING) 
				|| ( (pZone->getZoneLevel(pt.x, pt.y))&SAFE_ZONE == 0 ) )
		{
			pt.x = rand()%pZone->getWidth();
			pt.y = rand()%pZone->getHeight();
		}

		Item* pItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_ITEM, 27, list<OptionType_t>() );
		Assert( pItem != NULL );

		pZone->registerObject( pItem );
		TPOINT ptInZone = pZone->addItem( pItem, pt.x, pt.y, true, 36000 );
		pItem->create( "", STORAGE_ZONE, pZone->getZoneID(), ptInZone.x, ptInZone.y );

		filelog( "FlagWar.log", "%d : (%d,%d) 에 깃발이 만들어졌습니다.", pZone->getZoneID(), ptInZone.x, ptInZone.y );

		m_Flags.push_back( pItem->getItemID() );
	}

	pZone->unlock();

	g_pFlagManager->getAllowMap()[zoneID] = no;
}

void FlagWar::executeStart() 
{
	__BEGIN_TRY

	GCNoticeEvent gcNE;
	gcNE.setCode( NOTICE_EVENT_FLAG_WAR_START );

	VSDateTime current = VSDateTime::currentDateTime();
	gcNE.setParameter( ((DWORD)((DWORD)(current.date().year() - 2000))*1000000) + ((DWORD)((DWORD)current.date().month())*10000)
					   + ((DWORD)((DWORD)current.date().day())*100)    + ((DWORD)((DWORD)current.time().hour())) );

	g_pZoneGroupManager->broadcast( &gcNE );
	
	m_Flags.clear();
	g_pFlagManager->getAllowMap().clear();

	addFlags();
//	addFlagsRandom( 1122, 20 );

	// 랜덤하게 존을 선택해서 100개의 깃발을 생성한다.
	// 2시간 하자
	g_pFlagManager->addSchedule( new Schedule( this, VSDateTime::currentDateTime().addSecs(getWarTime()) ) );
	g_pFlagManager->startFlagWar();

	__END_CATCH
}

void FlagWar::executeFinish() 
{
	__BEGIN_TRY

	GCNoticeEvent gcNE;
	gcNE.setCode( NOTICE_EVENT_FLAG_WAR_FINISH );

	Race_t winnerRace = g_pFlagManager->getWinnerRace();
	gcNE.setParameter( ((DWORD)((DWORD)winnerRace << 16)) | (DWORD)g_pFlagManager->getFlagCount( winnerRace ) );

	g_pZoneGroupManager->broadcast( &gcNE );
	
	// 3분있다가 아템 터친다.
	g_pFlagManager->addSchedule( new Schedule( this, VSDateTime::currentDateTime().addSecs(180) ) );
	g_pFlagManager->endFlagWar();

	__END_CATCH
}

void FlagWar::executeEnd() 
{
	__BEGIN_TRY

	// 생성했던 깃발들을 쫓아가서 다 지워뿐다.
	vector<ItemID_t>::iterator itr = m_Flags.begin();
	vector<ItemID_t>::iterator endItr = m_Flags.end();
	
	for ( ; itr != endItr ; ++itr )
	{
		GlobalItemPosition* pItemPosition = GlobalItemPositionLoader::getInstance()->load( Item::ITEM_CLASS_EVENT_ITEM, *itr );
		if ( pItemPosition == NULL ) continue;

		// popItem은 아템을 해당 위치에서 뽑아내므로 지워버려도 된다.
		// 이건 FlagManager 가 도는 스레드에서 불러지므로 안에서 락걸어줘야 된다.
		Item* pItem = pItemPosition->popItem( true );
		if ( pItem != NULL )
		{
			pItem->destroy();
			SAFE_DELETE(pItem);
		}
		else
		{
			filelog( "FlagWar.log", "깃발 아이템 추적 실패... ㅜ.ㅠ");
		}
	}

	g_pFlagManager->resetFlagCounts();
	m_Flags.clear();

	// 다음을 기약하자
	g_pFlagManager->addSchedule( new Schedule( this, getNextFlagWarTime() ) );

/*	ZoneCoord_t	ZoneX, ZoneY;

	switch ( g_pFlagManager->getWinnerRace() )
	{
		case RACE_SLAYER:
			ZoneX = 90;
			ZoneY = 50;
			break;

		case RACE_VAMPIRE:
			ZoneX = 24;
			ZoneY = 52;
			break;

		case RACE_OUSTERS:
			ZoneX = 30;
			ZoneY = 86;
			break;

		default:
			return;
	}

	SUMMON_INFO summonInfo;
	summonInfo.canScanEnemy = false;
	summonInfo.clanType = SUMMON_INFO::CLAN_TYPE_DEFAULT;

	addMonstersToZone(getZoneByZoneID(1122), ZoneX, ZoneY, 0, 599, 1, summonInfo);*/

	__END_CATCH
}

VSDateTime FlagWar::getNextFlagWarTime()
{
	static const int NextFlagWarDay[8] =
	{
		0, 0, 1, 0, 1, 0, 0, 0
	};

	VSDateTime dt = VSDateTime::currentDateTime();

	VSDateTime nextWarDateTime;
	nextWarDateTime = dt.addDays( NextFlagWarDay[dt.date().dayOfWeek()] );

	if ( nextWarDateTime.date().dayOfWeek() < 6 )
		nextWarDateTime.setTime( VSTime( 18, 55, 0 ) );
	else
		nextWarDateTime.setTime( VSTime( 13, 55, 0 ) );

	if ( nextWarDateTime < VSDateTime::currentDateTime() )
	{
		bool anotherDay = true;
		if ( nextWarDateTime.date().dayOfWeek() == 6 )
		{
			nextWarDateTime.setTime( VSTime( 18, 55, 0 ) );
			if ( nextWarDateTime >= VSDateTime::currentDateTime() ) anotherDay = false;
		}

		if ( anotherDay )
		{
			//nextWarDateTime = nextWarDateTime.addDays( NextWarDay[warType][dt.addDays(1).date().dayOfWeek()] );
			nextWarDateTime = nextWarDateTime.addDays( 1 );
			nextWarDateTime = nextWarDateTime.addDays( NextFlagWarDay[nextWarDateTime.date().dayOfWeek()] );

			if ( nextWarDateTime.date().dayOfWeek() < 6 )
				nextWarDateTime.setTime( VSTime( 18, 55, 0 ) );
			else
				nextWarDateTime.setTime( VSTime( 13, 55, 0 ) );
		}
	}

	//cout << nextWarDateTime.toString() << "에 깃발 전쟁 시작함당~" << endl;
	filelog( "FlagWar.log", "%s에 깃발 뺏기 이벤트 시작", nextWarDateTime.toString().c_str() );

	return nextWarDateTime;
}

void FlagWar::addFlags()
{
	addFlagsRandom( 21, 6 );
	addFlagsRandom( 22, 6 );
	addFlagsRandom( 23, 6 );
	addFlagsRandom( 24, 7 );

	addFlagsRandom( 11, 7 );
	addFlagsRandom( 12, 6 );
	addFlagsRandom( 13, 6 );
	addFlagsRandom( 14, 6 );

	addFlagsRandom( 31, 6 );
	addFlagsRandom( 32, 6 );
	addFlagsRandom( 33, 7 );
	addFlagsRandom( 34, 6 );

	addFlagsRandom( 61, 11 );
	addFlagsRandom( 62, 11 );
	addFlagsRandom( 63, 12 );
	addFlagsRandom( 64, 11 );
}

int FlagWar::getWarTime() const { return 7200; }
