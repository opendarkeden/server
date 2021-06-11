//////////////////////////////////////////////////////////////////////
// 
// Filename    : CBillingServer.h 
// Written By  : reiot@ewestsoft.com
// Description : 로그인 서버용 메인 클래스
// 
//////////////////////////////////////////////////////////////////////

#ifndef __CBILLING_SERVER_H__
#define __CBILLING_SERVER_H__

// include files
#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////
//
// class CBillingServer
//
// 로그인 서버 자체를 나타내는 클래스이다.
//
//////////////////////////////////////////////////////////////////////

class CBillingServer {

public :
	
	// constructor
	CBillingServer () throw ( Error );
	
	// destructor
	~CBillingServer () throw ( Error );

	// intialize game server
	void init () throw ( Error );

	// start game server
	void start () throw ( Error );
	
	// stop game server
	void stop () throw ( Error );

};

// global variable declaration
extern CBillingServer * g_pCBillingServer;

#endif
