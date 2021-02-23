//////////////////////////////////////////////////////////////////////////////
// Filename    : Mutex.h
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __MUTEX_H__
#define __MUTEX_H__

#include <pthread.h>
#include "Types.h"
#include "Exception.h"

// forward declaration
class MutexAttr;

//////////////////////////////////////////////////////////////////////////////
// class Mutex;
//////////////////////////////////////////////////////////////////////////////

class Mutex 
{
public:
	Mutex ( MutexAttr * attr = NULL ) throw ( Error );
	virtual ~Mutex () throw ( Error );

public:
	string getName(void) const { return m_Name; }
	void setName(string name) { m_Name = name; }

	void lock () throw ( Error );
	void unlock () throw ( Error );
	void trylock () throw ( Error );
	
	pthread_mutex_t * getMutex () throw () { return &m_Mutex; }

private:
	pthread_mutex_t 	m_Mutex; 		// 뮤텍스 객체
	string 				m_Name; 		// 이 뮤텍스를 소유한 클래스 이름
	int 				m_LockTID;		// 현재 락을 건 놈의 precoess id
};

#endif
