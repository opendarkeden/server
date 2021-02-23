//////////////////////////////////////////////////////////////////////
//
// ThreadAttr.h
//
// by Reiot
//
//////////////////////////////////////////////////////////////////////

#ifndef __THREAD_ATTR_H__
#define __THREAD_ATTR_H__

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include <pthread.h>
#include "Types.h"
#include "Exception.h"


//////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////
class ThreadAttrException;


//////////////////////////////////////////////////////////////////////
//
// class ThreadAttr;
//
// Thread-Attribute 클래스는 동일한 속성(attribute)의 Thread 클래스를 
// 여러 개 생성할 필요가 있을 때 pthread_create()의 파라미터로 사용된다. 
// 즉 하나의 Thread-Attribute 객체만 생성해놓으면 된다는 뜻이다.
// (솔라리스 쓰레드에 있어서 생성할때마다 thread-flag 를 지정했던
// 기억을 되살려 보라~)
//
// 그런데, 실제로는 잘 쓰이지 않을 듯 하다. 왜냐하면 가장 유용하게
// 사용될 setstacksize()가 제공되지 않으며, detach 는 pthread_detach()
// 로도 충분하기 때문이다.
//
//////////////////////////////////////////////////////////////////////

class ThreadAttr {

//////////////////////////////////////////////////
// constructor / destructor
//////////////////////////////////////////////////
public :
	
	// constructor
	ThreadAttr () throw ( Error );

	// destructor
	~ThreadAttr () throw ( Error );
	

//////////////////////////////////////////////////
// public methods
//////////////////////////////////////////////////
public :
	
	//
	// return thread-attribute object
	//
	// *CAUTION* 
	//
	// do not return pthread_attr_t value !!
	// use pthread_attr_t pointer instead.
	// (pthread_attr_t 에 대해 assignment 가 지원되지 않을 가능성 있음)
	//
	pthread_attr_t * getAttr () throw () { return &attr; }

	// is thread attribute detached state?
	bool isDetached () const throw ( Error ) { return getDetachState() == PTHREAD_CREATE_DETACHED; }
	
	// set thread attribute detached state
	void setDetached () throw ( Error ) { setDetachState(PTHREAD_CREATE_DETACHED); }

	// is thread attribute joinable state?
	bool isJoinable () const throw ( Error ) { return getDetachState() == PTHREAD_CREATE_JOINABLE; }
	
	// set thread attribute joinable state
	void setJoinable () throw ( Error ) { setDetachState(PTHREAD_CREATE_JOINABLE); }


//////////////////////////////////////////////////
// protected methods
//////////////////////////////////////////////////

protected :

	// get thread attribute's state
	int getDetachState () const throw ( Error );

	// set thread attribute's state
	void setDetachState ( int state ) throw ( Error );


//////////////////////////////////////////////////
// attributes
//////////////////////////////////////////////////

private :
	
	// thread attribute
	pthread_attr_t attr;

};

#endif
