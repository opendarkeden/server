//////////////////////////////////////////////////////////////////////////////
// Filename    : GameServer.cpp 
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include <time.h>
#include <signal.h>
#include <unistd.h>

#include "GameServer.h"
#include "Assert.h"
#include "ThreadManager.h"
#include "ClientManager.h"
#include "ObjectManager.h"
#include "LoginServerManager.h"
#include "SharedServerManager.h"
#include "LogClient.h"
#include "SystemAPI.h"

#include "PacketFactoryManager.h"
#include "PacketValidator.h"
#include "DatabaseManager.h"
#include "GameServerInfoManager.h"
#include "SharedServerManager.h"
#include "BillingPlayerManager.h"
#include "GameServerTester.h"

#include "chinabilling/CBillingInfo.h"
#ifdef __CONNECT_CBILLING_SYSTEM__
	#include "chinabilling/CBillingPlayerManager.h"
#endif

#include "mofus/Mofus.h"
#ifdef __MOFUS__
	#include "mofus/MPlayerManager.h"
	#include "mofus/MPacketManager.h"
#endif

#include "SMSServiceThread.h"
#include "GDRLairManager.h"


////////////////////////////////////////////////////////////////////////////////
// constructor
////////////////////////////////////////////////////////////////////////////////

GameServer::GameServer ()
	throw (Error)
{
	__BEGIN_TRY
	
	try 
	{
		// create database manager
		g_pDatabaseManager = new DatabaseManager();

		// create object manager
		g_pObjectManager = new ObjectManager();
		
		// create packet factory manager , packet validator
		g_pPacketFactoryManager = new PacketFactoryManager();
		g_pPacketValidator = new PacketValidator();

		// create thread manager
		g_pThreadManager = new ThreadManager();

		// create login server manager
		g_pLoginServerManager = new LoginServerManager();

		// create shared server manager
		g_pSharedServerManager = new SharedServerManager();

		// create billing player manager
#ifdef __CONNECT_BILLING_SYSTEM__
		g_pBillingPlayerManager = new BillingPlayerManager();
#endif
	
		// create china billing player manager
#ifdef __CONNECT_CBILLING_SYSTEM__
		g_pCBillingPlayerManager = new CBillingPlayerManager();
#endif
	
#ifdef __MOFUS__
        g_pMPlayerManager = new MPlayerManager();
        g_pMPacketManager = new MPacketManager();
#endif

		// create client manager
		g_pClientManager = new ClientManager();

		// create login server manager
		g_pGameServerInfoManager = new GameServerInfoManager();
	
	} 
	catch (Throwable & t) 
	{
		//cout << t.toString() << endl;
		throw;
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// destructor
// stop()을 거치지 않고 게임 서버가 종료되는 것을 체크해줘야 한다.
//////////////////////////////////////////////////////////////////////////////

GameServer::~GameServer ()
	throw (Error)
{
	__BEGIN_TRY

	SAFE_DELETE(g_pClientManager);
	SAFE_DELETE(g_pObjectManager);
	SAFE_DELETE(g_pPacketValidator);
	SAFE_DELETE(g_pPacketFactoryManager);
	SAFE_DELETE(g_pLoginServerManager);
	SAFE_DELETE(g_pSharedServerManager);
#ifdef __CONNECT_BILLING_SYSTEM__
	SAFE_DELETE(g_pBillingPlayerManager);
#endif
#ifdef __CONNECT_CBILLING_SYSTEM__
	SAFE_DELETE(g_pCBillingPlayerManager);
#endif
#ifdef __MOFUS__
    SAFE_DELETE(g_pMPlayerManager);
    SAFE_DELETE(g_pMPacketManager);
#endif
	SAFE_DELETE(g_pGameServerInfoManager);
	SAFE_DELETE(g_pThreadManager);
	SAFE_DELETE(g_pDatabaseManager);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// initialize game server
//////////////////////////////////////////////////////////////////////////////

void GameServer::init ()
	 throw (Error)
{
	__BEGIN_TRY

	sysinit();
	cout << "GameServer::init() : System Initialization Success..." << endl;

	// gCurrentTime을 세팅한다.
	setCurrentTime();

	// 데이타베이스매니저를 초기화한다.
	g_pDatabaseManager->init();
	cout << "GameServer::init() : DatabaseManager Initialization Success..." << endl;

	// 데이타베이스매니저를 통해서 오브젝트매니저를 초기화한다. 
	g_pObjectManager->init();
	g_pObjectManager->load();
	cout << "GameServer::init() : ObjectManager Initialization Success..." << endl;

	// 오브젝트 매니저를 기반으로 쓰레드매니저를 초기화한다.
	// (특히 ZoneThreadPool은 ZoneGroupManager가 먼저 초기화되어야 한다.
	g_pThreadManager->init();
	cout << "GameServer::init() : ThreadManager Initialization Success..." << endl;
		
	// 클라이언트매니저를 초기화하기 전에, 패킷팩토리매니저/패킷발리데이터를 초기화한다.
	g_pPacketFactoryManager->init();
	cout << "GameServer::init() : PacketFactoryManager Initialization Success..." << endl;

	g_pPacketValidator->init();
	cout << "GameServer::init() : PacketValidator Initialization Success..." << endl;

	// 이제 서버간 통신 준비에 들어간다.
	g_pLoginServerManager->init();
	cout << "GameServer::init() : LoginServerManager Initialization Success..." << endl;
	
	// shared server 와의 통신 준비에 들어간다.
	g_pSharedServerManager->init();
	cout << "GameServer::init() : SharedServerManager Initialization Success..." << endl;

#ifdef __CONNECT_BILLING_SYSTEM__
	// shared server 와의 통신 준비에 들어간다.
	g_pBillingPlayerManager->init();
	cout << "GameServer::init() : BillingPlayerManager Initialization Success..." << endl;
#endif

#ifdef __CONNECT_CBILLING_SYSTEM__
	// china billing server 와의 통신 준비에 들어간다.
	g_pCBillingPlayerManager->init();
	cout << "GameServer::init() : CBillingPlayerManager Initialization Success..." << endl;
#endif

#ifdef __MOFUS__
    g_pMPacketManager->init();
    cout << "GameServer::init() : MPacketManager Initialization Success..." << endl;

    g_pMPlayerManager->init();
    cout << "GameServer::init() : MPlayerManager Initialization Success..." << endl;
#endif

	g_pGameServerInfoManager->init();
	cout << "GameServer::init() : GameServerInfoManager Initialization Success..." << endl;

	// 만반의 준비가 끝이 나면 이제 클라이언트매니저를 초기화함으로써,
	// 네트워킹에 대비한다.
	g_pClientManager->init();
	cout << "GameServer::init() : ClientManager Initialization Success..." << endl;
	
	// 초기화가 끝이 나면, 콘솔 출력을 멈추고 백그라운드로 들어간다.
	//goBackground();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// start game server
//////////////////////////////////////////////////////////////////////////////

void GameServer::start ()
	 throw (Error)
{
	__BEGIN_TRY
		
	cout << ">>> STARTING THREAD MANAGER..." << endl;
	g_pThreadManager->start();
	
	cout << ">>> STARTING LOGIN SERVER MANAGER..." << endl;
	g_pLoginServerManager->start();

	cout << ">>> STARTING SHARED SERVER MANAGER..." << endl;
	g_pSharedServerManager->start();

#ifdef __CONNECT_BILLING_SYSTEM__
	cout << ">>> STARTING BILLING PLAYER MANAGER..." << endl;
	g_pBillingPlayerManager->start();
#endif

#ifdef __CONNECT_CBILLING_SYSTEM__
	cout << ">>> STARTING CBILLING PLAYER MANAGER..." << endl;
	g_pCBillingPlayerManager->start();
#endif

#ifdef __MOFUS__
    g_pMPlayerManager->start();
    cout << ">>> STARTING MOFUS PLAYER MANAGER..." << endl;
#endif
	
	//add by zdj
	//cout << ">>> STARTING SMS SERVICE THREAD..." << endl;
	//SMSServiceThread::Instance().start();

//	cout << ">>> STARTING Gilles De Rais Lair Manager THREAD..." << endl;
	GDRLairManager::Instance().init();
	GDRLairManager::Instance().start();

	// 클라이언트 매니저를 시작한다.
	// *Reiot's Notes*
	// 가장 나중에 실행되어야 한다. 왜냐하면 멀티쓰레드기반이 아닌
	// 무한루프를 가진 함수이기 때문이다. 만일 이 다음에 다른 함수를
	// 호출할 경우, 루프가 끝나지 않는한(즉 에러가 발생하지 않는한)
	// 실행되지 않는다.	
	cout << ">>> ALL INITIALIZATIONS ARE COMPLETED SUCCESSFULLY." << endl;
	cout << ">>> STARTING ClientManager->start() INFINITE LOOP..." << endl;

	log(LOG_SYSTEM, "", "", "Game Server Started");

	// 테스트 by sigi. 2002.12.26
	if (g_pTestConfig!=NULL)
	{
		testGameServer();
	}

	try {

		g_pClientManager->start();

	} catch (Throwable& t) {
		filelog("GameServerError.txt", "%s", t.toString().c_str());
		throw;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// stop game server
//
// stop 순서에 유의하도록 하자. 가장 영향을 많이 주는 매니저부터
// stop 시켜야 한다. 만일 반대의 순서로 stop 시킬 경우 null pointer
// 같은 현상이 발생할 수 있다.
//
// 따라서, 쓰레드 관련 매니저부터 삭제해야 한다.
//////////////////////////////////////////////////////////////////////////////

void GameServer::stop ()
	 throw (Error)
{
	__BEGIN_TRY
		
	//
	// stop client manager
	//
	// 가장 먼저 클라이언트 매니저를 삭제시킴으로써 더이상 새 접속을 
	// 받지 않도록 한다.
	//
	g_pClientManager->stop();
	
	//
	// stop thread manager
	//
	// 그다음, 쓰레드매니저를 삭제함으로써 기존의 사용자들을 더이상 처리하지
	// 않고 게임 서버에서 쫓아낸다. 이때 쓰레드 매니저의 하위 쓰레드풀에서
	// stop을 실행할때 적절하게 잘 되어야 한다.
	//
	g_pThreadManager->stop();
	
	//
	// stop object manager
	//
	// 이제 모든 사용자들의 접속이 종료되었으므로, 남은 존 및 여러 가지 게임
	// 환경들을 데이타베이스로 저장하도록 한다.
	//
	//g_pObjectManager->save();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 시스템 레벨의 초기화
//////////////////////////////////////////////////////////////////////////////

void GameServer::sysinit()
	throw (Error)
{
	__BEGIN_TRY

	// rand() 를 위한 초기화
	srand(time(0));

	signal(SIGPIPE , SIG_IGN);	// 이거는 종종 발생할 듯
	signal(SIGALRM , SIG_IGN);	// 알람 하는 경우는 엄따, 예의상
	signal(SIGCHLD , SIG_IGN);	// fork 하는 경우는 엄따, 예의상

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 나중에 콘솔로 출력할 필요가 없어질 만큼 안정적이 되면, 
// 이 함수를 호출하도록 한다.
//////////////////////////////////////////////////////////////////////////////

void GameServer::goBackground ()
	throw (Error)
{
	__BEGIN_TRY

	int forkres = SystemAPI::fork_ex();

	if (forkres == 0) {
		// case of child process
		close(0);
		close(1);
		close(2);
	} else {
		// case of parent process
		exit(0);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// global variable declaration
//////////////////////////////////////////////////////////////////////////////
GameServer* g_pGameServer = NULL;
