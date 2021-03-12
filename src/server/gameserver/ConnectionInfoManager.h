//////////////////////////////////////////////////////////////////////////////
// Filename    : ConnectionInfoManager.h
// Written By  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __CONNECTION_INFO_MANAGER_H__
#define __CONNECTION_INFO_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Mutex.h"
#include <unordered_map>
#include "ConnectionInfo.h"

typedef unordered_map< string, ConnectionInfo* > HashMapConnectionInfo;

//////////////////////////////////////////////////////////////////////////////
// class ConnectionInfoManager;
// IP 스트링을 키값으로 하는 unordered_map 을 내부에 가지고 있다.
//////////////////////////////////////////////////////////////////////////////

class ConnectionInfoManager 
{
public:
	ConnectionInfoManager() ;
	~ConnectionInfoManager() ;

public:
	void addConnectionInfo(ConnectionInfo* pConnectionInfo) ;
	void deleteConnectionInfo(const string& ip) ;
	ConnectionInfo* getConnectionInfo(const string& ip) ;
	void heartbeat() ;	
	string toString() const ;

private:
	// hash map of ConnectionInfo
	// key is ip-string
	HashMapConnectionInfo m_ConnectionInfos;

	Timeval m_NextHeartbeat;
	Timeval m_UpdateUserStatusTime;	// 넷마블용 by sigi. 2002.11.4

	mutable Mutex m_Mutex;
};

// global variable declaration
extern ConnectionInfoManager* g_pConnectionInfoManager;

#endif
