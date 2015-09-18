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
#include <map>

class ResurrectLocationManager {
public:
    ResurrectLocationManager() throw();
    ~ResurrectLocationManager() throw();

    void init() throw();
    void load() throw();

    bool getSlayerPosition(ZoneID_t id, ZONE_COORD& zoneCoord) const throw();//NoSuchElementException);
    bool getVampirePosition(ZoneID_t id, ZONE_COORD& zoneCoord) const throw();//NoSuchElementException);

    void addSlayerPosition(ZoneID_t id, const ZONE_COORD& coord) throw(DuplicatedException, Error);
    void addVampirePosition(ZoneID_t id, const ZONE_COORD& coord) throw(DuplicatedException, Error);


protected:
    map<ZoneID_t, ZONE_COORD> m_SlayerPosition;
    map<ZoneID_t, ZONE_COORD> m_VampirePosition;
};

extern ResurrectLocationManager* g_pResurrectLocationManager;
#endif
