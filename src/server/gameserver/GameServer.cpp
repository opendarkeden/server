//////////////////////////////////////////////////////////////////////////////
// Filename    : GameServer.cpp 
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include <time.h>
#include <signal.h>
#include <unistd.h>

#include "GameServer.h"
#include "Assert1.h"
#include "ThreadManager.h"
#include "ClientManager.h"
#include "ObjectManager.h"
#include "LoginServerManager.h"
#include "SharedServerManager.h"
//#include "LogClient.h"
#include "SystemAPI.h"

#include "PacketFactoryManager.h"
#include "PacketValidator.h"
#include "DatabaseManager.h"
#include "GameServerInfoManager.h"
#include "SharedServerManager.h"
#include "BillingPlayerManager.h"
//#include "GameServerTester.h"

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


GameServer::GameServer() throw(Error) {
	__BEGIN_TRY
	
	try {
		g_pDatabaseManager = new DatabaseManager();
		g_pObjectManager = new ObjectManager();
		g_pPacketFactoryManager = new PacketFactoryManager();
		g_pPacketValidator = new PacketValidator();
		g_pThreadManager = new ThreadManager();
		g_pLoginServerManager = new LoginServerManager();
		g_pSharedServerManager = new SharedServerManager();
#ifdef __CONNECT_BILLING_SYSTEM__
		g_pBillingPlayerManager = new BillingPlayerManager();
#endif
#ifdef __CONNECT_CBILLING_SYSTEM__
		g_pCBillingPlayerManager = new CBillingPlayerManager();
#endif
#ifdef __MOFUS__
        g_pMPlayerManager = new MPlayerManager();
        g_pMPacketManager = new MPacketManager();
#endif
		g_pClientManager = new ClientManager();
		g_pGameServerInfoManager = new GameServerInfoManager();
	
	}
	catch(Throwable & t) {
		throw;
	}

	__END_CATCH
}


GameServer::~GameServer() throw(Error) {
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


void GameServer::init() throw(Error) {
	__BEGIN_TRY
    cout << "[GAMESERVER] Loading System..." << endl;
	sysinit();
	cout << "[GAMESERVER] System Loaded." << endl;

	setCurrentTime();

    cout << "[GAMESERVER] Loading DBManager..." << endl;
	g_pDatabaseManager->init();
	cout << "[GAMESERVER] DBManager Loaded." << endl;

    cout << "[GAMESERVER] Loading ObjectManager..." << endl;
	g_pObjectManager->init();
	g_pObjectManager->load();
	cout << "[GAMESERVER] ObjectManager Loaded." << endl;

    cout << "[GAMESERVER] Loading ThreadManager..." << endl;
	g_pThreadManager->init();
	cout << "[GAMESERVER] ThreadManager Loaded." << endl;

    cout << "[GAMESERVER] Loading PacketFactoryManager..." << endl;
	g_pPacketFactoryManager->init();
	cout << "[GAMESERVER] PacketFactoryManagerLoaded." << endl;

    cout << "[GAMESERVER] Loading PacketValidator..." << endl;
	g_pPacketValidator->init();
	cout << "[GAMESERVER] PacketValidator Loaded." << endl;

    cout << "[GAMESERVER] Loading LoginServerManager..." << endl;
	g_pLoginServerManager->init();
	cout << "[GAMESERVER] LoginServerManager Loaded." << endl;
	
    cout << "[GAMESERVER] Loading SharedServerManager..." << endl;
	g_pSharedServerManager->init();
	cout << "[GAMESERVER] SharedServerManager Loaded." << endl;

#ifdef __CONNECT_BILLING_SYSTEM__
    cout << "[GAMESERVER] Loading BillingPlayerManager..." << endl;
	g_pBillingPlayerManager->init();
	cout << "[GAMESERVER] BillingPlayerManagerLoaded." << endl;
#endif

#ifdef __CONNECT_CBILLING_SYSTEM__
    cout << "[GAMESERVER] Loading BillingPlayerManager..." << endl;
	g_pCBillingPlayerManager->init();
	cout << "[GAMESERVER] BillingPlayerManager Loaded." << endl;
#endif

#ifdef __MOFUS__
    cout << "[GAMESERVER] Loading MofusPacketManager..." << endl;
    g_pMPacketManager->init();
    cout << "[GAMESERVER] MofusPacketManager Loaded." << endl;

    cout << "[GAMESERVER] Loading MofusPlayerManager..." << endl;
    g_pMPlayerManager->init();
    cout << "[GAMESERVER] MofusPlayerManager Loaded." << endl;
#endif

    cout << "[GAMESERVER] Loading GameServerInfoManager..." << endl;
	g_pGameServerInfoManager->init();
	cout << "[GAMESERVER] GameServerInfoManager Loaded." << endl;

    cout << "[GAMESERVER] Loading ClientManager..." << endl;
	g_pClientManager->init();
	cout << "[GAMESERVER] ClientManager Loaded." << endl;
	
	// 초기화가 끝이 나면, 콘솔 출력을 멈추고 백그라운드로 들어간다.
	//goBackground();

	__END_CATCH
}


void GameServer::start() throw(Error) {
	__BEGIN_TRY

	cout << "[GAMESERVER] Starting ThreadManager..." << endl;
	g_pThreadManager->start();
    cout << "[GAMESERVER] ThreadManagerStarted." << endl;
	
	cout << "[GAMESERVER] Starting LoginServerManager..." << endl;
	g_pLoginServerManager->start();
    cout << "[GAMESERVER] LoginServerManager Started." << endl;

	cout << "[GAMESERVER] Starting SharedServerManager..." << endl;
	g_pSharedServerManager->start();
    cout << "[GAMESERVER] SharedServerManager Started." << endl;

#ifdef __CONNECT_BILLING_SYSTEM__
	cout << "[GAMESERVER] Starting BillingPlayerManager..." << endl;
	g_pBillingPlayerManager->start();
    cout << "[GAMESERVER] BillingPlayerManager Started." << endl;
#endif

#ifdef __CONNECT_CBILLING_SYSTEM__
	cout << "[GAMESERVER] Starting CBillingPlayerManager..." << endl;
	g_pCBillingPlayerManager->start();
    cout << "[GAMESERVER] CBillingPlayerManager Started." << endl;
#endif

#ifdef __MOFUS__
    cout << "[GAMESERVER] Starting MPlayerManager..." << endl;
    g_pMPlayerManager->start();
    cout << "[GAMESERVER] MPlayerManager Started." << endl;
#endif

	//cout << "[GAMESERVER] Starting SMSServiceThread..." << endl;
	//SMSServiceThread::Instance().start();
    //cout << "[GAMESERVER] SMSServiceThread Started." << endl;

    cout << "[GAMESERVER] Initializing GDRLairManager..." << endl;
	GDRLairManager::Instance().init();
    cout << "[GAMESERVER] GDRLairManager Initialized." << endl;
    cout << "[GAMESERVER] Starting GDRLairManager..." << endl;
	GDRLairManager::Instance().start();
    cout << "[GAMESERVER] GDRLairManagerStarted." << endl;

	// 클라이언트 매니저를 시작한다.
	// *Reiot's Notes*
	// 가장 나중에 실행되어야 한다. 왜냐하면 멀티쓰레드기반이 아닌
	// 무한루프를 가진 함수이기 때문이다. 만일 이 다음에 다른 함수를
	// 호출할 경우, 루프가 끝나지 않는한(즉 에러가 발생하지 않는한)
	// 실행되지 않는다.	
	cout << "[GAMESERVER] Loaded." << endl;

	//log(LOG_SYSTEM, "", "", "Game Server Started");

	try {
        cout << "[GAMESERVER] Starting ClientManager..." << endl;
		g_pClientManager->start();
        cout << "[GAMESERVER] ClientManager Started." << endl;

	}
    catch (Throwable& t) {
		filelog("GameServerError.txt", "%s", t.toString().c_str());
		throw;
	}

	__END_CATCH
}

void GameServer::stop() throw(Error) {
	__BEGIN_TRY
		
	g_pClientManager->stop();

	g_pThreadManager->stop();
	
	//g_pObjectManager->save();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// 시스템 레벨의 초기화
//////////////////////////////////////////////////////////////////////////////

void GameServer::sysinit() throw(Error) {
	__BEGIN_TRY

	// rand() 를 위한 초기화
	srand(time(0));

	signal(SIGPIPE , SIG_IGN);	// 이거는 종종 발생할 듯
	signal(SIGALRM , SIG_IGN);	// 알람 하는 경우는 엄따, 예의상
	signal(SIGCHLD , SIG_IGN);	// fork 하는 경우는 엄따, 예의상

	__END_CATCH
}


void GameServer::goBackground() throw(Error) {
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

GameServer* g_pGameServer = NULL;
