//////////////////////////////////////////////////////////////////////////////
// Filename    : ConnectionInfo.h
// Written by  : reiot@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __CONNECTION_INFO_H__
#define __CONNECTION_INFO_H__

#include "Types.h"
#include "Exception.h"
#include "Timeval.h"

//////////////////////////////////////////////////////////////////////////////
// class ConnectionInfo;
// 서버간 이동에서 정당한 연결에 대한 정보를 나타내는 객체
//////////////////////////////////////////////////////////////////////////////

class ConnectionInfo 
{
public:
	ConnectionInfo() throw();
	~ConnectionInfo() throw();

public:
	string getClientIP() const throw() { return m_ClientIP; }
	void setClientIP(const string & clientIP) throw() { m_ClientIP = clientIP; }

	string getPlayerID() const throw() { return m_PlayerID; }
	void setPlayerID(const string & PlayerID) throw() { m_PlayerID = PlayerID; }
	
	string getPCName() const throw() { return m_PCName; }
	void setPCName(const string & name) throw() { m_PCName = name; }

	Timeval getExpireTime() const throw() { return m_ExpireTime; }
	void setExpireTime(Timeval tv) throw() { m_ExpireTime = tv; }
	
	DWORD getKey() const throw() { return m_Key; }
	void setKey(DWORD key) throw() { m_Key = key; }

	string toString() const throw();

private:
	string  m_ClientIP;   // valid client's ip
	string  m_PlayerID;   // PlayerID
	string  m_PCName;     // PC name
	Timeval m_ExpireTime; // expire time : 언제까지 이 정보를 유지하고 있어야 하는지..
	DWORD   m_Key;        // validation key
};

//////////////////////////////////////////////////////////////////////////////
// CompareConnectionInfo
//
// priority_queue 에서 ConnectionInfo 끼리 비교할 때 사용하는 클래스�
//
// *CAUTION*
//
// 시간적으로 이른(시간값이 작은) 쪽이 PQ 의 top 에 위치해야 한다.
// 즉 PQ 는 ascending order 를 이뤄야 한다. 왜 그런지는 잘 살펴보기를..
// 시간이 없는 관계로.. - -;
//////////////////////////////////////////////////////////////////////////////

class CompareConnectionInfo 
{
public:
	// compare which is more recent
    bool operator()(const ConnectionInfo & left, const ConnectionInfo & right)
    {
		// Ascending Order
        return left.getExpireTime() > right.getExpireTime();

		// Descending Order
        //return left.getExpireTime() < right.getExpireTime();
    }
};

#endif
