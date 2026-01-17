//----------------------------------------------------------------------
//
// Filename    : ZoneGroupInfoManager.h
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

#ifndef __ZONE_GROUP_INFO_MANAGER_H__
#define __ZONE_GROUP_INFO_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ZoneGroupInfo.h"
#include <unordered_map>

typedef unordered_map< ZoneGroupID_t , ZoneGroupInfo * > HashMapZoneGroupInfo;

//----------------------------------------------------------------------
//
// class ZoneGroupInfoManager;
//
// ���׷� ���̵� Ű������ �ϴ� �� ������ unordered_map �� ������ �ִ�.
//
//----------------------------------------------------------------------

class ZoneGroupInfoManager {
	
public :
	
	// constructor
	ZoneGroupInfoManager () noexcept;
	
	// destructor
	~ZoneGroupInfoManager () noexcept;

	// initialize manager
	void init () noexcept(false);

	// load from database
	void load () noexcept(false);
	
	// add info
	void addZoneGroupInfo ( ZoneGroupInfo * pZoneGroupInfo ) noexcept(false);
	
	// delete info
	void deleteZoneGroupInfo ( ZoneGroupID_t zoneGroupID ) noexcept(false);
	
	// get info
	ZoneGroupInfo * getZoneGroupInfo ( ZoneGroupID_t zoneGroupID ) const noexcept(false);

	// get count of info
	uint getSize () const noexcept { return m_ZoneGroupInfos.size(); }

	// get debug string
	string toString () const;

private :
	
	// hash map of ZoneGroupInfo
	// key   : ZoneGroupID_t
	// value : ZoneGroupInfo *
	HashMapZoneGroupInfo m_ZoneGroupInfos;

};


// global variable declaration
extern ZoneGroupInfoManager * g_pZoneGroupInfoManager;

#endif
