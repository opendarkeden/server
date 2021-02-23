/////////////////////////////////////////////////////////////////////////////
// DynamicZoneManager.h
// 서버에서 생겼다 사라졌다하는 존을 관리하는 넘
/////////////////////////////////////////////////////////////////////////////

#ifndef __DYNAMIC_ZONE_MANAGER_H__
#define __DYNAMIC_ZONE_MANAGER_H__

#include "Types.h"
#include "Mutex.h"
#include <hash_map>

class DynamicZoneGroup;

///////////////////////////////////////////////////////////
// class DynamicZoneManager
///////////////////////////////////////////////////////////
class DynamicZoneManager
{
public:
	typedef hash_map<int,DynamicZoneGroup*>			HashMapDynamicZoneGroup;
	typedef HashMapDynamicZoneGroup::iterator		HashMapDynamicZoneGroupItor;
	typedef HashMapDynamicZoneGroup::const_iterator	HashMapDynamicZoneGroupConstItor;

public:
	DynamicZoneManager();
	~DynamicZoneManager();

public:
	void init();
	void clear();

	// 새로 DynamicZoneGroup 을 추가한다.
	void addDynamicZoneGroup( DynamicZoneGroup* pDynamicZoneGroup );

	// DynamicZoneGroup 을 찾아서 반환한다.
	DynamicZoneGroup* getDynamicZoneGroup( int dynamicZoneType );

	// get new dynamic zone id
	ZoneID_t getNewDynamicZoneID();

	static bool isDynamicZone( ZoneID_t zoneID );

private:
	Mutex m_Mutex;
	ZoneID_t m_DynamicZoneID;

	HashMapDynamicZoneGroup m_DynamicZoneGroups;
};

// global variable
extern DynamicZoneManager* g_pDynamicZoneManager;

#endif

