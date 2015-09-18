#include <stdio.h>
#include "DB.h"
#include "Properties.h"
#include "Player.h"
#include "PlayerCreature.h"
#include "ZoneGroupManager.h"
#include "StringPool.h"
#include "LevelWar.h"
#include "LevelWarInfo.h"
#include "LevelWarManager.h"
#include "LevelWarZoneInfoManager.h"
#include "SweeperBonusManager.h"
#include "VariableManager.h"

#include "GCNoticeEvent.h"
#include "GCSystemMessage.h"
#include "GCSweeperBonusInfo.h"

#include "CGSay.h"

// 전쟁 하는 날짜
int LevelWarTime[4][3] = {
	{ 2,20, 0 }, // 화요일 8시
	{ 4,20, 0 }, // 목요일 8시
	{ 2,21, 0 }, // 화요일 9시
	{ 4,21, 0 }, // 목요일 9시
};

void LevelWarManager::init() 
{ 
	m_SweeperSetManager.load(m_Level, m_pZone); 

	SAFE_DELETE(m_pLevelWarSchedule);

	VSDateTime warStartTime = getNextLevelWarTime();
	m_pLevelWarSchedule = new Schedule(new LevelWar(this ), warStartTime);

	filelog("WarLog.txt", "[Level=%d, Time=%s] 레벨별 전쟁을 추가합니다.", m_Level, warStartTime.toString().c_str());

	addSchedule(m_pLevelWarSchedule);
}

Work* LevelWarManager::heartbeat() 
	throw(Error)
{
	Work* pWork = NULL;
	pWork = Scheduler::heartbeat();

	if (m_pLevelWarSchedule!=NULL 
		&& !m_bHasWar
		&& g_pVariableManager->isActiveLevelWar() )
	{
		m_bHasWarToDay = VSDateTime::currentDateTime().daysTo(m_pLevelWarSchedule->getScheduledTime() ) <= 3;
	}

	if (m_bHasWar )
	{
		// 전쟁이 있으면 GCWarList 를 갱신해준다
		makeGCWarList();
	}

	return pWork;
}

void LevelWarManager::startWar()
{ 
	m_bHasWar = true;

	// 현재 시간을 start time 으로 기록해둔다. 
	// startTime 과 Level 이 기록을 남길 때 꼭 필요하다.
	setLevelWarStartTime(VSDateTime::currentDateTime());

	int year = VSDate::currentDate().year() - 2000;
	int month = VSDate::currentDate().month();
	int day = VSDate::currentDate().day();
	int hour = VSTime::currentTime().hour();
	int level = 0; 
	if (m_pZone->getZoneID() == 1131)
		level = 1;
	else if (m_pZone->getZoneID() == 1132)
		level = 2;
	else if (m_pZone->getZoneID() == 1133)
		level = 3;
	else if (m_pZone->getZoneID() == 1134)
		level = 4;

	fixTimeband(g_pVariableManager->getVariable(RACE_WAR_TIMEBAND ));

	killAllMonsters();

	GCNoticeEvent gcNoticeEvent;
	gcNoticeEvent.setCode(NOTICE_EVENT_LEVEL_WAR_STARTED);
//	gcNoticeEvent.setParameter(((DWORD)((DWORD)month << 24)) | ((DWORD)((DWORD)day << 16)) | ((DWORD)((DWORD)hour << 8)) | ((DWORD)((DWORD)level)));
	gcNoticeEvent.setParameter((level * 100000000) + (year * 1000000) + (month * 10000) + (day * 100) + hour);
	g_pZoneGroupManager->broadcast(&gcNoticeEvent);

	GCSweeperBonusInfo gcSweeperBonusInfo;
	g_pSweeperBonusManager->makeVoidSweeperBonusInfo(gcSweeperBonusInfo);
	g_pLevelWarZoneInfoManager->broadcast(m_pZone->getZoneID(), &gcSweeperBonusInfo);

	// 기록 남긴다.
	recordLevelWarStart();

}

void LevelWarManager::recordLevelWarStart()
{

	Statement* pStmt = NULL;
    Result* pResult  = NULL;

	BEGIN_DB
    {
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT SweeperType, OwnerRace FROM SweeperOwnerInfo WHERE ZoneID = %d", m_pZone->getZoneID());

		string slayerOld;
		string vampireOld;
		string oustersOld;
		string defaultOld;

		while (pResult->next())
		{
			uint id 		= pResult->getInt(1);
			uint ownerRace 	= pResult->getInt(2);

			if (ownerRace == 0 )
				slayerOld = slayerOld + itos(id) + "|";
			else if (ownerRace == 1 )
				vampireOld = vampireOld + itos(id) + "|";
			else if (ownerRace == 2 )
				oustersOld = oustersOld + itos(id) + "|";
			else
				defaultOld = defaultOld + itos(id) + "|";
		}

		pStmt->executeQuery("INSERT INTO LevelWarHistory (Level, LevelWarID, SlayerOldSweeper, VampireOldSweeper, OustersOldSweeper, DefaultOldSweeper) VALUES (%d, '%s', '%s', '%s', '%s', '%s')",
					m_Level,
					getLevelWarStartTime().toStringforWeb().c_str(),
					slayerOld.c_str(),
					vampireOld.c_str(),
					oustersOld.c_str(),
					defaultOld.c_str());
		
	}
	END_DB(pStmt)

}

void LevelWarManager::manualStart()
{
	if (!isEmpty() )
	{
		addSchedule(new Schedule(popRecentWork(), VSDateTime::currentDateTime() ));
	}
	else
	{
		m_pLevelWarSchedule = new Schedule(new LevelWar(this ), VSDateTime::currentDateTime());
		addSchedule(m_pLevelWarSchedule);
	}
}

void LevelWarManager::endWar()
{ 
	m_bHasWar = false; 
	m_SweeperSetManager.returnAllSweeper();

	resumeTimeband();

	GCSweeperBonusInfo gcSweeperBonusInfo;
	g_pSweeperBonusManager->makeSweeperBonusInfo(gcSweeperBonusInfo);
	g_pLevelWarZoneInfoManager->broadcast(m_pZone->getZoneID(), &gcSweeperBonusInfo);

	GCNoticeEvent gcNoticeEvent;
	gcNoticeEvent.setCode(NOTICE_EVENT_LEVEL_WAR_OVER);
	m_pZone->broadcastPacket(&gcNoticeEvent);

	VSDateTime warStartTime = getNextLevelWarTime();
	m_pLevelWarSchedule = new Schedule(new LevelWar(this ), warStartTime);

	filelog("WarLog.txt", "[Level=%d, Time=%s] 레벨별 전쟁을 추가합니다.", m_Level, warStartTime.toString().c_str());
	addSchedule(m_pLevelWarSchedule);

	char sLoad[100];
	sprintf(sLoad , "*world *load sweeper_owner %d", m_Level);
	CGSayHandler::opworld(NULL , sLoad, 0, true);

	// 기록 남긴다
	recordLevelWarEnd();
}

void LevelWarManager::recordLevelWarEnd()
{
	Statement* pStmt = NULL;
    Result* pResult  = NULL;

	BEGIN_DB
    {
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT SweeperType, OwnerRace FROM SweeperOwnerInfo WHERE ZoneID = %d", m_pZone->getZoneID());

		string slayerNew;
		string vampireNew;
		string oustersNew;
		string defaultNew;

		while (pResult->next())
		{
			uint id 		= pResult->getInt(1);
			uint ownerRace 	= pResult->getInt(2);

			if (ownerRace == 0 )
				slayerNew = slayerNew + itos(id) + "|";
			else if (ownerRace == 1 )
				vampireNew = vampireNew + itos(id) + "|";
			else if (ownerRace == 2 )
				oustersNew = oustersNew + itos(id) + "|";
			else
				defaultNew = defaultNew + itos(id) + "|";
		}

		pStmt->executeQuery("UPDATE LevelWarHistory SET SlayerSweeper = '%s', VampireSweeper = '%s', OustersSweeper = '%s', DefaultSweeper = '%s' WHERE Level = %d AND LevelWarID = '%s'",
					slayerNew.c_str(),
					vampireNew.c_str(),
					oustersNew.c_str(),
					defaultNew.c_str(), 
					m_Level,
					getLevelWarStartTime().toStringforWeb().c_str());
		
	}
	END_DB(pStmt)

	// script 돌리기 ㅡ.,ㅡ system 함수를 쓰게 될 줄이야 !_!
	char cmd[100];
	sprintf(cmd, "/home/darkeden/vs/bin/script/recordLevelWarHistory.py %d %s %d %d ",
					m_Level,
					getLevelWarStartTime().toStringforWeb().c_str(),
					g_pConfig->getPropertyInt("Dimension"),
					g_pConfig->getPropertyInt("WorldID"));

	filelog("script.log", cmd);
	system(cmd);

}

bool LevelWarManager::putSweeper(PlayerCreature* pPC, Item* pItem , MonsterCorpse* pCorpse)
{
	int race = m_SweeperSetManager.getSafeIndex(pCorpse);

	if (pPC->isSlayer() && race != 0) return false;

	if (pPC->isVampire() && race != 1) return false;

	if (pPC->isOusters() && race != 2) return false;
	
	return m_SweeperSetManager.putSweeper(pItem, pCorpse);
}

VSDateTime LevelWarManager::getNextLevelWarTime() const
{
	VSDateTime now = VSDateTime::currentDateTime();
	int dayOfWeek = now.date().dayOfWeek();
	bool isSameDay = false;

	if (dayOfWeek == LevelWarTime[m_Level-1][0] )
		isSameDay = now.time() < VSTime(LevelWarTime[m_Level-1][1], LevelWarTime[m_Level-1][2]);

	if (isSameDay ) return VSDateTime(now.date(), VSTime(LevelWarTime[m_Level-1][1], LevelWarTime[m_Level-1][2] ));

	int lastDays = LevelWarTime[m_Level-1][0] - dayOfWeek;
	if (lastDays <= 0 ) lastDays += 7;
	
	return VSDateTime(now.date().addDays(lastDays), VSTime(LevelWarTime[m_Level-1][1], LevelWarTime[m_Level-1][2] ));
}

void LevelWarManager::fixTimeband(uint timeband )
	throw(Error)
{
	__BEGIN_TRY

	Assert(m_pZone != NULL);
	m_pZone->stopTime();
	m_pZone->setTimeband(timeband);
	m_pZone->resetDarkLightInfo();

	__END_CATCH
}

void LevelWarManager::resumeTimeband()
	throw(Error)
{
	__BEGIN_TRY

	Assert(m_pZone != NULL);
	m_pZone->resumeTime();
	m_pZone->resetDarkLightInfo();

	__END_CATCH
}

void LevelWarManager::killAllMonsters()
	throw(Error)
{
	__BEGIN_TRY

	Assert(m_pZone != NULL);
	m_pZone->killAllMonsters_UNLOCK();

	__END_CATCH
}

int LevelWarManager::getStartHour()
{
	__BEGIN_TRY

	if (m_pLevelWarSchedule == NULL ) return -1;	

	return m_pLevelWarSchedule->getScheduledTime().time().hour();

	__END_CATCH
}

bool LevelWarManager::makeGCWarList()
	throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_MutexWarList)

	m_GCWarList.clear();

	if (!hasWar() )
	{
		m_MutexWarList.unlock();
		return false;
	}

	if (isEmpty() )
	{
		m_MutexWarList.unlock();
		return false;
	}

	const RecentSchedules::container_type& Schedules = m_RecentSchedules.getSchedules();
	RecentSchedules::const_iterator itr = Schedules.begin();
	RecentSchedules::const_iterator endItr = Schedules.end();

	for (; itr != endItr ; itr++)
	{
		Schedule* pSchedule = *itr;

		LevelWarInfo* pLevelWarInfo = new LevelWarInfo;

		const Work* pWork = pSchedule->getWork();
		Assert(pWork != NULL);

		VSDateTime dt(VSDateTime::currentDateTime());

		int endHour = pSchedule->getScheduledTime().time().hour();
		int endMin = pSchedule->getScheduledTime().time().minute();
		int endSec = pSchedule->getScheduledTime().time().second();

		int curHour = dt.time().hour();
		int curMin = dt.time().minute();
		int curSec = dt.time().second();

		int endSecs = endHour*60*60 + endMin*60 + endSec;
		int curSecs = curHour*60*60 + curMin*60 + curSec;

		int remainSec = 0;
		if (endSecs > curSecs) remainSec = endSecs - curSecs;

		pLevelWarInfo->setLevel(m_Level);
		pLevelWarInfo->setRemainTime(remainSec);

		if (remainSec != 0 )
			m_GCWarList.addWarInfo(pLevelWarInfo);
	}

	__LEAVE_CRITICAL_SECTION(m_MutexWarList)

	return true;
	
	__END_CATCH
}

void LevelWarManager::sendGCWarList(Player *pPlayer)
	throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_MutexWarList)

	if (!m_GCWarList.isEmpty() )
	{
		pPlayer->sendPacket(&m_GCWarList);
	}

	__LEAVE_CRITICAL_SECTION(m_MutexWarList)

	__END_CATCH
}
void LevelWarManager::broadcastGCWarList()
	throw(Error)
{
	__BEGIN_TRY

	__ENTER_CRITICAL_SECTION(m_MutexWarList)

	m_pZone->broadcastPacket(&m_GCWarList);

	__LEAVE_CRITICAL_SECTION(m_MutexWarList)

	__END_CATCH
}

void LevelWarManager::freeUserTimeCheck()
	throw(Error)
{
	__BEGIN_TRY

	int hour = VSTime::currentTime().hour();

	if (m_bCanEnterFreeUser && hour != LevelWarTime[m_Level-1][1] )
	{
		m_bCanEnterFreeUser = false;

		// Zone 에 있는 사람 다 튕겨주자.
		m_pZone->remainPayPlayer();
	}
	else if (!m_bCanEnterFreeUser && hour == LevelWarTime[m_Level-1][1] )
	{
		m_bCanEnterFreeUser = true;

		GCSystemMessage gcSystemMessage;
		char msg[100];

		sprintf(msg, g_pStringPool->c_str(STRID_LEVEL_WAR_ZONE_FREE_OPEN ), m_Level, hour, hour+1);

		gcSystemMessage.setMessage(msg);
	    g_pZoneGroupManager->broadcast(&gcSystemMessage);

	}

	__END_CATCH
}
