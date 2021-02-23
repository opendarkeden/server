//////////////////////////////////////////////////////////////////////
//
// Filename    : ZoneGroup.h
// Written By  : reiot@ewestsoft.com
// Description :
//
//////////////////////////////////////////////////////////////////////

#ifndef __ZONE_GROUP_H__
#define __ZONE_GROUP_H__

// include files
#include "Types.h"
#include "Exception.h"
#include <hash_map>
#include "Zone.h"
#include "GameTime.h"
#include "Gpackets/GMServerInfo.h"

// forward declaration
class ZoneThread;
class ZonePlayerManager;

// type redefinition
//typedef hash_map<ZoneID_t,Zone*> ZONE_HASHMAP;

//////////////////////////////////////////////////////////////////////
//
// class ZoneGroup;
//
//////////////////////////////////////////////////////////////////////
class ZoneGroup {
	
	// friend declaration
	friend class ZoneThread;

public:
	
	// constructor
	ZoneGroup(ZoneGroupID_t zoneGroupID) throw();
	
	// destructor
	~ZoneGroup() throw();
	

public:
	
	// initialize zone group
	void init() throw(Error);
	
	// load sub zones from database
	void load() throw(Error);
	
	// save sub zones to database
	void save() throw(Error);

	//
	void processPlayers() throw(Error);
	void heartbeat() throw(Error);	
	
public:

	// add zone to zone group
	void addZone(Zone* pZone) throw(Error);
	
	// delete zone from zone group
	void deleteZone(ZoneID_t zoneID) throw(NoSuchElementException);
	Zone* removeZone(ZoneID_t zoneID) throw(NoSuchElementException);
	
	// get zone from zone group
	Zone* getZone(ZoneID_t zoneID) const throw(NoSuchElementException);

//#ifdef __NO_COMBAT__
	Zone* getCombatZone(ZoneID_t zoneID) const throw(Error); // getZone과 같은 일을 수행하나 NULL을 리턴하는 것이 가능, 김경석
//#endif

//--------------------------------------------------
// get/set methods
//--------------------------------------------------
public:

	// get/set zone group id
	ZoneGroupID_t getZoneGroupID() const throw() { return m_ZoneGroupID; }
	void setZoneGroupID(ZoneGroupID_t zoneGroupID) throw() { m_ZoneGroupID = zoneGroupID; }

	// get zone player manager
	ZonePlayerManager* getZonePlayerManager() throw() { return m_pZonePlayerManager; }
	void setZonePlayerManager(ZonePlayerManager* pZonePlayerManager) throw() { m_pZonePlayerManager = pZonePlayerManager; }

	// get/set game time
	GameTime getGameTime() const throw() { return m_GameTime; }
	void setGameTime(const GameTime & gameTime) throw() { m_GameTime = gameTime; }

	void makeZoneUserInfo ( GMServerInfo & gmServerInfo ) throw(Error);

	const hash_map< ZoneID_t, Zone* >& getZones() const { return m_Zones; }

	// get debug string
	string toString() const throw();

public :
	void 	lock() throw (Error)		{ m_Mutex.lock(); }
	void 	unlock() throw (Error)		{ m_Mutex.unlock(); }

	  void   initLoadValue();
      DWORD  getLoadValue() const;


//--------------------------------------------------
// data members
//--------------------------------------------------
private:

	// zone group id
	ZoneGroupID_t m_ZoneGroupID;
	
	// zone 의 해쉬맵
	hash_map< ZoneID_t, Zone* > m_Zones;

	// zone player manager
	ZonePlayerManager* m_pZonePlayerManager;

	// game time
	GameTime m_GameTime;

	// Tick Time
	Timeval m_TickTime;

	DWORD	m_LoadValue;

	mutable Mutex  m_Mutex;
};

#endif
