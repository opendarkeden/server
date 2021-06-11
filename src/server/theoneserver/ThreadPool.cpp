//////////////////////////////////////////////////////////////////////
// 
// ThreadPool.cpp 
// 
// by Reiot
// 
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include <algorithm>
#include "ThreadPool.h"
#include "Assert.h"
#include "Thread.h"
#include "LogClient.h"

//////////////////////////////////////////////////
// function object for find_if ()
//////////////////////////////////////////////////

//
// 컨테이너속의 쓰레드 객체가 특정 TID를 갖고 있을 경우 true를 리턴한다.
//
class isSameTID {
public :

	// constructor
	isSameTID (TID tid) : m_TID(tid) {}

	//
	bool operator () (Thread* pThread) throw ()
	{
		return pThread->getTID() == m_TID;
	}

private :
	
	// thread identifier
	TID m_TID;

};

//////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////
ThreadPool::ThreadPool () 
	throw ()
{
	__BEGIN_TRY

	m_Mutex.setName("ThreadPool");
		
	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// destructor
// 포함하고 있는 모든 쓰레드 객체를 삭제해야 한다.
//////////////////////////////////////////////////////////////////////
ThreadPool::~ThreadPool () 
	throw ()
{
	__BEGIN_TRY
		
	//////////////////////////////////////////////////
	// enter critical section
	//////////////////////////////////////////////////
	m_Mutex.lock();
		
	/*
	list<Thread*>::iterator itr = m_Threads.begin();
	for (; itr != m_Threads.end() ; itr ++) 
	{
		Thread* temp = *itr;
		
		// 쓰레드는 종료한 상태여야 한다.
		Assert(temp != NULL && temp->getStatus() == Thread::EXIT);
		
		SAFE_DELETE(temp);
	}

	m_Threads.erase(m_Threads.begin() , m_Threads.end());
	
	g_pLogManager->Log5("after erase(begin , end) , list's size == %d\n" , m_Threads.size());
	
	*/
	
	list<Thread*>::iterator itr;
	
	while ((itr = m_Threads.begin()) != m_Threads.end()) 
	{
		// 아직도 리스트에 노드가 남아있다는 뜻이다.
		
		// 쓰레드는 종료한 상태여야 한다.
		Assert(*itr != NULL && (*itr)->getStatus() == Thread::EXIT);
		
		SAFE_DELETE(*itr);
		
		m_Threads.pop_front();
	}

	//////////////////////////////////////////////////
	// leave critical section
	//////////////////////////////////////////////////
	m_Mutex.unlock();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
// 쓰레드풀안에 등록된 쓰레드들을 RUNNING 상태로 만든다. 
//////////////////////////////////////////////////////////////////////
void ThreadPool::start () 
	throw (Error)
{
	__BEGIN_TRY
		
	log(LOG_DEBUG_MSG, "", "", "== ThreadPool has started ==");

	//////////////////////////////////////////////////
	// enter critical section
	//////////////////////////////////////////////////
	m_Mutex.lock();
		
	for (list<Thread*>::iterator itr = m_Threads.begin() ;
		  itr != m_Threads.end() ;
		  itr ++) {
		// start threads
		Assert(*itr != NULL);
		(*itr)->start();

		string msg = "== " + (*itr)->getName() + " has been started == ";
		log(LOG_DEBUG_MSG, "", "", msg);
	}

	//////////////////////////////////////////////////
	// leave critical section
	//////////////////////////////////////////////////
	m_Mutex.unlock();

	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
// 쓰레드풀안에 등록된 모든 쓰레드의 실행을 중단시킨다.
// (이는 singal 혹은 cancellation 으로 구현해야 하겠다.)
//////////////////////////////////////////////////////////////////////
void ThreadPool::stop () 
	throw (Error)
{
	__BEGIN_TRY
		
	throw UnsupportedError("do not use this method now...");

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// 쓰레드풀에 쓰레드 객체를 등록한다.
//////////////////////////////////////////////////////////////////////
void ThreadPool::addThread (Thread* thread) 
	throw (Error)
{
	__BEGIN_TRY
		
	//////////////////////////////////////////////////
	// enter critical section
	//////////////////////////////////////////////////
	m_Mutex.lock();

	// 쓰레드는 널이 아니어야 한다.
	Assert(thread != NULL);

	// 리스트의 맨 마지막에 쓰레드 객체를 삽입한다.
	m_Threads.push_back(thread);
	
	string msg = "== " + thread->getName() + " added to thread pool";
	log(LOG_DEBUG_MSG, "", "", msg);

	//////////////////////////////////////////////////
	// leave critical section
	//////////////////////////////////////////////////
	m_Mutex.unlock();

	__END_CATCH
}
	

//////////////////////////////////////////////////////////////////////
// 쓰레드풀에서 특정 쓰레드 객체를 삭제한다.
//////////////////////////////////////////////////////////////////////
void ThreadPool::deleteThread (TID tid) 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY
	
	//////////////////////////////////////////////////
	// enter critical section
	//////////////////////////////////////////////////
	m_Mutex.lock();

	// function object로 특정 TID를 가진 쓰레드 객체가 담긴 노드를 담은
	// iterator를 찾아낸다.
	list<Thread*>::iterator itr = find_if (m_Threads.begin() , m_Threads.end() , isSameTID(tid));
	
	if (itr != m_Threads.end()) // found!
	{ 
		// 쓰레드 객체를 임시로 저장해둔다.
		Thread* temp = *itr;
		
		// 쓰레드는 종료한 상태여야 한다.
		// 하위 클래스에 Mutex가 존재할 경우, getStatus(), setStatus()는 Mutex로 보호되어야 한다.
		Assert(temp != NULL && temp->getStatus() == Thread::EXIT);
		
		StringStream msg;
		msg << "== Thread[" << temp->getTID()
			<< "] has been removed from ThreadPool ==";
		log(LOG_DEBUG_MSG, "", "", msg.toString());

		// 쓰레드 객체를 삭제한다.
		SAFE_DELETE(temp);
		
		// 노드를 삭제한다.
		m_Threads.erase(itr);
	} 
	else // not found
	{						
		StringStream buf;
		buf << "TID(" << tid << ")" ;

		//////////////////////////////////////////////////
		// leave critical section
		//////////////////////////////////////////////////
		m_Mutex.unlock();

		throw NoSuchElementException(buf.toString());
	}
	
	//////////////////////////////////////////////////
	// leave critical section
	//////////////////////////////////////////////////
	m_Mutex.unlock();

	__END_CATCH
}

	
//////////////////////////////////////////////////////////////////////
// 쓰레드풀에서 특정 쓰레드 객체를 찾아서 리턴한다.
//////////////////////////////////////////////////////////////////////
Thread* ThreadPool::getThread (TID tid) 
	throw (NoSuchElementException , Error)
{
	__BEGIN_TRY
		
	Thread* thread = NULL;
	
	//////////////////////////////////////////////////
	// enter critical section
	//////////////////////////////////////////////////
	m_Mutex.lock();
		
	list<Thread*>::iterator itr = find_if (m_Threads.begin() , m_Threads.end() , isSameTID(tid));
	
	if (itr != m_Threads.end()) {	// found
		
		Assert(*itr != NULL);
		
		thread = *itr;

	} else {						// not found

		StringStream buf;
		buf << "TID(" << tid << ")" ;

		//////////////////////////////////////////////////
		// leave critical section
		//////////////////////////////////////////////////
		m_Mutex.unlock();

		throw NoSuchElementException(buf.toString());

	}

	//////////////////////////////////////////////////
	// leave critical section
	//////////////////////////////////////////////////
	m_Mutex.unlock();
	
	return thread;

	__END_CATCH
}
