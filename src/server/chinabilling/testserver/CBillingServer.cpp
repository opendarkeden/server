//////////////////////////////////////////////////////////////////////
// 
// Filename    : CBillingServer.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 중국 빌링 서버(테스트)용 메인 클래스
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "CBillingServer.h"
#include "Assert.h"
#include "GameServerManager.h"
#include "database/DatabaseManager.h"

#include "LogClient.h"

//////////////////////////////////////////////////////////////////////
//
// constructor
//
// 시스템 매니저의 constructor에서는 하위 매니저 객체를 생성한다.
//
//////////////////////////////////////////////////////////////////////
CBillingServer::CBillingServer ()
	throw ( Error )
{
	__BEGIN_TRY
	
	// create inter-server communication manager
	g_pGameServerManager = new GameServerManager();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// destructor
//
// 시스템 매니저의 destructor에서는 하위 매니저 객체를 삭제해야 한다.
//
//////////////////////////////////////////////////////////////////////
CBillingServer::~CBillingServer ()
	throw ( Error )
{
	__BEGIN_TRY
		
	SAFE_DELETE( g_pGameServerManager );

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// initialize game server
//
//////////////////////////////////////////////////////////////////////
void CBillingServer::init ()
	 throw ( Error )
{
	__BEGIN_TRY

	cout << "CBillingServer::init() start" << endl;

	// 서버간 통신 매니저를 초기화한다.
	g_pGameServerManager->init();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// start shared server
//
//////////////////////////////////////////////////////////////////////
void CBillingServer::start ()
	 throw ( Error )
{
	__BEGIN_TRY

	cout << "---------- Start CBillingServer ---------" << endl;
	// 서버간 통신 매니저를 시작한다.
	g_pGameServerManager->start();
		
	while ( true )
	{
		usleep( 100 );
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// stop shared server
//
// stop 순서에 유의하도록 하자. 가장 영향을 많이 주는 매니저부터
// stop 시켜야 한다. 만일 반대의 순서로 stop 시킬 경우 null pointer
// 같은 현상이 발생할 수 있다.
//
//////////////////////////////////////////////////////////////////////
void CBillingServer::stop ()
	 throw ( Error )
{
	__BEGIN_TRY

	// 나중에 이 부분을 코멘트화해야 한다.
	throw UnsupportedError();
		
	//
	g_pGameServerManager->stop();

	__END_CATCH
}


//////////////////////////////////////////////////
// global variable declaration
//////////////////////////////////////////////////
CBillingServer * g_pCBillingServer = NULL;
