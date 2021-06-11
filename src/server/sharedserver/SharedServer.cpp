//////////////////////////////////////////////////////////////////////
// 
// Filename    : SharedServer.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 쉐어드 서버용 메인 클래스
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "SharedServer.h"
#include "Assert.h"
#include "GameServerInfoManager.h"
#include "GameServerGroupInfoManager.h"
#include "GameServerManager.h"
#include "HeartbeatManager.h"
#include "database/DatabaseManager.h"
#include "PacketFactoryManager.h"
#include "PacketValidator.h"
#include "GameWorldInfoManager.h"
#include "GuildManager.h"
#include "ResurrectLocationManager.h"
#include "StringPool.h"

#include "LogClient.h"

#include "types/ServerType.h"
#ifdef __NETMARBLE_SERVER__
	#include "NetmarbleGuildRegisterThread.h"
#endif

//////////////////////////////////////////////////////////////////////
//
// constructor
//
// 시스템 매니저의 constructor에서는 하위 매니저 객체를 생성한다.
//
//////////////////////////////////////////////////////////////////////
SharedServer::SharedServer ()
	throw ( Error )
{
	__BEGIN_TRY
	
	// create database manager
	g_pDatabaseManager = new DatabaseManager();

	// create guild manager
	g_pGuildManager = new GuildManager();

	// create some info managers
	g_pGameServerInfoManager = new GameServerInfoManager();
	g_pGameServerGroupInfoManager = new GameServerGroupInfoManager();

	// create packet factory manager, packet validator
	// (클라이언트 매니저와 서버간통신매니저보다 먼저 생성, 초기화되어야 한다.)
	g_pPacketFactoryManager = new PacketFactoryManager();
	g_pPacketValidator = new PacketValidator();
		
	// create inter-server communication manager
	g_pGameServerManager = new GameServerManager();

	// create client manager
	g_pHeartbeatManager = new HeartbeatManager();

	// create GameWorldInfoManager
	g_pGameWorldInfoManager = new GameWorldInfoManager();

	// create ResurrectLocationManager
	g_pResurrectLocationManager = new ResurrectLocationManager();

	g_pStringPool = new StringPool();

/*#ifdef __NETMARBLE_SERVER__
	g_pNetmarbleGuildRegisterThread = new NetmarbleGuildRegisterThread();
#endif*/

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// destructor
//
// 시스템 매니저의 destructor에서는 하위 매니저 객체를 삭제해야 한다.
//
//////////////////////////////////////////////////////////////////////
SharedServer::~SharedServer ()
	throw ( Error )
{
	__BEGIN_TRY
		
	SAFE_DELETE( g_pHeartbeatManager );
	SAFE_DELETE( g_pGameServerManager );
	SAFE_DELETE( g_pPacketValidator );
	SAFE_DELETE( g_pPacketFactoryManager );
	SAFE_DELETE( g_pGameServerInfoManager );
	SAFE_DELETE( g_pGameServerGroupInfoManager );
	SAFE_DELETE( g_pGuildManager );
	SAFE_DELETE( g_pDatabaseManager );
	SAFE_DELETE( g_pGameWorldInfoManager );
	SAFE_DELETE( g_pResurrectLocationManager );
	SAFE_DELETE( g_pStringPool );

/*#ifdef __NETMARBLE_SERVER__
	SAFE_DELETE( g_pNetmarbleGuildRegisterThread );
#endif*/

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// initialize game server
//
//////////////////////////////////////////////////////////////////////
void SharedServer::init ()
	 throw ( Error )
{
	__BEGIN_TRY

	cout << "SharedServer::init() start" << endl;

	// 데이타베이스매니저를 초기화한다.
	g_pDatabaseManager->init();

	g_pStringPool->load();

	// guild manager 를 초기화한다.
	g_pGuildManager->init();

	// initialize some info managers
	g_pGameServerInfoManager->init();
	g_pGameServerGroupInfoManager->init();
	
	g_pGameWorldInfoManager->init();

	// 클라이언트매니저를 초기화하기 전에, 패킷팩토리매니저/패킷발리데이터를 초기화한다.
	g_pPacketFactoryManager->init();
	g_pPacketValidator->init();

	// 서버간 통신 매니저를 초기화한다.
	g_pGameServerManager->init();

	// ResurrectLocationManager 초기화
	g_pResurrectLocationManager->init();

/*#ifdef __NETMARBLE_SERVER__
	g_pNetmarbleGuildRegisterThread->init();
#endif*/
	
	// 만반의 준비가 끝이 나면 이제 클라이언트매니저를 초기화함으로써,
	// 네트워킹에 대비한다.
	g_pHeartbeatManager->init();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// start shared server
//
//////////////////////////////////////////////////////////////////////
void SharedServer::start ()
	 throw ( Error )
{
	__BEGIN_TRY

	cout << "---------- Start SharedServer ---------" << endl;
	// 서버간 통신 매니저를 시작한다.
	g_pGameServerManager->start();

	// 넷마블 길드 등록 스레드 시작
/*#ifdef __NETMARBLE_SERVER__
	g_pNetmarbleGuildRegisterThread->start();
#endif*/
		
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
	g_pHeartbeatManager->start();

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
void SharedServer::stop ()
	 throw ( Error )
{
	__BEGIN_TRY

	// 나중에 이 부분을 코멘트화해야 한다.
	throw UnsupportedError();
		
	// 
	g_pHeartbeatManager->stop();
	
	//
	g_pGameServerManager->stop();

	__END_CATCH
}


//////////////////////////////////////////////////
// global variable declaration
//////////////////////////////////////////////////
SharedServer * g_pSharedServer = NULL;
