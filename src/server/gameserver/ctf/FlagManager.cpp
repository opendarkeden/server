#include "FlagManager.h"
#include "FlagWar.h"
#include "NewbieFlagWar.h"
#include "PlayerCreature.h"
#include "MonsterCorpse.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "DB.h"
#include "Properties.h"
#include "Player.h"
#include "EffectFlagInsert.h"
#include "EffectManager.h"
#include "NPCInfo.h"

#include "GCFlagWarStatus.h"
#include "GCDeleteInventoryItem.h"
#include "GCAddEffect.h"

#include "SystemAvailabilitiesManager.h"

#include <stdio.h>
#include <cstdlib>

FlagManager* g_pFlagManager = NULL;

FlagManager::FlagManager()
{
	m_Mutex.setName("FlagManager");
	m_FlagCount.clear();

	m_StatusPacket.setTimeRemain(0);
	m_StatusPacket.setFlagCount(RACE_SLAYER, 0);
	m_StatusPacket.setFlagCount(RACE_VAMPIRE, 0);
	m_StatusPacket.setFlagCount(RACE_OUSTERS, 0);

	m_PutTime[RACE_SLAYER] = m_PutTime[RACE_VAMPIRE] = m_PutTime[RACE_OUSTERS] = VSDateTime::currentDateTime();

	FlagWar* pFlagWar = new FlagWar();
	addSchedule(new Schedule(pFlagWar, pFlagWar->getNextFlagWarTime() ));

	pFlagWar = new NewbieFlagWar();
	addSchedule(new Schedule(pFlagWar, pFlagWar->getNextFlagWarTime() ));
}

FlagManager::~FlagManager() throw() { }

void FlagManager::init()
{
	SYSTEM_RETURN_IF_NOT(SYSTEM_FLAG_WAR);
	Statement* pStmt = NULL;
	Result* pResult  = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT ZoneID, CenterX, CenterY, Width, Height, Race-1, MonsterType FROM FlagPolePosition");

		while (pResult->next() )
		{
			ZoneID_t zoneID = (ZoneID_t) pResult->getInt(1);
			Zone* pZone = getZoneByZoneID(zoneID);

			ZoneCoord_t left = (ZoneCoord_t) pResult->getInt(2);
			ZoneCoord_t top  = (ZoneCoord_t) pResult->getInt(3);
			uint width  = (ZoneCoord_t) pResult->getInt(4);
			uint height = (ZoneCoord_t) pResult->getInt(5);
			Race_t race = (Race_t) pResult->getInt(6);
			MonsterType_t type = (MonsterType_t) pResult->getInt(7);

			addPoleField(pZone, left, top, width, height, race, type);
		}
	}
	END_DB(pStmt)
}

void FlagManager::addPoleField(Zone* pZone, ZoneCoord_t left, ZoneCoord_t top, uint width, uint height, Race_t race, MonsterType_t type )
{
	Assert(pZone != NULL);
	Assert(isValidZoneCoord(pZone, left, top ));
	Assert(isValidZoneCoord(pZone, left+width, top+height ));

	NPCInfo* pNPCInfo = new NPCInfo();
	pNPCInfo->setName("깃션");
	pNPCInfo->setNPCID(type);
	pNPCInfo->setX(left);
	pNPCInfo->setY(top);

	pZone->addNPCInfo(pNPCInfo);

	for (uint i=0; i<width; ++i )
	for (uint j=0; j<height; ++j )
	{
		MonsterCorpse* pFlagPole = new MonsterCorpse(type, "깃션", 2);
		Assert(pFlagPole != NULL);

		pFlagPole->setZone(pZone);
		pFlagPole->setShrine(true);
		pZone->registerObject(pFlagPole);

		m_FlagPoles[pFlagPole] = race;

		TPOINT tp = pZone->addItem(pFlagPole, left+(i*2), top+(j*2));
		Assert(tp.x != -1);

		forbidDarkness(pZone, tp.x, tp.y, 1);
	}

	m_PoleFields.push_back(PoleFieldInfo(pZone->getZoneID(), left, top, width*2, height*2 ));
}

void FlagManager::manualStart()
{
	if (!isEmpty() )
	{
		//cout << "스케줄 땡기기.." << endl;
		addSchedule(new Schedule(popRecentWork(), VSDateTime::currentDateTime() ));
	}
	else
	{
		//cout << "스케줄 만들기.." << endl;
		addSchedule(new Schedule(new FlagWar(), VSDateTime::currentDateTime() ));
	}
}

bool FlagManager::startFlagWar()
{
	if (m_bHasFlagWar ) return false;
	m_bHasFlagWar = true;

	Work* pWork = m_RecentSchedules.top()->getWork();
	FlagWar* pFlagWar = dynamic_cast<FlagWar*>(pWork);

	if (pFlagWar != NULL )
		m_EndTime = VSDateTime::currentDateTime().addSecs(pFlagWar->getWarTime());
	else
		m_EndTime = VSDateTime::currentDateTime().addSecs(3600);
//	m_EndTime = m_RecentSchedules.top()->getScheduledTime();

	resetFlagCounts();

	m_StatusPacket.setTimeRemain(remainWarTimeSecs());
	m_StatusPacket.setFlagCount(RACE_SLAYER, 0);
	m_StatusPacket.setFlagCount(RACE_VAMPIRE, 0);
	m_StatusPacket.setFlagCount(RACE_OUSTERS, 0);

	broadcastStatus();

	return true;
}

bool FlagManager::endFlagWar()
{
	if (m_bHasFlagWar )
	{
		recordFlagWarHistory();

		// script 돌리기 ㅡ.,ㅡ system 함수를 쓰게 될 줄이야 !_!
		char cmd[100];
		sprintf(cmd, "/home/darkeden/vs/bin/script/recordFlagWarHistory.py %s %d %d %d %d %d %d %d ",
						m_EndTime.toStringforWeb().c_str(),
						(int)getWinnerRace(),
						g_pConfig->getPropertyInt("Dimension"),
						g_pConfig->getPropertyInt("WorldID"),
						g_pConfig->getPropertyInt("ServerID"),
						m_FlagCount[SLAYER],
						m_FlagCount[VAMPIRE],
						m_FlagCount[OUSTERS]);

		filelog("script.log", cmd);
		system(cmd);

		m_bHasFlagWar = false;
		return true;
	}

	return false;
}

bool FlagManager::putFlag(PlayerCreature* pPC, MonsterCorpse* pFlagPole )
{
	if (!isFlagPole(pFlagPole ) ) return false;
	if (pPC->getRace() != m_FlagPoles[pFlagPole] ) return false;
	if (!pPC->isFlag(Effect::EFFECT_CLASS_HAS_FLAG ) ) return false;

	lock();
	m_FlagCount[(RACEINDEX)(pPC->getRace())]++;
	m_StatusPacket.setFlagCount(pPC->getRace(), m_FlagCount[(RACEINDEX)(pPC->getRace())]);
	m_PutTime[pPC->getRace()] = VSDateTime::currentDateTime();
	filelog("FlagWar.log", "%s 님이 깃발을 깃대에 꽂으셨습니당. S : %d, V : %d, O : %d", pPC->getName().c_str(),
			m_FlagCount[SLAYER], m_FlagCount[VAMPIRE], m_FlagCount[OUSTERS]);
	unlock();

	broadcastStatus();

	return true;
}

bool FlagManager::getFlag(PlayerCreature* pPC, MonsterCorpse* pFlagPole )
{
	if (!isFlagPole(pFlagPole ) ) return false;
	if (pPC->getRace() == m_FlagPoles[pFlagPole] ) return false;
	if (pPC->isFlag(Effect::EFFECT_CLASS_HAS_FLAG ) ) return false;
	if (m_FlagCount[(RACEINDEX)(m_FlagPoles[pFlagPole])] == 0 ) return false;

	lock();
	m_FlagCount[(RACEINDEX)(m_FlagPoles[pFlagPole])]--;
	m_StatusPacket.setFlagCount(m_FlagPoles[pFlagPole], m_FlagCount[(RACEINDEX)(m_FlagPoles[pFlagPole])]);
	filelog("FlagWar.log", "%s 님이 깃발을 뽑으셨습니당. S : %d, V : %d, O : %d", pPC->getName().c_str(),
			m_FlagCount[SLAYER], m_FlagCount[VAMPIRE], m_FlagCount[OUSTERS]);
	unlock();

	broadcastStatus();

	return true;
}

bool FlagManager::putFlag(PlayerCreature* pPC, Item* pItem, MonsterCorpse* pFlagPole )
{
	Assert(pItem->getObjectID() == pPC->getExtraInventorySlotItem()->getObjectID());

	if (pPC->getRace() != getFlagPoleRace(pFlagPole ) ) return false;
	if (pFlagPole->getTreasureCount() != 0 ) return false;
	if (!putFlag(pPC, pFlagPole ) ) return false;

	pPC->deleteItemFromExtraInventorySlot();
	GCDeleteInventoryItem gcDeleteInventoryItem;
	gcDeleteInventoryItem.setObjectID(pItem->getObjectID());

	pPC->getPlayer()->sendPacket(&gcDeleteInventoryItem);

	Effect* pEffect = pPC->findEffect(Effect::EFFECT_CLASS_HAS_FLAG);
	if (pEffect != NULL ){
		//cout << "이펙트도 없애주고.." << endl;
		pEffect->setDeadline(0);
	}

	pFlagPole->addTreasure(pItem);

	pFlagPole->setFlag(Effect::EFFECT_CLASS_FLAG_INSERT);
	EffectFlagInsert* pFlagEffect = new EffectFlagInsert(pFlagPole);
	pFlagPole->getEffectManager().addEffect(pFlagEffect);

	GCAddEffect gcAddEffect;
	gcAddEffect.setEffectID(Effect::EFFECT_CLASS_FLAG_INSERT);
	gcAddEffect.setObjectID(pFlagPole->getObjectID());
	gcAddEffect.setDuration(65535);

	recordPutFlag(pPC, pItem);

	pFlagPole->getZone()->broadcastPacket(pFlagPole->getX(), pFlagPole->getY(), &gcAddEffect);

	return true;
}

Race_t FlagManager::getWinnerRace()
{
	uint max = 0;
	RACEINDEX maxRace = SLAYER;

	map<RACEINDEX,uint>::const_iterator itr = m_FlagCount.begin();
	map<RACEINDEX,uint>::const_iterator endItr = m_FlagCount.end();

	for (; itr != endItr; ++itr )
	{
		if (itr->second > max ) { maxRace = itr->first; max = itr->second; }
		if (itr->second == max )
		{
			if (m_PutTime[(Race_t)itr->first] > m_PutTime[(Race_t)maxRace] ){ maxRace = itr->first; max = itr->second; }
		}
	}

	return (Race_t)maxRace;
}

/*VSDateTime FlagManager::getNextFlagWarTime()
{
}*/

void FlagManager::resetFlagCounts()
{
	m_FlagCount[SLAYER] = 0;
	m_FlagCount[VAMPIRE] = 0;
	m_FlagCount[OUSTERS] = 0;

	// 추적 실패한 깃발들을 지워주는 일이 필요한 거 같다
	// 필드의 깃발들은 문제가 없지만 깃대에 꽂힌 깃발은 반드시 지워줘야 한다
	list<PoleFieldInfo>::iterator itr = m_PoleFields.begin();
	list<PoleFieldInfo>::iterator endItr = m_PoleFields.end();
	for (; itr != endItr; ++itr )
	{
		Zone* pZone = getZoneByZoneID(itr->zoneID);

		ZoneCoord_t ix, iy;
		for(ix = itr->l ; ix <= (itr->l + itr->w*2) ; ix+=2 )
		for(iy = itr->t ; iy <= (itr->t + itr->h*2) ; iy+=2 )
		{
			if (!isValidZoneCoord(pZone, ix, iy ) ) continue;
			Tile& tile = pZone->getTile(ix, iy);
			Item* pCorpse = tile.getItem();
			if (pCorpse == NULL 
				|| pCorpse->getItemClass() != Item::ITEM_CLASS_CORPSE
				|| pCorpse->getItemType() != MONSTER_CORPSE )
			{
				continue;
			}

			MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pCorpse);
			Item* pItem = pMonsterCorpse->getTreasure();

			if (pItem != NULL 
				&& pItem->getItemClass() == Item::ITEM_CLASS_EVENT_ITEM
				&& pItem->getItemType() == 27)
			{
				pZone->deleteItem(pItem, ix, iy);
				pItem->destroy();
				SAFE_DELETE(pItem);
			}
		}
	}

	// Reset 할 때 FlagWarStat 테이블을 정리한다
	Statement* pStmt = NULL;
	Result* pResult  = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("DELETE FROM FlagWarStat");
	}
	END_DB(pStmt)
}

bool FlagManager::isInPoleField(ZONE_COORD zc )
{
	list<PoleFieldInfo>::iterator itr = m_PoleFields.begin();
	list<PoleFieldInfo>::iterator endItr = m_PoleFields.end();

	for (; itr != endItr; ++itr )
	{
		if (itr->isInField(zc) ) return true;
	}

	return false;
}

void FlagManager::recordPutFlag(PlayerCreature* pPC, Item* pItem ) 
	throw(Error)
{
	Statement* pStmt = NULL;
	Result* pResult  = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT Name FROM FlagWarStat WHERE Name = '%s' AND ItemID = %d", 
								pPC->getName().c_str(), 
								pItem->getItemID());

		// 있으면 무시 없으면 INSERT
		if (!pResult->next() )
		{
			pResult = pStmt->executeQuery("INSERT INTO FlagWarStat (PlayerID, Name, Race, ServerID, ItemID) VALUES ('%s','%s',%d,%d,%d)",
									pPC->getPlayer()->getID().c_str(),
									pPC->getName().c_str(),
									(int)pPC->getRace(),
									g_pConfig->getPropertyInt("ServerID"),
									pItem->getItemID());
		}

	}
	END_DB(pStmt)
}

void FlagManager::recordFlagWarHistory()
	throw(Error)
{
	Statement* pStmt = NULL;
	Statement* pStmt2 = NULL;

	Result* pResult  = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt2 = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pResult = pStmt->executeQuery("SELECT PlayerID, Name, Race, ServerID, count(*) FROM FlagWarStat GROUP BY Name, ServerID");

		while (pResult->next())
		{
			string playerID = pResult->getString(1);
			string name 	= pResult->getString(2);
			Race_t race		= pResult->getInt(3);
			int    serverID = pResult->getInt(4);
			int    num		= pResult->getInt(5);

			pStmt2->executeQuery("INSERT INTO FlagWarHistory (FlagWarID, PlayerID, Name, Race, ServerID, FlagNum) VALUES ('%s','%s','%s',%d,%d,%d)",
							m_EndTime.toStringforWeb().c_str(),
							playerID.c_str(),
							name.c_str(),
							(int)race,
							serverID,
							num);
		}

		SAFE_DELETE(pStmt2);
	}
	END_DB(pStmt)
}

void FlagManager::broadcastPacket(Packet* pPacket ) const
{
	map<ZoneID_t, uint>::const_iterator itr = m_FlagAllowMap.begin();
	map<ZoneID_t, uint>::const_iterator endItr = m_FlagAllowMap.end();

	for (; itr != endItr ; ++itr )
	{
		Zone* pZone = getZoneByZoneID(itr->first);
		pZone->broadcastPacket(pPacket);
	}
}
