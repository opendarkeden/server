//----------------------------------------------------------------------
//
// Filename    : ReconnectLoginInfo.h
// Written by  : reiot@ewestsoft.com
// Description : 
//
//----------------------------------------------------------------------

#ifndef __RECONNECT_LOGIN_INFO_H__
#define __RECONNECT_LOGIN_INFO_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Timeval.h"
#include "StringStream.h"

//----------------------------------------------------------------------
//
// class ReconnectLoginInfo;
//
// 서버간 이동에서 정당한 연결에 대한 정보를 나타내는 객체
//
//----------------------------------------------------------------------

class ReconnectLoginInfo {

public :

	// constructor
	ReconnectLoginInfo () throw () : m_Key(0) 
	{ 
		m_ExpireTime.tv_sec = 0; 
		m_ExpireTime.tv_usec = 0; 
	}

	// destructor
	~ReconnectLoginInfo () throw () {}

	// get/set client ip
	string getClientIP () const throw () { return m_ClientIP; }
	void setClientIP ( const string & clientIP ) throw () { m_ClientIP = clientIP; }

	// get/set PlayerID
	string getPlayerID() const throw() { return m_PlayerID; }
	void setPlayerID( const string & PlayerID ) throw() { m_PlayerID = PlayerID; }

	// get/set expire time
	Timeval getExpireTime () const throw () { return m_ExpireTime; }
	void setExpireTime ( Timeval tv ) throw () { m_ExpireTime = tv; }
	
	// get/set validation key
	DWORD getKey () const throw () { return m_Key; }
	void setKey ( DWORD key ) throw () { m_Key = key; }

	// get debug string
	string toString () const throw () 
	{
		StringStream msg;
		msg << "ReconnectLoginInfo(ClientIP:" << m_ClientIP 
			<< ",ExpireTime:" << m_ExpireTime.tv_sec << "." << m_ExpireTime.tv_usec 
			<< ",KEY: " << m_Key << ")";
		return msg.toString();
	}

private :

	// valid client's ip
	string m_ClientIP;

	// PlayerID
	string m_PlayerID;

	// expire time : 언제까지 이 정보를 유지하고 있어야 하는지..
	Timeval m_ExpireTime;

	// validation key
	DWORD m_Key;

};

//----------------------------------------------------------------------
//
// CompareReconnectLoginInfo
//
// priority_queue 에서 ReconnectLoginInfo 끼리 비교할 때 사용하는 클래스�
//
// *CAUTION*
//
// 시간적으로 이른(시간값이 작은) 쪽이 PQ 의 top 에 위치해야 한다.
// 즉 PQ 는 ascending order 를 이뤄야 한다. 왜 그런지는 잘 살펴보기를..
// 시간이 없는 관계로.. - -;
//
//----------------------------------------------------------------------
class CompareReconnectLoginInfo {

public :

	// compare which is more recent
    bool operator () ( const ReconnectLoginInfo & left , const ReconnectLoginInfo & right )
    {
		// Ascending Order
        return left.getExpireTime() > right.getExpireTime();

		// Descending Order
        //return left.getExpireTime() < right.getExpireTime();
    }
};

#endif
