//////////////////////////////////////////////////////////////////////////////
// Filename    : Mutex.cpp
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Mutex.h"
#include "MutexAttr.h"
#include "pthreadAPI.h"
#include "Thread.h"
#include "LogClient.h"
#include "StringStream.h"

////////////////////////////////////////////////////////////////////////////////
//
// constructor
//
////////////////////////////////////////////////////////////////////////////////

Mutex::Mutex ( MutexAttr * attr ) 
	 throw ( Error )
{
	__BEGIN_TRY

	pthreadAPI::pthread_mutex_init_ex( &m_Mutex , ( attr == NULL ? NULL : attr->getAttr() ) );
	m_LockTID = -1;
	
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
//
// destructor
//
////////////////////////////////////////////////////////////////////////////////

Mutex::~Mutex () 
    throw ( Error )
{
	__BEGIN_TRY

	try 
	{
		pthreadAPI::pthread_mutex_destroy_ex( &m_Mutex );
	} 
	catch ( MutexException & me ) 
	{
		cerr << me.toString() << endl;
		throw Error(me.toString());
	}
	
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
//
// lock mutex
//
////////////////////////////////////////////////////////////////////////////////
void Mutex::lock () 
     throw ( Error )
{
	__BEGIN_TRY

	//filelog("lock.txt", "Thread[%d][%s] waiting lock", Thread::self(), m_Name.c_str());

	try 
	{
		int TID = Thread::self();

		if (TID != m_LockTID)
		{
			pthreadAPI::pthread_mutex_lock_ex( &m_Mutex );
			m_LockTID = TID;
		}
		else
		{
			cerr << "Mutex::lock() : SELF DEAD LOCK [" << m_Name << "]" << endl;
			filelog("MutexError.log", "Mutex::lock() : SELF DEAD LOCK [%s]", m_Name.c_str());
			throw Error("Mutex::lock() : SELF DEAD LOCK");
		}
	} 
	catch ( MutexException & me ) 
	{
		cerr << me.toString() << endl;
		throw Error(me.toString());
	}

	//filelog("lock.txt", "Thread[%d][%s] gain lock", Thread::self(), m_Name.c_str());

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
//
// if mutex is locked, throw MutexException. else lock mutex
//
////////////////////////////////////////////////////////////////////////////////
void Mutex::trylock () 
     throw ( Error )
{
	__BEGIN_TRY

	//filelog("lock.txt", "Thread[%d][%s] trying to gain lock", Thread::self(), m_Name.c_str());

	try 
	{
		int TID = Thread::self();

		if (TID != m_LockTID)
		{
			pthreadAPI::pthread_mutex_trylock_ex( &m_Mutex );
			m_LockTID = TID;
		}
		else
		{
			cerr << "Mutex::trylock() : SELF DEAD LOCK [" << m_Name << "]" << endl;
			filelog("MutexError.log", "Mutex::trylock() : SELF DEAD LOCK [%s]", m_Name.c_str());
			throw Error("Mutex::trylock() : SELF DEAD LOCK");
		}
	} 
	catch ( MutexException & me ) 
	{
		cerr << me.toString() << endl;
		throw Error(me.toString());
	}

	//filelog("lock.txt", "Thread[%d][%s] gain lock", Thread::self(), m_Name.c_str());

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
//
// unlock mutex
//
////////////////////////////////////////////////////////////////////////////////
void Mutex::unlock () 
     throw ( Error )
{
	__BEGIN_TRY

	try 
	{
		pthreadAPI::pthread_mutex_unlock_ex( &m_Mutex );
		m_LockTID = -1;
	}
	catch ( MutexException & me ) 
	{
		cerr << me.toString() << endl;
		throw Error(me.toString());
	}

	//filelog("lock.txt", "Thread[%d][%s] release lock", Thread::self(), m_Name.c_str());

	__END_CATCH
}
