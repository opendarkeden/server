////////////////////////////////////////////////////////////////////////////////
//
// Thread.cpp
//
// by Reiot, the Lord of MUDMANIA(TM)
//
// Last Updated : 1999. 07. 02.
//
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include "Thread.h"
#include "ThreadAttr.h"
#include "pthreadAPI.h"

using namespace pthreadAPI;


////////////////////////////////////////////////////////////////////////////////
//
// constructor
//
////////////////////////////////////////////////////////////////////////////////
//
// Thread 클래스를 상속받은 DerivedThread 는 최소한 ThreadAttr 를 공유하게 된다. 
// 만약 DerivedThread 를 여러 개 만들 필요가 있다면, 그 메쏘드 내에서 적절한 
// ThreadAttr 를 생성한 후에, 이를 하위 쓰레드의 생성자에 넘겨주고 모든 하위 
// 쓰레드를 생성한 후에, Thread-Attribute 객체를 삭제하면 될 것이다.
//
// 주의할 점은, 객체 생성과 실제 쓰레드의 시작은 동시에 이루어지지 않는다는
// 것이다. 즉 모든 쓰레드의 Start() 를 수행한 후에 ThreadAttr 객체를 삭제해야
// 한다. 그렇지 않으면 에러가 날 것이다.
//
// 또한 모든 쓰레드는 new 로 생성해야 한다. 현재 pthread_create() 의 마지막 
// 파라미터로 쓰레드 객체의 주소를 넘겨주게 되는데, 이때 함수 스택에 쓰레드 
// 객체가 생성될 경우 Scope Rule에 의해 에러가 나게 된다. 무조건 쓰레드 객체는 
// 힙(Heap)에 생성해야만 한다!!!
//
////////////////////////////////////////////////////////////////////////////////
Thread::Thread ( ThreadAttr * attr ) 
	 throw ()
: m_TID(0) , m_ThreadAttr(attr), m_Status(Thread::READY)
{
}


////////////////////////////////////////////////////////////////////////////////
//
// destructor (virtual)
//
////////////////////////////////////////////////////////////////////////////////
//
// DerivedThread 클래스에서 추가된 attribute 를 삭제토록 하기 위해서 virtual 로
// 정의되어 있다. 실제로는 아무런 일도 하지 않는다.
//
////////////////////////////////////////////////////////////////////////////////
Thread::~Thread () 
	 throw ()
{
}


////////////////////////////////////////////////////////////////////////////////
//
// 쓰레드를 생성한다.
//
////////////////////////////////////////////////////////////////////////////////
//
// pthread_create() 에 대해서 살펴보도록 하자.
//
// int pthread_create ( pthread_t * tid , 
//                      pthread_attr_t * atttr , 
//                      void * (*start_routine)(void*) , 
//                      void * arg 
//                    );
//
// 생성에 성공하면 0 을 리턴하며, 실패할 경우 에러 코드를 리턴한다.
// 에러 코드는 EAGAIN 이 유일하며, 시스템 리소스가 부족하거나 쓰레드 숫자가
// 너무 많음을 의미한다.
//
// tid 의 포인터를 첫번째 파라미터로 주면, 그 안에 thread identifier 가 저장된다.
//
// attr 이 NULL 일 경우 Default Attribute 를 가진 쓰레드가 생성된다. 특별히
// 어떤 속성을 지정하려면 적절한 pthread_attr_t 를 제공하면 될 것이다.
//
// start_routine 으로는 Thread 클래스의 friend method 를 사용하는데, 이때 arg 로
// this - Thread Object - 를 제공하게 된다. 그러면, start_routine 안에서는 
// polymorphism 을 사용해서 하위 클래스의 run() 메쏘드를 자동으로 호출하게 
// 되므로.. 모든 것은 가능해진다. -_-;
//
////////////////////////////////////////////////////////////////////////////////
void Thread::start () 
     throw ( ThreadException , Error )
{ 
	__BEGIN_TRY
		
	if ( m_Status != Thread::READY )
		throw ThreadException("invalid thread's status");

	pthread_create_ex( &m_TID, ( m_ThreadAttr == NULL ? NULL : m_ThreadAttr->getAttr() ) , start_routine , this );
	
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
//
// 하위 클래스에서 뮤텍스를 내포하면서 재정의해야 한다.
//
////////////////////////////////////////////////////////////////////////////////
void Thread::stop ()
	 throw ( Error )
{
	__BEGIN_TRY
		
	throw UnsupportedError();
		
	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// 특정 쓰레드가 종료할 때까지 현재 쓰레드를 멈춘다.
//
// 여기서 *현재* 쓰레드라는데 주의하라. 쓰레드 A 가 쓰레드 B 를 기다리는 것이
// 아니므로, 이 메쏘드는 static 이어야 한다. 
//
// 이때 status 는 어떤 데이타구조라도 가능하다. (structure, class...)
//
////////////////////////////////////////////////////////////////////////////////
void Thread::join ( const Thread & t )
     throw ( ThreadException , Error )
{ 
	__BEGIN_TRY

	pthread_join_ex ( t.getTID() , NULL );
	
	__END_CATCH
}

void Thread::join ( const Thread & t, void * status )
     throw ( ThreadException , Error )
{ 
	__BEGIN_TRY

	pthread_join_ex ( t.getTID() , &status );
	
	__END_CATCH
}

void Thread::join ( const Thread * t )
     throw ( ThreadException , Error )
{ 
	__BEGIN_TRY

	pthread_join_ex ( t->getTID() , NULL );
	
	__END_CATCH
}

void Thread::join ( const Thread * t, void * status )
     throw ( ThreadException , Error )
{ 
	__BEGIN_TRY

	pthread_join_ex ( t->getTID() , &status );
	
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
//
// 쓰레드를 Detached 모드로 바꾼다.
//
// 어떤 쓰레드가 detached 모드일 경우, 종료할 때 자동적으로 스택 등의 리소스를
// 반납하게 된다. 만약 아니라면 join()을 통해서 종료할 때까지 기다렸다가 리소스를
// 반납하게 해야 한다. 이렇게 될 경우 시스템의 퍼포먼스가 떨어지게 되므로, 대부분
// 의 쓰레드들에 있어서 이 메쏘드를 호출해주는 것이 좋을 것이다.
//
////////////////////////////////////////////////////////////////////////////////
void Thread::detach () 
     throw ( Error )
{
	__BEGIN_TRY

	pthread_detach_ex(m_TID);
	
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
//
// 현재 쓰레드를 종료시킨다.
//
// void pthread_exit ( void * retval );
//
// 필요하다면 어떤 데이타구조라도 리턴해서 join 하는 쓰레드로 넘길 수 있다.
// (그러나, 대부분의 쓰레드들이 detached 로 돌아간다면 NULL 을 리턴하는 것이
// 좋을 것이다.)
//
////////////////////////////////////////////////////////////////////////////////
void Thread::exit ( void * retval )
	 throw ()
{
	pthread_exit_ex( retval );
}


////////////////////////////////////////////////////////////////////////////////
//
// thread's start routine
//
// Thread 클래스의 friend method 이다.
//
// REENTRANT function 이면 내가 보기엔 안전할 듯 한데.. 태수는 thread 객체를
// thread specific data 로 만들었단 말씀이야. 호홋. 쓰레드 스택 안에서 실행되면 
// 완벽하게 다른 게 되지 않나? 
//
// 하위 클래스의 run()을 virtual로 호출하기 전후에, 쓰레드의 상태를 RUNNING,
// EXIT로 바꾸는데 주의하라. 일단 EXIT로 바뀌면, 쓰레드는 더이상 재시작될 수 없다.
//
////////////////////////////////////////////////////////////////////////////////
void * start_routine ( void * derivedThread )
	   throw ()
{
	Thread * thread = (Thread *)derivedThread;
	
	// set thread's status to "RUNNING"
	thread->setStatus(Thread::RUNNING);

	// here - polymorphism used. (derived::run() called.)
	thread->run();
	
	// set thread's status to "EXIT"
	thread->setStatus(Thread::EXIT);

	Thread::exit(NULL);

	return NULL;	// avoid compiler's warning
}


////////////////////////////////////////////////////////////////////////////////
//
// 현재 쓰레드의 TID 를 알아낸다. static 멤버함수이다.
//
////////////////////////////////////////////////////////////////////////////////
TID Thread::self ()
	 throw ()
{
	return pthread_self_ex();
}


////////////////////////////////////////////////////////////////////////////////
//
// return thread information string
//
////////////////////////////////////////////////////////////////////////////////
string Thread::toString () const
       throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "Thread[" << (uint)m_TID<< "]" ;
	return msg.toString();
	
	__END_CATCH
}
