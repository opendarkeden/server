//////////////////////////////////////////////////////////////////////
// 
// Filename    : TheOneServer.cpp 
// Written By  : reiot@ewestsoft.com
// Description : 로그인 서버용 메인 클래스
// 
//////////////////////////////////////////////////////////////////////

// include files
#include "TheOneServer.h"
#include "Assert.h"
#include "GameServerManager.h"
#include "database/DatabaseManager.h"
#include "PacketFactoryManager.h"
#include "UDPManager.h"

//////////////////////////////////////////////////////////////////////
//
// constructor
//
// 시스템 매니저의 constructor에서는 하위 매니저 객체를 생성한다.
//
//////////////////////////////////////////////////////////////////////
TheOneServer::TheOneServer ()
	throw ( Error )
{
	__BEGIN_TRY
	
	// create database manager
	g_pDatabaseManager = new DatabaseManager();

	g_pPacketFactoryManager = new PacketFactoryManager();

	// create inter-server communication manager
	g_pGameServerManager = new GameServerManager();

	//g_pUDPManager = new UDPManager();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// destructor
//
// 시스템 매니저의 destructor에서는 하위 매니저 객체를 삭제해야 한다.
//
//////////////////////////////////////////////////////////////////////
TheOneServer::~TheOneServer ()
	throw ( Error )
{
	__BEGIN_TRY
		
	SAFE_DELETE(g_pGameServerManager);
	SAFE_DELETE(g_pPacketFactoryManager);
	SAFE_DELETE(g_pDatabaseManager);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// initialize game server
//
//////////////////////////////////////////////////////////////////////
void TheOneServer::init ()
	 throw ( Error )
{
	__BEGIN_TRY

	cout << "Init DatabaseManager..." << endl;
	// 데이타베이스매니저를 초기화한다.
	g_pDatabaseManager->init();
	cout << "Init DatabaseManager Complete!" << endl;

	g_pPacketFactoryManager->init();

	// 서버간 통신 매니저를 초기화한다.
	g_pGameServerManager->init();
	
	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// start login server
//
//////////////////////////////////////////////////////////////////////
void TheOneServer::start ()
	 throw ( Error )
{
	__BEGIN_TRY

	// 서버간 통신 매니저를 시작한다.
	g_pGameServerManager->start();
		
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
void TheOneServer::stop ()
	 throw ( Error )
{
	__BEGIN_TRY

	g_pGameServerManager->stop();

	__END_CATCH
}


//////////////////////////////////////////////////
// global variable declaration
//////////////////////////////////////////////////
TheOneServer * g_pTheOneServer = NULL;
