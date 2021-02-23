//////////////////////////////////////////////////////////////////////
//
// MutexAttr.h
//
// by Reiot
//
//////////////////////////////////////////////////////////////////////
//
// Mutex-Attribute Class
//
// Mutex-Attribute 클래스는 동일한 속성(attribute)의 Mutex 클래스를 
// 여러 개 생성할 필요가 있을 때 pthread_mutex_init()의 파라미터로 
// 사용된다. 즉 하나의 Mutex-Attribute 객체만 생성해놓으면 된다는 
// 뜻이다.
//
//////////////////////////////////////////////////////////////////////


#ifndef __MUTEX_ATTR_H__
#define __MUTEX_ATTR_H__

//////////////////////////////////////////////////
// include
//////////////////////////////////////////////////
#include <pthread.h>
#include "Types.h"
#include "pthreadAPI.h"
#include "Exception.h"


//////////////////////////////////////////////////
// forward declaration
//////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
//
// class MutexAttr;
//
//////////////////////////////////////////////////////////////////////

class MutexAttr {

//////////////////////////////////////////////////
// constructor / destructor
//////////////////////////////////////////////////

public :
	
	// constructor
	MutexAttr () throw ( Error ) { pthread_mutexattr_init( &m_Attr ); }

	// destructor
	~MutexAttr () throw ( Error ) { pthread_mutexattr_destroy( &m_Attr ); }
	

//////////////////////////////////////////////////
// public methods
//////////////////////////////////////////////////

public :

	//
	// return mutex-attribute object
	//
	// *CAUTION* 
	//
	// do not return pthread_mutexattr_t value !!
	// use pthread_mutexattr_t pointer instead.
	// (pthread_mutexattr_t 에 대해 assignment 가 지원되지 않을 
	// 가능성 있음)
	//
	pthread_mutexattr_t * getAttr () throw () { return &m_Attr; }
	
	/*
	bool isFastMutex () const throw ( MutexAttrException ) { return getMutexKind() == PTHREAD_MUTEX_FAST_NP; }
	bool isRecursiveMutex () const throw ( MutexAttrException ) { return getMutexKind() == PTHREAD_MUTEX_RECURSIVE_NP; }
	bool isErrorCheckMutex () const throw ( MutexAttrException ) { return getMutexKind() == PTHREAD_MUTEX_ERRORCHECK_NP; }
	
	void setFastMutex () throw ( MutexAttrException ) { setMutexKind( PTHREAD_MUTEX_FAST_NP ); }
	void setRecursiveMutex () throw ( MutexAttrException ) { setMutexKind( PTHREAD_MUTEX_RECURSIVE_NP ); }
	void setErrorCheckMutex () throw ( MutexAttrException ) { setMutexKind( PTHREAD_MUTEX_ERRORCHECK_NP ); }

	// get mutex kind
	int getMutexKind () const throw ( MutexAttrException );

	// set mutex kind
	void setMutexKind ( int Kind ) throw ( MutexAttrException );
	*/


//////////////////////////////////////////////////
// attributes
//////////////////////////////////////////////////

private :
	
	// mutex attribute
	pthread_mutexattr_t m_Attr;

};

#endif
