///////////////////////////////////////////////////////////////////
// 전쟁에 대한 전반적인 정보 및 전쟁 시작 및 종료시 처리루틴 구현
///////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "RaceWar.h"
#include "Mutex.h"
#include "WarSystem.h"
#include "Properties.h"
#include "DB.h"
#include "Assert.h"
#include "ZoneGroupManager.h"
//#include "HolyLandRaceBonus.h"
#include "Zone.h"
#include "ZoneGroup.h"
#include "ZoneUtil.h"
#include "CastleInfoManager.h"
#include "ShrineInfoManager.h"
#include "ZoneInfoManager.h"
#include "PCManager.h"
#include "Gpackets/GCWarScheduleList.h"
#include "RaceWarInfo.h"
#include "HolyLandManager.h"
#include "VariableManager.h"
#include "RaceWarLimiter.h"
#include "RegenZoneManager.h"
#include "DragonEyeManager.h"

#include "StringStream.h"

#include "Gpackets/GCSystemMessage.h"
#include "Gpackets/GCNoticeEvent.h"
#include "Cpackets/CGSay.h"

//--------------------------------------------------------------------------------
//
// constructor / destructor
//
//--------------------------------------------------------------------------------
RaceWar::RaceWar( WarState warState, WarID_t warID )
: War( warState, warID )
{
}

RaceWar::~RaceWar()
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
void RaceWar::executeStart()
	throw (Error)
{
	__BEGIN_TRY

	sendWarStartMessage();

	// 종족전에서는 보너스를 끈다.
//	g_pHolyLandRaceBonus->clear();

	// 전쟁 중에는 NPC가 사라진다.
	//g_pCastleInfoManager->deleteAllNPCs();

	// 전쟁 중에는 성 안에서 마구 싸운다~
	g_pCastleInfoManager->releaseAllSafeZone();

	// 수호성단 보호막이 모두 사라진다.
	g_pShrineInfoManager->removeAllShrineShield();

	// 아담의 성지 전역에 피의 성서 위치를 보내준다.
	// 이거 이제 WarSystem::addWar 안에서 불러준다.
	// g_pShrineInfoManager->broadcastBloodBibleStatus();
//	g_pHolyLandManager->sendBloodBibleStatus();

	// 아담의 성지 전역에 시간을 고정한다.
	g_pHolyLandManager->fixTimeband( g_pVariableManager->getVariable( RACE_WAR_TIMEBAND ) );

	g_pHolyLandManager->killAllMonsters();

	RegenZoneManager::getInstance()->putTryingPosition();
	RegenZoneManager::getInstance()->broadcastStatus();

	// 드래곤 아이 아이템을 초기 위치에 둔다.
	g_pDragonEyeManager->addAllDragonEyesToZone();

	// hasActiveRaceWar()가 설정되는 타이밍 때문에..
	// WarSystem::addWar()에서 실행한다.
	// 종족 전쟁에 참가하지 않는 사람들을 내보낸다.
	//g_pHolyLandManager->remainRaceWarPlayers();

	// RaceWarHistory Table 에 기록
	recordRaceWarStart();

	__END_CATCH
}

void RaceWar::recordRaceWarStart()
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result* pResult  = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT Race, SUM(CurrentNum) FROM RaceWarPCLimit GROUP BY Race");

		uint slayerSum  = 0;
		uint vampireSum = 0;
		uint oustersSum = 0;

		string slayerOld;
		string vampireOld;
		string oustersOld;

		while (pResult->next())
		{
			uint race = pResult->getInt(1);
			uint num  = pResult->getInt(2);

			if ( race == 0 )
				slayerSum = num;
			else if ( race == 1 )
				vampireSum = num;
			else if ( race == 2 )
				oustersSum = num;
		}

		pResult = pStmt->executeQuery("SELECT ID, OwnerRace FROM ShrineInfo");

		while (pResult->next())
		{
			uint id   		= pResult->getInt(1);
			uint ownerRace	= pResult->getInt(2);

			if ( ownerRace == 0 )
				slayerOld = slayerOld + itos(id) + "|";
			else if ( ownerRace == 1 )
				vampireOld = vampireOld + itos(id) + "|";
			else if ( ownerRace == 2 )
				oustersOld = oustersOld + itos(id) + "|";
		}

		pStmt->executeQuery("INSERT INTO RaceWarHistory (RaceWarID, SlayerNum, VampireNum, OustersNum, SlayerOldBloodBible, VampireOldBloodBible, OustersOldBloodBible) VALUES ('%s', %d, %d, %d, '%s', '%s', '%s')",
						getWarStartTime().toStringforWeb().c_str(),
						slayerSum, vampireSum, oustersSum,
						slayerOld.c_str(),
						vampireOld.c_str(),
						oustersOld.c_str() );
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
void RaceWar::executeEnd()
	throw (Error)
{
	__BEGIN_TRY

	//----------------------------------------------------------------------------
	// 전쟁 끝났다는 걸 알린다.
	//----------------------------------------------------------------------------
	sendWarEndMessage();

	//----------------------------------------------------------------------------
	// 종족전인 경우 처리
	//----------------------------------------------------------------------------
	// 전쟁 신청금 쌓인거는 어떻게 할까? 무시 _-_;
	// 종족전에서는 꺼진 보너스를 다시 켠다.
//	g_pHolyLandRaceBonus->refresh();

	//----------------------------------------------------------------------------
	// 피의 성서 조각을 되돌려준다.
	//----------------------------------------------------------------------------
	g_pShrineInfoManager->returnAllBloodBible();

	g_pShrineInfoManager->addAllShrineShield();
	
	g_pCastleInfoManager->resetAllSafeZone();

	g_pCastleInfoManager->transportAllOtherRace();

	//g_pCastleInfoManager->loadAllNPCs();

	// 아담의 성지 전역에 피의 성서 위치를 보내준다.
	//g_pHolyLandManager->sendBloodBibleStatus();
	g_pShrineInfoManager->broadcastBloodBibleStatus();

	// 아담의 성지 전역에 고정했던 시간을 다시 돌린다.
	g_pHolyLandManager->resumeTimeband();

	// 전쟁 참가자 리스트를 모두 제거한다.
	RaceWarLimiter::clearPCList();

	// 참가자 숫자를 0으로 바꾼다.
	RaceWarLimiter::getInstance()->clearCurrent();
	RegenZoneManager::getInstance()->deleteTryingPosition();
	RegenZoneManager::getInstance()->reload();

	// 캐릭터들의 Flag도 모두 제거한다.
	g_pZoneGroupManager->removeFlag( Effect::EFFECT_CLASS_RACE_WAR_JOIN_TICKET );

	CGSayHandler::opworld(NULL, "*world *load blood_bible_owner", 0, true);

	// 드래곤 아이 아이템을 없앤다.
	g_pDragonEyeManager->removeAllDragonEyes();

	// RaceWarHistory Table 에 기록
	recordRaceWarEnd();

	__END_CATCH
}

void RaceWar::recordRaceWarEnd()
	throw (Error)
{
	__BEGIN_TRY

	Statement* pStmt = NULL;
	Result* pResult  = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pResult = pStmt->executeQuery("SELECT ID, OwnerRace FROM ShrineInfo");

		string slayerNew;
		string vampireNew;
		string oustersNew;

		while (pResult->next())
		{
			uint id   		= pResult->getInt(1);
			uint ownerRace	= pResult->getInt(2);

			if ( ownerRace == 0 )
				slayerNew = slayerNew + itos(id) + "|";
			else if ( ownerRace == 1 )
				vampireNew = vampireNew + itos(id) + "|";
			else if ( ownerRace == 2 )
				oustersNew = oustersNew + itos(id) + "|";
		}

		pStmt->executeQuery("UPDATE RaceWarHistory SET SlayerBloodBible = '%s', VampireBloodBible = '%s', OustersBloodBible = '%s' WHERE RaceWarID = '%s'",
						slayerNew.c_str(),
						vampireNew.c_str(),
						oustersNew.c_str(),
						getWarStartTime().toStringforWeb().c_str() );
	}
	END_DB(pStmt)

	// script 돌리기 ㅡ.,ㅡ system 함수를 쓰게 될 줄이야 !_!
	char cmd[100];
	sprintf(cmd, "/home/darkeden/vs/bin/script/recordRaceWarHistory.py %s %d %d ",
					getWarStartTime().toStringforWeb().c_str(),
					g_pConfig->getPropertyInt("Dimension"),
					g_pConfig->getPropertyInt("WorldID") );

	filelog("script.log", cmd);
	system(cmd);
	
	__END_CATCH
}

string RaceWar::getWarName() const
	throw (Error)
{
	__BEGIN_TRY

	return "蘆痢쇌濫轢";

	__END_CATCH
}

//--------------------------------------------------------------------------------
// 전쟁 끝날 때
//--------------------------------------------------------------------------------
void RaceWar::sendWarEndMessage() const
    throw (ProtocolException, Error)
{
    __BEGIN_TRY

	War::sendWarEndMessage();

	// 안전지대 해제 확인? 패킷
	GCNoticeEvent gcNoticeEvent;
	gcNoticeEvent.setCode( NOTICE_EVENT_RACE_WAR_OVER );
	g_pZoneGroupManager->broadcast( &gcNoticeEvent );

    __END_CATCH
}


void    RaceWar::makeWarScheduleInfo( WarScheduleInfo* pWSI ) const 
	throw (Error)
{
	__BEGIN_TRY

    pWSI->warType 				= getWarType();
//    pWSI->challengerGuildID		= 0;
 //   pWSI->challengerGuildName	= "";

	__END_CATCH
}

void 	RaceWar::makeWarInfo(WarInfo* pWarInfo) const 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pWarInfo!=NULL);
	Assert(pWarInfo->getWarType()==WAR_RACE);

	RaceWarInfo* pRaceWarInfo = dynamic_cast<RaceWarInfo*>(pWarInfo);
	Assert(pRaceWarInfo!=NULL);

	const hash_map<ZoneID_t, CastleInfo*>& castleInfos = g_pCastleInfoManager->getCastleInfos();

	hash_map<ZoneID_t, CastleInfo*>::const_iterator itr = castleInfos.begin();

	for ( ; itr!=castleInfos.end(); itr++)
	{
		CastleInfo* pCastleInfo = itr->second;
		pRaceWarInfo->addCastleID( pCastleInfo->getZoneID() );
	}

	__END_CATCH
}


string RaceWar::toString() const
	throw (Error)
{
	__BEGIN_TRY

	StringStream msg;
	
	msg << "RaceWar("
		<< "WarID:" << (int)getWarID()
		<< ",State:" << (int)getState()
		<< ")";

	return msg.toString();

	__END_CATCH
}
