//////////////////////////////////////////////////////////////////////////////
// Filename    : WayPoint.cpp
// Written by  : excel96
// Description : 
// 슬레이어용 개인 포탈을 위한 웨이포인트의 집합을 관리하는 클래스 모듈
//////////////////////////////////////////////////////////////////////////////

#include "WayPoint.h"
#include "Zone.h"
#include "ZoneUtil.h"
#include "Tile.h"
#include "Assert.h"
#include "DB.h"

//////////////////////////////////////////////////////////////////////////////
// class WayPoint member methods
//////////////////////////////////////////////////////////////////////////////

// constructor
WayPoint::WayPoint()
{
	m_ZoneCoord.id = 0;
	m_ZoneCoord.x  = 0;
	m_ZoneCoord.y  = 0;
	m_Race		   = 0;
}

// destructor
WayPoint::~WayPoint()
{
}

// key generator
ulonglong WayPoint::getKey(void) const 
{
	return getKey(m_ZoneCoord.id, m_ZoneCoord.x, m_ZoneCoord.y);
}

// static key generator
ulonglong WayPoint::getKey(ZoneID_t id, ZoneCoord_t x, ZoneCoord_t y)
{
	ulonglong ID = id;
	ulonglong X  = x;
	ulonglong Y  = y;
	
	ulonglong key = (ID << 32) | (X << 16) | Y;
	return key;
}


//////////////////////////////////////////////////////////////////////////////
// class WaypointManager member methods
//////////////////////////////////////////////////////////////////////////////

// constructor
WayPointManager::WayPointManager()
{
}

// destructor
WayPointManager::~WayPointManager()
{
	WayPointMap::iterator itr = begin();
	for (; itr != end(); itr++)
	{
		WayPoint* pWayPoint = itr->second;
		SAFE_DELETE(pWayPoint);
	}

	clear();
}

// load waypoint data from database
void WayPointManager::load(void) 
	throw()
{
	__BEGIN_TRY

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT ZoneID, X, Y, Race FROM WayPointInfo");

		while (pResult->next())
		{
			ZoneID_t    ZID = pResult->getInt(1);
			ZoneCoord_t ZX  = pResult->getInt(2);
			ZoneCoord_t ZY  = pResult->getInt(3);
			Race_t     Race = pResult->getInt(4);

			WayPoint* pWayPoint = new WayPoint;
			Assert(pWayPoint != NULL);
			pWayPoint->setZoneCoord(ZID, ZX, ZY);
			pWayPoint->setRace( Race );

			addWayPoint(pWayPoint);

			// 아우스터즈 웨이포인트는 블럭해줘야 된다.
			if ( Race == RACE_OUSTERS )
			{
				Zone* pZone = getZoneByZoneID(ZID);
				Tile& rTile = pZone->getTile( ZX, ZY );

				rTile.setBlocked( Creature::MOVE_MODE_WALKING );
				rTile.setBlocked( Creature::MOVE_MODE_BURROWING );
			}
		}

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt);

	__END_CATCH
}

// if there's right waypoint, return true, else return false
bool WayPointManager::isValidWayPoint(ZoneID_t id, ZoneCoord_t x, ZoneCoord_t y, Race_t race)
	throw()
{
	__BEGIN_TRY

	ulonglong key = WayPoint::getKey(id, x, y);
	WayPointMap::const_iterator itr = find(key);

	if (itr != end() && itr->second->getRace() == race) return true;

	return false;

	__END_CATCH
}

// add waypoint data into waypoint map
void WayPointManager::addWayPoint(WayPoint* pWayPoint) 
	throw()
{
	__BEGIN_TRY

	Assert(pWayPoint != NULL);

	ulonglong key = pWayPoint->getKey();

	WayPointMap::const_iterator itr = find(key);

	if (itr != end())
	{
		cerr << "WayPointManager::addWayPoint() : Duplicated WayPoint" << endl;
		cerr << "아마 헬기랑 대지정령뿔이랑 좌표가 겹쳤을지도...ㅋㅋㅋ.즐~" << endl;
		throw ("WayPointManager::addWayPoint() : Duplicated WayPoint");
	}

	insert(WayPointMap::value_type(key, pWayPoint));

	__END_CATCH
}

WayPointManager* g_pWayPointManager = NULL;
