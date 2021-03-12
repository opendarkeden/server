//////////////////////////////////////////////////////////////////////////////
// Filename    : PCManager.h 
// Written By  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __PC_MANANGER_H__
#define __PC_MANANGER_H__

#include "CreatureManager.h"
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// class PCManager
//////////////////////////////////////////////////////////////////////////////
const BYTE defaultRaceValue = 0xFF;

class PCManager : public CreatureManager 
{
public:
	PCManager() ;
	virtual ~PCManager() ;
	
public:

	// 크리처 매니저에 새 크리처 객체를 등록한다.
	//virtual void addCreature(Creature* pCreature) ;
	
	// 크리처 매니저에 들어있는 특정 크리처 객체를 삭제한다.
	//virtual void deleteCreature(ObjectID_t objectID) ;
	
	// 크리처 매니저에 들어있는 특정 크리처 객체를 리턴한다.
	//Creature* getCreature(ObjectID_t objectID) const ;

	// 매니저에 소속된 크리처들(NPC,Monster)을 처리한다.
	virtual void processCreatures() ;

	// 죽은 크리처를 처리한다.
	virtual void killCreature(Creature* pDeadCreature) ;

	// PC 매니저일 경우, 브로드캐스트한다.
	//void broadcastPacket(Packet* pPacket, Creature* owner) ;

	// 모든 사용자들 다른 곳으로 이동시킨다.
	void transportAllCreatures(ZoneID_t ZoneID, ZoneCoord_t ZoneX = 0xffff, ZoneCoord_t ZoneY = 0xffff, Race_t race=defaultRaceValue, Turn_t delay=10) const ;
	
	// get debug string 
	string toString() const ;

	// Holy Land Race Bonus 변화에 따른 플레이어 refresh
	void setRefreshHolyLandPlayer( bool bRefresh ) { m_bRefreshHolyLandPlayer = bRefresh; }
//	void setRefreshLevelWarBonusZonePlayer( bool bRefresh ) { m_bRefreshLevelWarBonusZonePlayer = bRefresh; }

	vector<uint>	getPCNumByRace() const;
private:
	bool m_bRefreshHolyLandPlayer;
//	bool m_bRefreshLevelWarBonusZonePlayer;

};

#endif
