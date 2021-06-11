//////////////////////////////////////////////////////////////////////////////
// Filename    : MasterLairManager.h 
// Written by  : 쉭
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __MASTER_LAIR_MANAGER_H__
#define __MASTER_LAIR_MANAGER_H__

#include "MonsterCounter.h"
#include "Item.h"
#include "Timeval.h"
#include "Mutex.h"
#include <unordered_map>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// class MasterLairManager
//////////////////////////////////////////////////////////////////////////////

class Zone;

class MasterLairManager
{
public : 
	enum MasterLairEvent 
	{ 
		EVENT_WAITING_PLAYER,     // 사람들이 들어오길 기다린다. 
		EVENT_MINION_COMBAT,      // 소환된 몬스터와 싸운다. 
		EVENT_MASTER_COMBAT,      // 마스터와 싸운다. 
		EVENT_WAITING_KICK_OUT,    // 사용자 강제추방 대기(마스터 잡은 경우의 정리 시간) 
		EVENT_WAITING_REGEN,      // 다시 리젠되길 기다린다. 

		EVENT_MAX
	}; 


public:
	MasterLairManager(Zone* pZone) ;
	~MasterLairManager() ;

	MasterLairEvent getCurrentEvent() const { return m_Event; }

	bool enterCreature(Creature* pCreature) ;  // 존에 출입이 가능한가? 
	bool leaveCreature(Creature* pCreature) ;  // 존에서 나간 경우

	bool heartbeat() ;

	//void increaseSummonedMonsterNumber(int num) ;
	bool isMasterReady() const { return m_bMasterReady; }
	void setMasterReady(bool bReady=true) { m_bMasterReady = bReady; }

	void startEvent() ;
	void stopEvent() ;

	void lock()  { m_Mutex.lock(); }
    void ulnock()  { m_Mutex.unlock(); }

	string toString() const ;

protected :
	void processEventWaitingPlayer() ;
	void processEventMinionCombat() ;
	void processEventMasterCombat() ;
	void processEventWaitingKickOut() ;
	void processEventWaitingRegen() ;

	void activeEventWaitingPlayer() ;
	void activeEventMinionCombat() ;
	void activeEventMasterCombat() ;
	void activeEventWaitingKickOut() ;
	void activeEventWaitingRegen() ;

	void deleteAllMonsters() ;		// 모든 몬스터 삭제
	void kickOutPlayers() ;		// 사용자 강제 추방
	void giveKillingReward() ;		// 마스터 죽였을 때 받는 보상
	void killAllMonsters() ;		// 모든 몬스터를 죽인다

private : 
	Zone*             m_pZone;  
	ObjectID_t        m_MasterID;           // 마스터 한 마리 
	ZoneCoord_t       m_MasterX;
	ZoneCoord_t       m_MasterY;

	bool              m_bMasterReady;      // 마스터가 싸울 준비가 되었나? 

	//int               m_nMaxSummonMonster; // 마스터가 소환할 최대의 몬스터 수 
	//int               m_nSummonedMonster;  // 마스터가 소환한 몬스터 수 

	int               m_nMaxPassPlayer;	   // 최대 출입 사용자 수
	int               m_nPassPlayer;       // Pass를 받은 사람 수 

	MasterLairEvent   m_Event;             // 현재의 이벤트 종류 
	Timeval           m_EventTime;         // 현재의 이벤트가 지속될 시간
	int               m_EventValue;		   // 이벤트와 관련된 값

	Timeval           m_RegenTime;         // 싹 정리하고 다시 시작하는 시간 


	mutable Mutex     m_Mutex;				// m_nPassPlayer를 확실히 체크할려고..
};

#endif
