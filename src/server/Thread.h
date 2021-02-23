//////////////////////////////////////////////////////////////////////
//
// Thread.h
//
// by Reiot
//
//////////////////////////////////////////////////////////////////////
//
// POSIX Thread Class 
//
// 만일 어떤 루틴을 쓰레드로 돌리려면, 일단 Thread 클래스를 상속
// 받아 derived 클래스를 설계, run() 멤버함수만 재정의한 후, 
// derived 클래스의 객체를 생성해서 Start() 함수를 실행하면 된다.
//
// 사용방법은 다음과 같다.
//
// MDerivedThread * dt = new DerivedThread (...);
// dt->Start();
// delete dt;
//
// virtual destructor 가 정의된 이유는, 다음과 같은 상황에서 제대로
// 동작하게 하기 위해서이다. ( 만일 정의하지 않으면 하위 클래스의
// destructor 는 호출되지 않는다. )
//
// Thread * t = new DerivedThread (...);
// t->Start();
// delete t;
//
// 단 쓰레드 객체를 삭제하는 것과 쓰레드를 종료시키는 것은 무관하다.
//
//////////////////////////////////////////////////////////////////////


#ifndef __THREAD_H__
#define __THREAD_H__


//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////

#include "Types.h"
#include "Exception.h"
#include "pthreadAPI.h"


//////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////
class ThreadAttr;
class ThreadException;


//////////////////////////////////////////////////////////////////////
//
// class Thread
//
// POSIX Thread Class
//
//////////////////////////////////////////////////////////////////////

class Thread {

//////////////////////////////////////////////////
// constants
//////////////////////////////////////////////////
public :
	
	enum ThreadStatus {
		READY ,		// run 할 준비가 되어 있는 상태
		RUNNING ,	// 실제로 running 중인 상태
		EXITING ,	// 종료 직전 상태 (실제로 처리는 하고 있는 중임)
		EXIT		// 완전히 종료한 상태 
	};
	

//////////////////////////////////////////////////
// constructor and destructor
//////////////////////////////////////////////////

public :

	// constructor
	Thread ( ThreadAttr * attr = NULL ) throw ();

	// destructor
	virtual ~Thread () throw ();


//////////////////////////////////////////////////
// public methods
//////////////////////////////////////////////////

public :

	// 쓰레드가 최초로 동작하도록 해주는 trigger 의 역할을 하는 함수. 쓰레드 
	// 객체를 생성한 후에, 이 함수를 호출하면 내부적으로 derived 클래스의 
	// run() 멤버함수를 호출하게 된다. 
	void start () throw ( ThreadException , Error );
	
	// 동작중인 쓰레드를 중단시킨다.
	// 내부에 뮤텍스를 사용하는 하위 쓰레드 클래스에서만 가능하다.
	virtual void stop () throw ( Error );

	// 쓰레드가 종료할 때까지 기다린다. 역시 쓰레드간에 사용된다. 보통은 
	// 쓰레드를 새로 생성시켜 특정 작업을 시킨 후 그 처리가 완료될 때까지
	// 생성시킨 쓰레드를 잠재우는 과정에서 사용된다. 멀티프로세싱 환경
	// 에서의 join 과 같은 역할을 한다.
	// 
	// 주의할 점은 pthread_join() 은 현재 이 코드를 실행하는 쓰레드가 
	// 파라미터로 지정받은 쓰레드를 기다린다는 것이다. 즉, 특정 쓰레드가
	// 또다른 특정 쓰레드를 기다리게 할 수는 없다.
	//
	// ex> Thread t;
	//     Thread::Join ( t );
	static void join ( const Thread & t ) throw ( ThreadException , Error );
	static void join ( const Thread * t ) throw ( ThreadException , Error );
	static void join ( const Thread & t , void * retval ) throw ( ThreadException , Error );
	static void join ( const Thread * t , void * retval ) throw ( ThreadException , Error );

	// 쓰레드를 Detached 모드로 바꾼다.
	void detach () throw ( Error );

	// 현재 쓰레드들 종료한다. 즉 특정 쓰레드를 종료시킨다는 말이 아니라,
	// 이 메쏘드를 수행하는 쓰레드를 종료시킨다는 말이다. 이때, 특정
	// 객체를 파라미터로 넘겨줌으로써 JOIN 하는 쓰레드가 그 값을 받아낼
	// 수도 있다.
	//
	// ex> Thread::Exit();
	//     or
	//     Thread::Exit(retval);
	static void exit ( void * retval = NULL ) throw ();

	// 쓰레드에서 독립적으로 실행되는 코드가 들어가는 부분이다. Thread 
	// 클래스를 상속받은 하위 클래스는 항상 이 함수를 재정의해줘야 한다.
	virtual void run () throw () {};


//////////////////////////////////////////////////
// 
//////////////////////////////////////////////////
public :

	// get current thread's tid
	static TID self () throw ();

	// 디버깅용이다. 쓰레드에 대한 정보를 string 의 형태로 반환한다.
	virtual string toString () const throw ();

	// get thread identifier
	TID getTID () const throw () { return m_TID; }
	
	// get/set thread's status
	ThreadStatus getStatus () const throw () { return m_Status; }
	void setStatus ( ThreadStatus status ) throw () { m_Status = status; }
	
	// get thread name
	virtual string getName () const throw () { return "Thread"; }
	

//////////////////////////////////////////////////
// data members
//////////////////////////////////////////////////

private :

	// thread identifier variable
	TID m_TID;
	
	// thread-attribute object
	ThreadAttr * m_ThreadAttr;
	
	// thread status
	ThreadStatus m_Status;

};


//////////////////////////////////////////////////
// thread function used at pthread_create()
//////////////////////////////////////////////////
void * start_routine ( void * derivedThread ) throw ();

#endif
