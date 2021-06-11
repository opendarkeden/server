//////////////////////////////////////////////////////////////////////
// 
// ThreadPool.h 
// 
// by Reiot
// 
//////////////////////////////////////////////////////////////////////

#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include <list>
#include "Types.h"
#include "Exception.h"
#include "Thread.h"
#include "Mutex.h"


//////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//
// class ThreadPool
//
// 쓰레드 객체들의 컬렉션 클래스이다. 서버 종료시 활동중인 모든 쓰레드들을
// 중단시킬 때, 쓰레드풀 객체의 Stop메쏘드를 사용하면 된다. 내부적으로
// 시그널이나 캔슬레이션이 사용될 전망이다. 그런데, 아직은 자료가 없어서
// 구현을 못하고 있다. ^^;
//
//////////////////////////////////////////////////////////////////////

class ThreadPool {

//////////////////////////////////////////////////
// constructor/destructor
//////////////////////////////////////////////////
public:
	
	// constructor
	ThreadPool() throw();
	
	// destructor
	// 포함하고 있는 모든 쓰레드 객체를 삭제해야 한다.
	virtual ~ThreadPool() throw();

	
//////////////////////////////////////////////////
// methods
//////////////////////////////////////////////////
public:
	
	// 쓰레드풀안에 등록된 쓰레드들을 RUNNING 상태로 만든다. 
	void start() throw(Error);
	
	// 쓰레드풀안에 등록된 모든 쓰레드의 실행을 중단시킨다.
	//(이는 singal 혹은 cancellation 으로 구현해야 하겠다.)
	void stop() throw(Error);
	
	// 쓰레드풀에 쓰레드 객체를 등록한다.
	void addThread(Thread* thread) throw(Error);
	
	// 쓰레드풀에서 특정 쓰레드 객체를 삭제한다.
	void deleteThread(TID tid) throw(NoSuchElementException, Error);
	
	// 쓰레드풀에서 특정 쓰레드 객체를 찾아서 리턴한다.
	Thread* getThread(TID tid) throw(NoSuchElementException, Error);

//#ifdef __NO_COMBAT__
	list<Thread*> getThreads(){ return m_Threads; } // 김경석
//#endif

//////////////////////////////////////////////////
// attributes
//////////////////////////////////////////////////
private:
	
	//
	// 쓰레드 객체의 포인터에 대한 리스트
	// 실제로는 쓰레드 클래스의 하위 클래스가 들어가게 된다.
	// 일반적으로 같은 종류의 쓰레드들이 등록된다.
	//
	// ex> PlayerThreadPool - PlayerThread
	//     NPCThreadPool    - NPCThread
	//     MobThreadPool    - MobThread
	//
	list<Thread*> m_Threads;

	// mutex for list operation(add, delete, get ...)	
	mutable Mutex m_Mutex;
};

#endif
