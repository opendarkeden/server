//--------------------------------------------------------------------------------
// 
// Filename    : ThreadManager.cc
// Written By  : Reiot
// 
//--------------------------------------------------------------------------------

// include files
#include "ThreadManager.h"
#include "ThreadPool.h"
#include "ZoneGroupThread.h"
#include "Assert.h"
#include "LogClient.h"
#include "ZoneGroupManager.h"
#include "Properties.h"
#include "DB.h"


//--------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------
ThreadManager::ThreadManager () 
     throw (Error)
: m_pZoneGroupThreadPool(NULL)
{
	__BEGIN_TRY
		
	// 존쓰레드풀을 생성한다.
	m_pZoneGroupThreadPool = new ThreadPool();

	__END_CATCH
}

	
//--------------------------------------------------------------------------------
//
// destructor
//
// Stop()이 되지 않았을 경우 실행시켜야 한다. State 개념을 도입할까?
//
//--------------------------------------------------------------------------------
ThreadManager::~ThreadManager () 
     throw (Error)
{
	__BEGIN_TRY

	SAFE_DELETE(m_pZoneGroupThreadPool);

	__END_CATCH
}


//--------------------------------------------------------------------------------
//
// 쓰레드 매니저를 초기화한다.
//
// 하위 쓰레드풀에 쓰레드들을 생성, 등록시킨다.
//
// *CAUTION*
//
// 당연히, 쓰레드 매니저를 초기화하기 전에, 존그룹매니저를 초기화해야 한다.
//
//--------------------------------------------------------------------------------
void ThreadManager::init () 
     throw (Error)
{
	__BEGIN_TRY
		
	// 존 쓰레드를 등록한다.
	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	BEGIN_DB
	{
		pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT ZoneGroupID FROM ZoneGroupInfo");

		while (pResult->next()) 
		{
			ZoneGroupID_t zoneGroupID = pResult->getInt(1);
			ZoneGroupThread* pZoneGroupThread = new ZoneGroupThread(g_pZoneGroupManager->getZoneGroup(zoneGroupID));
			m_pZoneGroupThreadPool->addThread(pZoneGroupThread);
		}

		SAFE_DELETE(pStmt);
	} 
	END_DB(pStmt)

	__END_CATCH
}
	

//--------------------------------------------------------------------------------
//
// activate sub thread pools
//
// 하위 쓰레드 풀을 활성화시킨다. 
//
//--------------------------------------------------------------------------------
void ThreadManager::start () 
     throw (Error)
{
	__BEGIN_TRY

	// Zone Thread Pool 을 활성화시킨다.
	m_pZoneGroupThreadPool->start();
	
	__END_CATCH
}
	

//--------------------------------------------------------------------------------
//
// deactivate sub thread pools
//
// 하위 쓰레드 풀을 종료시킨다.
//
//--------------------------------------------------------------------------------
void ThreadManager::stop () 
     throw (Error)
{
	__BEGIN_TRY

	throw UnsupportedError();

	__END_CATCH
}


//--------------------------------------------------------------------------------
// global variable definition
//--------------------------------------------------------------------------------
ThreadManager* g_pThreadManager = NULL;
