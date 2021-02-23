//////////////////////////////////////////////////////////////////////////////
// Filename    : HolyLandManager.h
// Written By  : Bezz
// Description : Holy Land ( Zone * ) 를 가지고 있다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __HOLY_LAND_MANAGER_H__
#define __HOLY_LAND_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Mutex.h"
#include <hash_map>

//////////////////////////////////////////////////////////////////////////////
// class HolyLandManager;
//////////////////////////////////////////////////////////////////////////////

class Zone;
class Packet;

typedef hash_map<ZoneID_t, Zone*> HashMapZone;
typedef hash_map<ZoneID_t, Zone*>::iterator HashMapZoneItor;
typedef hash_map<ZoneID_t, Zone*>::const_iterator HashMapZoneConstItor;

class HolyLandManager 
{
public:
	HolyLandManager() throw();
	~HolyLandManager() throw();

	void clear() { lock(); m_HolyLands.clear(); unlock(); }

public:
	void addHolyLand( Zone* pZone ) throw ( DuplicatedException, Error );

	const HashMapZone& getHolyLands() const { return m_HolyLands; }

	void lock() throw(Error) { m_Mutex.lock(); }
	void unlock() throw(Error) { m_Mutex.unlock(); }

	void broadcast( Packet* pPacket ) const throw(Error);

//	void sendBloodBibleStatus() const throw (Error);

	void fixTimeband( uint timeband ) throw(Error);
	void resumeTimeband() throw(Error);

	void    killAllMonsters() throw (Error);

	void	remainRaceWarPlayers() throw (Error);

	void refreshHolyLandPlayers() throw (Error);

private:
	HashMapZone m_HolyLands;

	mutable Mutex m_Mutex;
};

// global variable declaration
extern HolyLandManager* g_pHolyLandManager;

#endif
