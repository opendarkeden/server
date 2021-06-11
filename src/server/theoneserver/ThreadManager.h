//--------------------------------------------------------------------------------
// 
// Filename    : ThreadManager.h 
// Written By  : Reiot
// Description :
// 
//--------------------------------------------------------------------------------

#ifndef __THREAD_MANAGER_H__
#define __THREAD_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"

// forward declaration
class ThreadPool;


//////////////////////////////////////////////////////////////////////
//
// class ThreadManager
//
// 게임 서버상의 모든(!) 쓰레드풀을 관리한다. 게임서버로부터 init, start,
// stop 명령이 떨어지면 하위 쓰레드풀의 같은 메쏘드를 호출한다.
//
// init  : 각 쓰레드풀에 옵션에서 지정한 개수의 쓰레드를 생성, 등록한다.
// start : 각 쓰레드풀에 등록된 쓰레드들을 활성화(start)시킨다.
// stop  : 각 쓰레드풀에 등록된 쓰레드들을 비활성화(stop)시킨다.
//
//////////////////////////////////////////////////////////////////////

class ThreadManager {

public:
	
	// constructor
	ThreadManager() throw(Error);
	
	// destructor
	~ThreadManager() throw(Error);

	
public:
	
	// 쓰레드 매니저를 초기화한다.
	void init() throw(Error);
	
	// activate sub thread pools
	// 하위 쓰레드 풀을 활성화시킨다.
	void start() throw(Error);
	
	// deactivate sub thread pools
	// 하위 쓰레드 풀을 종료시킨다.
	void stop() throw(Error);

//#ifdef __NO_COMBAT__
	ThreadPool* getThreadPool(){ return m_pZoneGroupThreadPool; } // 김경석
//#endif

private:
	
	// 쓰레드풀
	ThreadPool* m_pZoneGroupThreadPool;
	
};


// global variable declaration
extern ThreadManager* g_pThreadManager;

#endif
