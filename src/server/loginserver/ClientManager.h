//////////////////////////////////////////////////////////////////////
//
// Filename    : ClientManager.h
// Written by  : reiot@ewestsoft.com
// Description : 로그인 서버용 클라이언트 매니저
//
//////////////////////////////////////////////////////////////////////

#ifndef __LOGIN_CLIENT_MANAGER_H__
#define __LOGIN_CLIENT_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"

//////////////////////////////////////////////////////////////////////
//
// class ClientManager;
//
// 로그인 서버에 접속한 모든 플레이어들의 입출력을 처리하며,
// 새로운 클라이언트의 연결 시도를 처리한다.
//
// 클라이언트의 run()은 로그인 서버 프로세스의 메인 쓰레드에서 돌아간다.
// 따라서, Thread를 상속받을 필요가 없다. 그러나, 클래스의 구조나 역할은
// Thread 를 상속받은 다른 클래스와 유사하다.
//
// *NOTES*
//
// LoginPlayerManager를 ClientManager의 데이터 멤버로 정의할 수도 있지만,
// 패킷 핸들러에서 쉽게 접근하기 위해서는 글로벌 변수로 정의되어야 한다.
//
//////////////////////////////////////////////////////////////////////

class ClientManager {

public :

	// constructor
	ClientManager () throw ( Error );

	// destructor
	~ClientManager () throw ( Error );

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
extern ClientManager * g_pClientManager;

#endif
