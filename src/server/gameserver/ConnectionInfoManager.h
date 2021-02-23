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
#include <hash_map>
#include "ConnectionInfo.h"

typedef hash_map< string, ConnectionInfo* > HashMapConnectionInfo;

//////////////////////////////////////////////////////////////////////////////
// class ConnectionInfoManager;
// IP 스트링을 키값으로 하는 hash_map 을 내부에 가지고 있다.
//////////////////////////////////////////////////////////////////////////////

class ConnectionInfoManager 
{
public:
	ConnectionInfoManager() throw();
	~ConnectionInfoManager() throw();

public:
	void addConnectionInfo(ConnectionInfo* pConnectionInfo) throw(DuplicatedException, Error);
	void deleteConnectionInfo(const string& ip) throw(NoSuchElementException, Error);
	ConnectionInfo* getConnectionInfo(const string& ip) throw(NoSuchElementException, Error);
	void heartbeat() throw(Error);	
	string toString() const throw();

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
