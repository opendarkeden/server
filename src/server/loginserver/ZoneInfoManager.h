//----------------------------------------------------------------------
//
// Filename    : ZoneInfoManager.h
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

#ifndef __ZONE_INFO_MANAGER_H__
#define __ZONE_INFO_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "ZoneInfo.h"
#include <unordered_map>

typedef unordered_map< ZoneID_t , ZoneInfo * > HashMapZoneInfo;

//----------------------------------------------------------------------
//
// class ZoneInfoManager;
//
// 존 아이디를 키값으로 하는 존 정보의 unordered_map 을 가지고 있다.
//
//----------------------------------------------------------------------

class ZoneInfoManager {
	
public :
	
	// constructor
	ZoneInfoManager () ;
	
	// destructor
	~ZoneInfoManager () ;

	// initialize manager
	void init ();

	// load from database
	void load ();
	
	// add info
	void addZoneInfo ( ZoneInfo * pZoneInfo );
	
	// delete info
	void deleteZoneInfo ( ZoneID_t zoneID );
	
	// get info
	ZoneInfo * getZoneInfo ( ZoneID_t zoneID ) ;

	// get count of info
	uint getSize () const { return m_ZoneInfos.size(); }

	// get debug string
	string toString () const ;

private :
	
	// hash map of ZoneInfo
	// key   : ZoneID_t
	// value : ZoneInfo *
	HashMapZoneInfo m_ZoneInfos;

};


// global variable declaration
extern ZoneInfoManager * g_pZoneInfoManager;

#endif
