//////////////////////////////////////////////////////////////////////
// 
// Filename    : LoginServer.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 로그인 서버용 메인 클래스
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "LoginServer.h"
#include "Assert.h"
#include "GameServerInfoManager.h"
#include "GameServerGroupInfoManager.h"
#include "GameServerManager.h"
#include "ClientManager.h"
#include "ZoneInfoManager.h"
#include "ZoneGroupInfoManager.h"
#include "database/DatabaseManager.h"
#include "PacketFactoryManager.h"
#include "PacketValidator.h"
#include "ItemDestroyer.h"
#include "UserInfoManager.h"
#include "GameWorldInfoManager.h"
//#include "gameserver/billing/BillingPlayerManager.h"
#include "chinabilling/CBillingPlayerManager.h"

#include "LogClient.h"

#ifdef __THAILAND_SERVER__

	#include "TimeChecker.h"
	
#endif

//////////////////////////////////////////////////////////////////////
//
// constructor
//
// 시스템 매니저의 constructor에서는 하위 매니저 객체를 생성한다.
//
//////////////////////////////////////////////////////////////////////
LoginServer::LoginServer ()
	throw ( Error )
{
	__BEGIN_TRY
	
	// create database manager
	g_pDatabaseManager = new DatabaseManager();

	// create some info managers
	g_pGameServerInfoManager = new GameServerInfoManager();
	g_pGameServerGroupInfoManager = new GameServerGroupInfoManager();

	g_pZoneInfoManager = new ZoneInfoManager();
	g_pZoneGroupInfoManager = new ZoneGroupInfoManager();
	
	// create packet factory manager, packet validator
	// (클라이언트 매니저와 서버간통신매니저보다 먼저 생성, 초기화되어야 한다.)
	g_pPacketFactoryManager = new PacketFactoryManager();
	g_pPacketValidator = new PacketValidator();
		
	// create inter-server communication manager
	g_pGameServerManager = new GameServerManager();

	// create client manager
	g_pClientManager = new ClientManager();

	// create ItemDestroyer
	g_pItemDestroyer = new ItemDestroyer();
	
	// create ItemDestroyer
	g_pUserInfoManager = new UserInfoManager();

	// create GameWorldInfoManager
	g_pGameWorldInfoManager = new GameWorldInfoManager();

	// login 서버에서는 빌링을 빼기로 한다.
	// 애드빌 요청. by bezz 2003.04.22
//#ifdef __CONNECT_BILLING_SYSTEM__
	// create GameWorldInfoManager
	//g_pBillingPlayerManager = new BillingPlayerManager();
//#endif

	// 중국 빌링
#ifdef __CONNECT_CBILLING_SYSTEM__
	// create CBillingPlayerManager
	g_pCBillingPlayerManager = new CBillingPlayerManager();
#endif

#ifdef __THAILAND_SERVER__

	g_pTimeChecker = new TimeChecker();
#endif
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// destructor
//
// 시스템 매니저의 destructor에서는 하위 매니저 객체를 삭제해야 한다.
//
//////////////////////////////////////////////////////////////////////
LoginServer::~LoginServer ()
	throw ( Error )
{
	__BEGIN_TRY
		
	if ( g_pClientManager != NULL ) {
		delete g_pClientManager;
		g_pClientManager = NULL;
	}

	if ( g_pGameServerManager != NULL ) {
		delete g_pGameServerManager;
		g_pGameServerManager = NULL;
	}
	
	if ( g_pPacketValidator != NULL ) {
		delete g_pPacketValidator;
		g_pPacketValidator = NULL;
	}

	if ( g_pPacketFactoryManager != NULL ) {
		delete g_pPacketFactoryManager;
		g_pPacketFactoryManager = NULL;
	}

	if ( g_pZoneGroupInfoManager != NULL ) {
		delete g_pZoneGroupInfoManager;
		g_pZoneGroupInfoManager = NULL;
	}
	
	if ( g_pZoneInfoManager != NULL ) {
		delete g_pZoneInfoManager;
		g_pZoneInfoManager = NULL;
	}
	
	if ( g_pGameServerInfoManager != NULL ) {
		delete g_pGameServerInfoManager;
		g_pGameServerInfoManager = NULL;
	}

	if ( g_pGameServerGroupInfoManager != NULL ) {
		delete g_pGameServerGroupInfoManager;
		g_pGameServerGroupInfoManager = NULL;
	}
	if ( g_pDatabaseManager != NULL ) {
		delete g_pDatabaseManager;
		g_pDatabaseManager = NULL;
	}
	if ( g_pUserInfoManager != NULL ) {
		delete g_pUserInfoManager;
		g_pUserInfoManager = NULL;
	}
	if ( g_pGameWorldInfoManager != NULL ) {
		delete g_pGameWorldInfoManager;
		g_pGameWorldInfoManager = NULL;
	}

	// login 서버에서는 빌링을 빼기로 한다.
	// 애드빌 요청. by bezz 2003.04.22
//#ifdef __CONNECT_BILLING_SYSTEM__
	//if ( g_pBillingPlayerManager != NULL ) {
		//delete g_pBillingPlayerManager;
		//g_pBillingPlayerManager = NULL;
	//}
//#endif

	// 중국 빌링
#ifdef __CONNECT_CBILLING_SYSTEM__
	// destroy CBillingPlayerManager
	if ( g_pCBillingPlayerManager != NULL ) {
		delete g_pCBillingPlayerManager;
		g_pCBillingPlayerManager = NULL;
	}
#endif

#ifdef __THAILAND_SERVER__
	if ( g_pTimeChecker != NULL )
	{
		delete g_pTimeChecker;
		g_pTimeChecker = NULL;
	}
	
#endif
	

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// initialize game server
//
//////////////////////////////////////////////////////////////////////
void LoginServer::init ()
	 throw ( Error )
{
	__BEGIN_TRY

	// 데이타베이스매니저를 초기화한다.
	g_pDatabaseManager->init();

	// initialize some info managers
	g_pGameServerInfoManager->init();
	g_pGameServerGroupInfoManager->init();
	g_pZoneInfoManager->init();
	g_pZoneGroupInfoManager->init();
	
	g_pGameWorldInfoManager->init();

	// 클라이언트매니저를 초기화하기 전에, 패킷팩토리매니저/패킷발리데이터를 초기화한다.
	g_pPacketFactoryManager->init();
	g_pPacketValidator->init();

	g_pUserInfoManager->init();

	// 서버간 통신 매니저를 초기화한다.
	g_pGameServerManager->init();
	
	// login 서버에서는 빌링을 빼기로 한다.
	// 애드빌 요청. by bezz 2003.04.22
//#ifdef __CONNECT_BILLING_SYSTEM__
	// 빌링 서버 접속 준비
	//g_pBillingPlayerManager->init();
//#endif

	// 중국 빌링
#ifdef __CONNECT_CBILLING_SYSTEM__
	// 중국 빌링 서버 접속 준비
	g_pCBillingPlayerManager->init();
#endif

#ifdef __THAILAND_SERVER__
	// for Thailand ChildGuard System
	g_pTimeChecker->init();
#endif
	
	
	// 만반의 준비가 끝이 나면 이제 클라이언트매니저를 초기화함으로써,
	// 네트워킹에 대비한다.
	g_pClientManager->init();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// start login server
//
//////////////////////////////////////////////////////////////////////
void LoginServer::start ()
	 throw ( Error )
{
	__BEGIN_TRY

	// 서버간 통신 매니저를 시작한다.
	g_pGameServerManager->start();
		
	// login 서버에서는 빌링을 빼기로 한다.
	// 애드빌 요청. by bezz 2003.04.22
//#ifdef __CONNECT_BILLING_SYSTEM__
	//g_pBillingPlayerManager->start();
//#endif
	// 중국 빌링
#ifdef __CONNECT_CBILLING_SYSTEM__
	// 중국 빌링 서버 돌려
	g_pCBillingPlayerManager->start();
#endif

	//
	// 클라이언트 매니저를 시작한다.
	//
	// *Reiot's Notes*
	//
	// 가장 나중에 실행되어야 한다. 왜냐하면 멀티쓰레드기반이 아닌
	// 무한루프를 가진 함수이기 때문이다. 만일 이 다음에 다른 함수를
	// 호출할 경우, 루프가 끝나지 않는한(즉 에러가 발생하지 않는한)
	// 다른 매니저의 처리 루프는 실행되지 않는다.	
	//
	g_pClientManager->start();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// stop login server
//
// stop 순서에 유의하도록 하자. 가장 영향을 많이 주는 매니저부터
// stop 시켜야 한다. 만일 반대의 순서로 stop 시킬 경우 null pointer
// 같은 현상이 발생할 수 있다.
//
//////////////////////////////////////////////////////////////////////
void LoginServer::stop ()
	 throw ( Error )
{
	__BEGIN_TRY

	// 나중에 이 부분을 코멘트화해야 한다.
	throw UnsupportedError();
		
	// 가장 먼저 클라이언트 매니저를 삭제시킴으로써 더이상 새 접속을 받지 않도록 한다.
	g_pClientManager->stop();
	
	//
	g_pGameServerManager->stop();

	// login 서버에서는 빌링을 빼기로 한다.
	// 애드빌 요청. by bezz 2003.04.22
//#ifdef __CONNECT_BILLING_SYSTEM__
	//g_pBillingPlayerManager->stop();
//#endif

	// 중국 빌링
#ifdef __CONNECT_CBILLING_SYSTEM__
	// 중국 빌링 서버 세워
	g_pCBillingPlayerManager->stop();
#endif

	__END_CATCH
}


//////////////////////////////////////////////////
// global variable declaration
//////////////////////////////////////////////////
LoginServer * g_pLoginServer = NULL;
