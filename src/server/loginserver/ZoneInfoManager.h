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
#include <hash_map>

typedef hash_map< ZoneID_t , ZoneInfo * > HashMapZoneInfo;

//----------------------------------------------------------------------
//
// class ZoneInfoManager;
//
// 존 아이디를 키값으로 하는 존 정보의 hash_map 을 가지고 있다.
//
//----------------------------------------------------------------------

class ZoneInfoManager {
	
public :
	
	// constructor
	ZoneInfoManager () throw ();
	
	// destructor
	~ZoneInfoManager () throw ();

	// initialize manager
	void init () throw ( Error );

	// load from database
	void load () throw ( Error );
	
	// add info
	void addZoneInfo ( ZoneInfo * pZoneInfo ) throw ( DuplicatedException );
	
	// delete info
	void deleteZoneInfo ( ZoneID_t zoneID ) throw ( NoSuchElementException );
	
	// get info
	ZoneInfo * getZoneInfo ( ZoneID_t zoneID ) const throw ( NoSuchElementException );

	// get count of info
	uint getSize () const throw () { return m_ZoneInfos.size(); }

	// get debug string
	string toString () const throw ();

private :
	
	// hash map of ZoneInfo
	// key   : ZoneID_t
	// value : ZoneInfo *
	HashMapZoneInfo m_ZoneInfos;

};


// global variable declaration
extern ZoneInfoManager * g_pZoneInfoManager;

#endif
