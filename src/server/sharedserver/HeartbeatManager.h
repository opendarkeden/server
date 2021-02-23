//////////////////////////////////////////////////////////////////////
//
// Filename    : HeartbeatManager.h
// Written by  : reiot@ewestsoft.com
// Description : 로그인 서버용 클라이언트 매니저
//
//////////////////////////////////////////////////////////////////////

#ifndef __HEARTBEAT_MANAGER_H__
#define __HEARTBEAT_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////
//
// class HeartbeatManager;
//
// 로그인 서버에 접속한 모든 플레이어들의 입출력을 처리하며,
// 새로운 클라이언트의 연결 시도를 처리한다.
//
// 클라이언트의 run()은 로그인 서버 프로세스의 메인 쓰레드에서 돌아간다.
// 따라서, Thread를 상속받을 필요가 없다. 그러나, 클래스의 구조나 역할은
// Thread 를 상속받은 다른 클래스와 유사하다.
//
//////////////////////////////////////////////////////////////////////

class HeartbeatManager {

public :

	// constructor
	HeartbeatManager () throw ( Error );

	// destructor
	~HeartbeatManager () throw ( Error );

	// 클라이언트 매니저를 초기화한다.
	void init () throw ( Error );

	// 클라이언트 매니저를 시작한다.
	void start () throw ( Error );

	// 클라이언트 매니저를 중단한다.
	void stop () throw ( Error );

	// 클라이언트 매니저의 메인 메쏘드
	void run () throw ( Error );

};

// external variable declaration
extern HeartbeatManager * g_pHeartbeatManager;

#endif
