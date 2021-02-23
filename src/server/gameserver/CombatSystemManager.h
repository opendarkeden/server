//////////////////////////////////////////////////////////////////////////////////////////
//
// Filename    : CombatSystemManager.h
// Written by  : intblue@metrotech.co.kr
// Description : 전투 시스템 매니저
//
//////////////////////////////////////////////////////////////////////////////////////////

#ifndef __COMBAT_SYSTEM_MANAGER_H__
#define __COMBAT_SYSTEM_MANAGER_H__

#include <time.h>

#include "ThreadManager.h"
#include "ThreadPool.h"
#include "ZoneGroupThread.h"
#include "ZoneGroup.h"
#include "Zone.h"
#include "ZonePlayerManager.h"
#include "Gpackets/GCSystemMessage.h"
#include "Packet.h"
#include "Mutex.h"

//////////////////////////////////////////////////////////////////////
//
// class CombatSystemManager;
//
// 전투 시스템을 관리하는 매니저 객체
//
//////////////////////////////////////////////////////////////////////
const int VAMPIRE_HAS_SLAYER_HP_RELIC_POINT = 30;
const int VAMPIRE_HAS_SLAYER_TO_HIT_RELIC_POINT = 15;
const int SLAYER_HAS_VAMPIRE_HP_RELIC_POINT = 30;
const int SLAYER_HAS_VAMPIRE_TO_HIT_RELIC_POINT = 15;

const int RELIC_STAY_ON_BASE      = 0;
const int SAME_RACE_HAVE_RELIC    = 1;
const int ANOTHER_RACE_HAVE_RELIC = 2;
const int RELIC_STAY_ON_ZONE      = 3;

const string RELIC1NAME = "롬멜훈장";
const string RELIC2NAME = "성의";
const string RELIC3NAME = "처녀의피";
const string RELIC4NAME = "역십자가";

class CombatSystemManager {
	public:
		CombatSystemManager() throw();
		~CombatSystemManager() throw();

		void CheckCombat() throw(Error); // 전투 활성화 여부 체크하여 생성/파괴 실시

		void ActiveCombat() throw(Error); // 전투 개시
		void DeactiveCombat() throw(Error); // 전투 종료

		void BroadcastPacket(Packet*) throw(Error); // 모든 존의 사용자에게 메시지 전달
		void BroadcastPacket(Packet*, int condition, int minute) throw(Error); // 모든 존의 사용자에게 메시지 전달

		void ActiveMonster(); // 전투 몬스터 생성
		void DeactiveMonster(); // 전투 몬스터 파괴

		// Relic의 상태 파악
		// 0: 성물 보관대에 소유
		// 1: 자신의 종족이 가지고 있음
		// 2: 타종족이 가지고 있음
		// 3: 바닥에 떨어져 있음
	    int  getRelicStatus(int RelicIndex) { return m_RelicStatus[RelicIndex]; }
		void setRelicStatus(int Relic, int Status) { m_RelicStatus[Relic] = Status; }

		// Relic의 소유주
		string getRelicOwner(int RelicIndex) { return m_RelicOwner[RelicIndex]; }
		void   setRelicOwner(int RelicIndex, string Owner) { m_RelicOwner[RelicIndex] = Owner; }

		// 다른 종족의 성물을 가졌을 시 보너스 포인트 계산
		int getSlayerToHitPoint() const { return m_SlayerToHitPoint; }
		void setSlayerToHitPoint(int tohit) { m_SlayerToHitPoint = tohit; }

		int getSlayerHPPoint() const { return m_SlayerHPPoint; }
		void setSlayerHPPoint(int hp) { m_SlayerHPPoint = hp; }

		int getVampireToHitPoint() const  { return m_VampireToHitPoint; }
		void setVampireToHitPoint(int tohit) { m_VampireToHitPoint = tohit; }

		int getVampireHPPoint() const  { return m_VampireHPPoint; }
		void setVampireHPPoint(int hp) { m_VampireHPPoint = hp; }

		//bool getRelicAttacked() const { return m_RelicAttacked; }
		//void setRelicAttacked(bool attack) { m_RelicAttacked = attack; }

		//bool getRelicMoved() const { return m_RelicMoved; }
		//void setRelicMoved(bool move) { m_RelicMoved = move; }

		bool isCombatFlag() const { return m_bCombat; }
		bool isCombatStartFlag() const { return m_bCombatActive; }
		bool isCombatEndFlag() const { return m_bCombatDeactive; }

		void setCombatActivate() { m_bCombatActive = true; m_bCombatDeactive = false; }
		void setCombatDeactivate() { m_bCombatDeactive = true; m_bCombatActive = false; }

		void setRelic(int relicindex, bool relic) { m_Relic[relicindex] = relic; }
		bool getRelic(int relicindex) const { return m_Relic[relicindex]; }
	

		// set relic storage id, get relic storage id
		void setRelicLocation(int relicindex, int ownerobjectid, int storage, int storageid, int x, int y);

		int getRelicOwnerObjectID(int relicindex) const { return m_RelicOwnerObjectID[relicindex]; }
		int getRelicStorageID(int relicindex) const { return m_RelicStorageID[relicindex]; }
		int getRelicStorage(int relicindex) const { return m_RelicStorage[relicindex]; }
		void setRelicStorage(int relicindex, int storage) { m_RelicStorage[relicindex] = storage; }
		void setRelicStorageID(int relicindex, ObjectID_t object) { m_RelicStorageID[relicindex] = object; }

		ZoneCoord_t getRelicX(int relicindex) const { return m_RelicX[relicindex]; }
		ZoneCoord_t getRelicY(int relicindex) const { return m_RelicY[relicindex]; }


		// set relic object id, get relic object id
		void setRelicObjectID(int relicindex, ObjectID_t object) { m_RelicObjectID[relicindex] = object; }
		ObjectID_t getRelicObjectID(int relicindex) const { return m_RelicObjectID[relicindex]; }

		int getMonsterRegenFlag(int index) const { return m_RegenFlag[index]; }
		void setMonsterRegenFlag(int index, int value, int type); 

		int getMonsterRegenType(int index) const { return m_RegenTypeFlag[index]; }

		void RelicToString(int index);
	private:
		bool m_bCombat; // 전투가 진행 중 인지 여부를 표현하는 변수
		bool m_bCombatActive;
		bool m_bCombatDeactive;

		int m_RelicStatus[5];
		string m_RelicOwner[5];
		int m_RegenFlag[5];
		int m_RegenTypeFlag[5];

		int m_SlayerHPPoint;
		int m_SlayerToHitPoint;
		int m_VampireToHitPoint;
		int m_VampireHPPoint;

		// 각 렐릭이 출현했는가 하는 부분 
		bool m_Relic[5];

		// 각 렐릭의 위치 정보
		int m_RelicOwnerObjectID[5];
		int m_RelicStorageID[5];
		int m_RelicStorage[5];
	    ZoneCoord_t m_RelicX[5], m_RelicY[5];

		// 각 렐릭의 Object ID
		ObjectID_t m_RelicObjectID[5];

		mutable Mutex m_Mutex;
};

extern CombatSystemManager* g_pCombatSystemManager;

#endif
