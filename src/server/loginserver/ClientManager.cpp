//////////////////////////////////////////////////////////////////////
//
// Filename    : ClientManager.cpp
// Written by  : reiot@ewestsoft.com
// Description : 로그인 서버용 클라이언트 매니저
//
//////////////////////////////////////////////////////////////////////

#include "DatabaseManager.h"
#include "ClientManager.h"
#include "Assert.h"
#include "LoginPlayerManager.h"
#include "ReconnectLoginInfoManager.h"
#include "Profile.h"
#include "PacketProfile.h"
#include "Timeval.h"
#include "Properties.h"

#include "GameWorldInfoManager.h"
#include "GameServerGroupInfoManager.h"

#ifdef __THAILAND_SERVER__
	
	#include "TimeChecker.h"

#endif

//////////////////////////////////////////////////////////////////////
//
// constructor
//
// 하위 매니저 객체를 생성하는 곳이다.
//
//////////////////////////////////////////////////////////////////////
ClientManager::ClientManager () 
	throw ( Error )
{
	__BEGIN_TRY

	// 로그인 플레이어 매니저를 생성한다.
	g_pLoginPlayerManager = new LoginPlayerManager();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// destructor
//
// 하위 매니저 객체를 삭제하는 곳이다.
//
//////////////////////////////////////////////////////////////////////
ClientManager::~ClientManager () 
	throw ( Error )
{
	__BEGIN_TRY

	// 로그인 플레이어 매니저를 삭제한다.
	if ( g_pLoginPlayerManager != NULL ) {
		delete g_pLoginPlayerManager;
		g_pLoginPlayerManager = NULL;	
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// 하위 매니저 객체를 초기화하고, 자신을 초기화한다.
//
//////////////////////////////////////////////////////////////////////
void ClientManager::init ()
	throw ( Error )
{
	__BEGIN_TRY

	g_pLoginPlayerManager->init();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// 서비스를 시작한다.
//
//////////////////////////////////////////////////////////////////////
void ClientManager::start ()
	throw ( Error )
{
	__BEGIN_TRY

	run();		// 바로 run() 메쏘드를 호출한다. ^^;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// 자신의 서비스를 중단한 후, 하위 매니저 객체들의 서비스를 중단시킨다.
//
//////////////////////////////////////////////////////////////////////
void ClientManager::stop ()
	throw ( Error )
{
	__BEGIN_TRY

	throw UnsupportedError("stopping manager not supported.");

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 클라이언트 매니저의 메인 루프이다.
//////////////////////////////////////////////////////////////////////
void ClientManager::run ()
	throw ( Error )
{
	__BEGIN_TRY

	Assert( g_pLoginPlayerManager != NULL );

	Timeval NextTime;
	getCurrentTime(NextTime);

	// GameWorldInfo, GameServerInfo 새로 로드하는 시간
	Timeval ReloadNextTime = NextTime;
	// GameWorldInfo, GameServerInfo 새로 로드하는 시간 간격, 분 단위
	int ReloadGap = g_pConfig->getPropertyInt("ServerInfoReloadTime") * 60;
	ReloadNextTime.tv_sec += ReloadGap;

	NextTime.tv_sec += 10;

	Timeval dummyQueryTime;
	getCurrentTime(dummyQueryTime);

	while ( true ) 
	{
		usleep(100);

		beginProfileEx("LS_MAIN");

		beginProfileEx("LPM_SELECT");
		g_pLoginPlayerManager->select();
		endProfileEx("LPM_SELECT");

		beginProfileEx("LPM_EXCEPTION");
		g_pLoginPlayerManager->processExceptions();
		endProfileEx("LPM_EXCEPTION");

		beginProfileEx("LPM_INPUT");
		g_pLoginPlayerManager->processInputs();
		endProfileEx("LPM_INPUT");

		beginProfileEx("LPM_COMMAND");
		g_pLoginPlayerManager->processCommands();
		endProfileEx("LPM_COMMAND");

		beginProfileEx("LPM_OUTPUT");
		g_pLoginPlayerManager->processOutputs();
		endProfileEx("LPM_OUTPUT");

		beginProfileEx("LPM_HEARTBEAT");
		g_pReconnectLoginInfoManager->heartbeat();
		endProfileEx("LPM_HEARTBEAT");

		endProfileEx("LS_MAIN");

		Timeval currentTime;
		getCurrentTime(currentTime);

		if (NextTime < currentTime)
		{
			//outputProfileEx(false, false);
			(g_ProfileSampleManager.getProfileSampleSet())->outputProfileToFile("Profile", false, false);

			NextTime.tv_sec = currentTime.tv_sec + 10;
			NextTime.tv_usec = currentTime.tv_usec;

			// 매턴마다 프로파일 데이터를 초기화해준다.
			// 누적 데이터보다는 시간대에 따른 시간을 측정하기 위해서...
			initProfileEx();

			//g_PacketProfileManager.outputResultToFile("PacketProfile.txt");
			g_PacketProfileManager.init();
		}

		if ( ReloadNextTime < currentTime )
		{
			if ( g_pGameWorldInfoManager != NULL )
			{
				g_pGameWorldInfoManager->load();
			}

			if ( g_pGameServerGroupInfoManager != NULL )
			{
				g_pGameServerGroupInfoManager->load();
			}

			ReloadNextTime.tv_sec += ReloadGap;
		}

		// DB connection 이 timeout 으로 끊어지지 않게 가끔씩 의미없는 쿼리함해준다.
		// by bezz. 2003.04.21
		if ( dummyQueryTime < currentTime )
		{
			g_pDatabaseManager->executeDummyQuery( g_pDatabaseManager->getConnection("DARKEDEN") );

			dummyQueryTime.tv_sec += (60+rand()%30) * 60;
		}
#ifdef __THAILAND_SERVER__
	
		g_pTimeChecker->heartbeat();
#endif
		
	}

	__END_CATCH
}
	

// global variable definition
ClientManager * g_pClientManager = NULL;
