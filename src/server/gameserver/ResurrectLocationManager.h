//////////////////////////////////////////////////////////////////////////////
// Filename    : ResurrectLocationManager.h
// Written by  : excel96
// Description : 
// 플레이어가 죽었을 때 다시 태어나는 부활 위치를 존 별로 저장하고
// 있는 맵이다. 
//////////////////////////////////////////////////////////////////////////////

#ifndef __RESURRECTMANAGER_H__
#define __RESURRECTMANAGER_H__

#include "Types.h"
#include "Exception.h"
#include <unordered_map>

//////////////////////////////////////////////////////////////////////////////
// class ResurrectLocationManager
//
// 플레이어가 죽었을 때 다시 태어나는 부활 위치를 존 별로 저장하고
// 있는 맵이다. 
//
// 슬레이어 및 뱀파이어 각각 기본 부활 위치를 지정할 수 있는 
// 함수가 있어야 한다. 현재는 Resurrect.cpp에 소스 레벨로 들어가 있다.
//////////////////////////////////////////////////////////////////////////////

class PlayerCreature;

class ResurrectLocationManager
{
public:
	ResurrectLocationManager() ;
	~ResurrectLocationManager() ;

public:
	void init() ;
	void load() ;

public:
	bool getSlayerPosition(ZoneID_t id, ZONE_COORD& zoneCoord) const ;//NoSuchElementException);
	bool getVampirePosition(ZoneID_t id, ZONE_COORD& zoneCoord) const ;//NoSuchElementException);
	bool getOustersPosition(ZoneID_t id, ZONE_COORD& zoneCoord) const ;//NoSuchElementException);
	bool getRaceDefaultPosition(Race_t, ZONE_COORD& zoneCoord) const ;

	bool getPosition(PlayerCreature* pPC, ZONE_COORD& zondCoord) const ;
	bool getBasicPosition(PlayerCreature* pPC, ZONE_COORD& zondCoord) const ;

	void addSlayerPosition(ZoneID_t id, const ZONE_COORD& coord) ;
	void addVampirePosition(ZoneID_t id, const ZONE_COORD& coord) ;
	void addOustersPosition(ZoneID_t id, const ZONE_COORD& coord) ;


protected:
	unordered_map<ZoneID_t, ZONE_COORD> m_SlayerPosition;
	unordered_map<ZoneID_t, ZONE_COORD> m_VampirePosition;
	unordered_map<ZoneID_t, ZONE_COORD> m_OustersPosition;
};


//////////////////////////////////////////////////////////////////////////////
// global variable
//////////////////////////////////////////////////////////////////////////////
extern ResurrectLocationManager* g_pResurrectLocationManager;

#endif
