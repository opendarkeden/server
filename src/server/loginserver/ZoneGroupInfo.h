//----------------------------------------------------------------------
//
// Filename    : ZoneGroupInfo.h
// Written By  : Reiot
// Description :
//
//----------------------------------------------------------------------

#ifndef __ZONE_GROUP_INFO_H__
#define __ZONE_GROUP_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"

//----------------------------------------------------------------------
//
// class ZoneGroupInfo;
//
// 로그인 서버용 존 그룹 정보 객체이다.
//
// 어떤 존그룹이 어떤 서버에 의해서 처리되는지만 다룬다.
//
//----------------------------------------------------------------------

class ZoneGroupInfo {

public :

	// get/set zone group id
	ZoneGroupID_t getZoneGroupID () const throw () { return m_ZoneGroupID; }
	void setZoneGroupID ( ZoneGroupID_t zoneGroupID ) throw () { m_ZoneGroupID = zoneGroupID; }

	// get/set game server's nick name
	ServerID_t getServerID () const throw () { return m_ServerID; }
	void setServerID ( const ServerID_t ServerID ) throw () { m_ServerID = ServerID; }

	// get debug string
	string toString () const throw ()
	{
		StringStream msg;

		msg << "ZoneGroupInfo("
			<< "ZoneGroupID:" << m_ZoneGroupID 
			<< ",ServerID:" << m_ServerID
			<< ")";

		return msg.toString();
	}

private :

	// 존그룹 아이디
	ZoneGroupID_t m_ZoneGroupID;

	// 게임 서버
	ServerID_t m_ServerID;

};

#endif
