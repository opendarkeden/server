//////////////////////////////////////////////////////////////////////
// 
// Filename    : TheOneServer.h 
// Written By  : reiot@ewestsoft.com
// Description : 로그인 서버용 메인 클래스
// 
//////////////////////////////////////////////////////////////////////

#ifndef __THE_ONE_SERVER_H__
#define __THE_ONE_SERVER_H__

// 이 모듈이 포함되면, 로그인 서버 모듈이 된다.
#ifndef __THE_ONE_SERVER__
#define __THE_ONE_SERVER__
#endif

// include files
#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////
//
// class TheOneServer
//
// 로그인 서버 자체를 나타내는 클래스이다.
//
//////////////////////////////////////////////////////////////////////

class TheOneServer {

public :
	
	// constructor
	TheOneServer () throw ( Error );
	
	// destructor
	~TheOneServer () throw ( Error );

	// intialize game server
	void init () throw ( Error );

	// start game server
	void start () throw ( Error );
	
	// stop game server
	void stop () throw ( Error );

};

// global variable declaration
extern TheOneServer * g_pTheOneServer;

#endif
