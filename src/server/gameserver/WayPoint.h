//////////////////////////////////////////////////////////////////////////////
// Filename    : WayPoint.h
// Written by  : excel96
// Description : 
// 슬레이어용 개인 포탈을 위한 웨이포인트의 집합을 관리하는 클래스 모듈
//////////////////////////////////////////////////////////////////////////////

#ifndef __WAYPOINT_H__
#define __WAYPOINT_H__

#include "Types.h"
#include "Exception.h"
#include <map>

//////////////////////////////////////////////////////////////////////////////
// class WayPoint
//////////////////////////////////////////////////////////////////////////////

class WayPoint
{
public:
	WayPoint();
	~WayPoint();

public:
	ZoneID_t getZoneID(void) const { return m_ZoneCoord.id; }
	void setZoneID(ZoneID_t id) { m_ZoneCoord.id = id; }

	ZoneCoord_t getX(void) const { return m_ZoneCoord.x; }
	void setX(ZoneCoord_t x) { m_ZoneCoord.x = x; }

	ZoneCoord_t getY(void) const { return m_ZoneCoord.y; }
	void setY(ZoneCoord_t y) { m_ZoneCoord.y = y; }

	Race_t getRace(void) const { return m_Race; }
	void setRace(Race_t race) { m_Race = race; }

	ZONE_COORD getZoneCoord(void) const { return m_ZoneCoord; }
	void setZoneCoord(const ZONE_COORD& c) { m_ZoneCoord.id = c.id; m_ZoneCoord.x = c.x; m_ZoneCoord.y = c.y; }
	void setZoneCoord(ZoneID_t id, ZoneCoord_t x, ZoneCoord_t y) { m_ZoneCoord.id = id; m_ZoneCoord.x = x; m_ZoneCoord.y = y; }

	ulonglong getKey(void) const;
	static ulonglong getKey(ZoneID_t id, ZoneCoord_t x, ZoneCoord_t y);

private:
	ZONE_COORD m_ZoneCoord;
	Race_t	   m_Race;
};


//////////////////////////////////////////////////////////////////////////////
// class WaypointManager
//////////////////////////////////////////////////////////////////////////////

class WayPointManager : public std::map<ulonglong, WayPoint*>
{
public:
	typedef std::map<ulonglong, WayPoint*> WayPointMap;
	typedef WayPointMap::iterator          iterator;
	typedef WayPointMap::const_iterator    const_iterator;

public:
	WayPointManager();
	~WayPointManager();

public:
	void load(void) ;
	bool isValidWayPoint(ZoneID_t id, ZoneCoord_t x, ZoneCoord_t y, Race_t race) ;

private:
	void addWayPoint(WayPoint* pWayPoint) ;
};

// global varible
extern WayPointManager* g_pWayPointManager;



#endif
