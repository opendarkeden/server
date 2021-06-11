//----------------------------------------------------------------------
//
// Filename    : ZoneInfo.h
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

#ifndef __ZONE_INFO_H__
#define __ZONE_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"

//----------------------------------------------------------------------
//
// class ZoneInfo;
//
// 로그인 서버용 존 정보 객체이다.
//
// 어떤 존이 어떤 존 그룹에 속하는지만 다룬다.
//
//----------------------------------------------------------------------

class ZoneInfo {

public :

	// get/set zone id
	ZoneID_t getZoneID () const throw () { return m_ZoneID; }
	void setZoneID ( ZoneID_t zoneID ) throw () { m_ZoneID = zoneID; }

	// get/set zone group id
	ZoneGroupID_t getZoneGroupID () const throw () { return m_ZoneGroupID; }
	void setZoneGroupID ( ZoneGroupID_t zoneGroupID ) throw () { m_ZoneGroupID = zoneGroupID; }

	// get debug string
	string toString () const throw ()
	{
		StringStream msg;
		msg << "ZoneInfo(ZoneID:" << m_ZoneID << ",ZoneGroupID:" << m_ZoneGroupID << ")";
		return msg.toString();
	}

private :

	// 존 아이디
	ZoneID_t m_ZoneID;

	// 존 그룹 아이디
	ZoneGroupID_t m_ZoneGroupID;

};

#endif
