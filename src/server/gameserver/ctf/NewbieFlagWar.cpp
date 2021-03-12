#include "NewbieFlagWar.h"
#include "ZoneUtil.h"
#include "MonsterSummonInfo.h"
#include "Zone.h"
#include "ZoneInfoManager.h"
#include "FlagManager.h"

void NewbieFlagWar::executeEnd() 
{
	FlagWar::executeEnd();
	ZoneCoord_t	ZoneX, ZoneY;

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

	addMonstersToZone(getZoneByZoneID(1122), ZoneX, ZoneY, 0, 599, 1, summonInfo);
}

VSDateTime NewbieFlagWar::getNextFlagWarTime()
{
	static const int NextFlagWarDay[8] =
	{
		0, 1, 0, 1, 0, 4, 3, 2
	};

	VSDateTime dt = VSDateTime::currentDateTime();

	VSDateTime nextWarDateTime;
	nextWarDateTime = dt.addDays( NextFlagWarDay[dt.date().dayOfWeek()] );

	nextWarDateTime.setTime( VSTime( 18, 55, 0 ) );

	if ( nextWarDateTime < VSDateTime::currentDateTime() )
	{
		nextWarDateTime = nextWarDateTime.addDays( 1 );
		nextWarDateTime = nextWarDateTime.addDays( NextFlagWarDay[nextWarDateTime.date().dayOfWeek()] );
	}

	filelog( "FlagWar.log", "%s에 초보존 깃발 뺏기 이벤트 시작", nextWarDateTime.toString().c_str() );
	return nextWarDateTime;
}

void NewbieFlagWar::addFlags()
{
	addFlagsRandom( 1122, 20 );
}
