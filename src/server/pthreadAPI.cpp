//////////////////////////////////////////////////////////////////////
//
// pthreadAPI.cpp
//
// by Reiot, the Fallen Lord of MUDMANIA(TM)
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include "pthreadAPI.h"
#include <pthread.h>
#include <errno.h>

//////////////////////////////////////////////////
//////////////////////////////////////////////////
extern int errno;


//////////////////////////////////////////////////////////////////////
//
// exception version of pthread_create()
//
//////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_create_ex ( pthread_t * thread , pthread_attr_t * attr , void * (*start_routine)(void *), void * arg )
	throw ( ThreadException , Error )
{ 
	__BEGIN_TRY

	if ( pthread_create( thread , attr , start_routine , arg ) < 0 ) {
		switch ( errno ) {
			case EAGAIN :
				throw ThreadException("시스템 리소스가 부족하거나, 너무 많은 쓰레드가 활성화상태입니다.");
			default :
				throw UnknownError(strerror(errno),errno);
		}
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// exception version of pthread_join()
//
//////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_join_ex ( pthread_t th , void ** thread_return )
	 throw ( ThreadException , Error )
{ 
	__BEGIN_TRY

	if ( pthread_join ( th , thread_return ) < 0 ) {
		switch ( errno ) {
			case ESRCH :
				throw Error("지정된 쓰레드를 찾을 수 없습니다.");
			case EINVAL :
				throw ThreadException("지정된 쓰레드가 이미 detached 되었거나, 또다른 쓰레드가 이미 기다리고 있습니다.");
			case EDEADLK :
				throw Error("자기 자신을 기다릴 수는 없습니다.");
			default :
				throw UnknownError(strerror(errno),errno);
		}
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// exception version of pthread_detach()
//
//////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_detach_ex ( pthread_t th )
	throw ( Error )
{
	__BEGIN_TRY

	if ( pthread_detach(th) < 0 ) {
		switch ( errno ) {
			case ESRCH :
				throw Error("지정된 쓰레드를 찾을 수 없습니다.");
			case EINVAL :
				throw ThreadException("지정된 쓰레드는 이미 detached 상태입니다.");
			default :
				throw UnknownError(strerror(errno),errno);
		}
	}

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// exception version of pthread_exit()
//
//////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_exit_ex ( void * retval )
	 throw ()
{
	pthread_exit( retval );
}


//////////////////////////////////////////////////////////////////////
//
// exception version of pthread_self()
//
//////////////////////////////////////////////////////////////////////
pthread_t pthreadAPI::pthread_self_ex ()
	 throw ()
{
	return pthread_self();
}


//////////////////////////////////////////////////////////////////////
//
// exception version of pthread_attr_init()
//
//////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_attr_init_ex ( pthread_attr_t * attr )
	 throw ( Error )
{
	__BEGIN_TRY

	if ( pthread_attr_init( attr ) != 0 )
		throw UnknownError();

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////
//
// exception version of pthread_attr_destroy()
//
//////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_attr_destroy_ex ( pthread_attr_t * attr )
	 throw ( Error )
{
	__BEGIN_TRY

	if ( pthread_attr_destroy( attr ) != 0 )
		throw UnknownError();

	__END_CATCH
}

			  
//////////////////////////////////////////////////////////////////////
//
// exception version of pthread_getdetachstate()
//
//////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_attr_getdetachstate_ex ( const pthread_attr_t * attr , int * detachstate )
	 throw ( Error )
{
	__BEGIN_TRY

	if ( pthread_attr_getdetachstate( attr , detachstate ) != 0 )
		throw UnknownError();

	__END_CATCH
}

					 
//////////////////////////////////////////////////////////////////////
//
// exception version of pthread_setdetachstate()
//
//////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_attr_setdetachstate_ex ( pthread_attr_t * attr , int detachstate )
	 throw ( Error )
{
	__BEGIN_TRY

	if ( pthread_attr_setdetachstate( attr , detachstate ) < 0 ) {
		switch ( errno ) {
			case EINVAL :
				throw Error("invalid thread attribute state");
			default :
				throw UnknownError(strerror(errno),errno);
		}
	}

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
//
// exception version of pthread_mutex_init()
//
////////////////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_mutex_init_ex ( pthread_mutex_t * mutex , const pthread_mutexattr_t * mutexattr)
	throw ( Error )
{
	__BEGIN_TRY

	if ( pthread_mutex_init( mutex , mutexattr ) != 0 )
		throw UnknownError();

	__END_CATCH
}
						   

////////////////////////////////////////////////////////////////////////////////
//
// exception version of pthread_mutex_destroy()
//
////////////////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_mutex_destroy_ex ( pthread_mutex_t * mutex )
	throw ( MutexException , Error )
{
	__BEGIN_TRY

	if ( pthread_mutex_destroy( mutex ) < 0 ) {
		switch ( errno ) {
			case EBUSY :
				throw MutexException("뮤텍스가 현재 잠금상태입니다.");
			default :
				throw UnknownError(strerror(errno),errno);
		}
	}

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
//
// exception version of pthread_mutex_lock()
//
////////////////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_mutex_lock_ex (pthread_mutex_t *mutex)
	 throw ( MutexException , Error )
{
	__BEGIN_TRY

	if ( pthread_mutex_lock(mutex) < 0 ) {
		switch ( errno ) {
			case EINVAL :
				throw Error("뮤텍스가 올바르게 초기화되지 않았습니다.");
			case EDEADLK :
				throw MutexException("DEADLOCK - 뮤텍스가 현재 쓰레드에 의해서 이미 잠겨있습니다.");
			default :
				throw UnknownError(strerror(errno),errno);
		}
	}

	__END_CATCH
}

			 
////////////////////////////////////////////////////////////////////////////////
//
// exception version of pthread_mutex_unlock()
//
////////////////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_mutex_unlock_ex ( pthread_mutex_t * mutex )
	 throw ( MutexException , Error )
{
	__BEGIN_TRY

	if ( pthread_mutex_unlock ( mutex ) < 0 ) {
		switch ( errno ) {
			case EINVAL :
				throw Error("뮤텍스가 올바르게 초기화되지 않았습니다.");
			case EPERM :
				throw MutexException("현재 쓰레드가 뮤텍스를 잠그고 있지 않습니다.");
			default :
				throw UnknownError(strerror(errno),errno);
		}
	}

	__END_CATCH
}

							  
////////////////////////////////////////////////////////////////////////////////
//
// exception version of pthread_mutex_trylock()
//
////////////////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_mutex_trylock_ex ( pthread_mutex_t * mutex )
	 throw ( MutexException , Error )
{
	__BEGIN_TRY

	if ( pthread_mutex_trylock ( mutex ) < 0 ) {
		switch ( errno ) {
			case EINVAL :
				throw Error("뮤텍스가 올바르게 초기화되지 않았습니다.");
			case EBUSY :
				throw MutexException("mutex already locked...");
			default :
				throw UnknownError(strerror(errno),errno);
		}
	}

	__END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
//
// exception version of pthread_mutexattr_init()
//
////////////////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_mutexattr_init_ex ( pthread_mutexattr_t * attr )
    throw ( Error )
{
	__BEGIN_TRY

	if ( pthread_mutexattr_init( attr ) != 0 )
		throw UnknownError();

	__END_CATCH
}
	   

////////////////////////////////////////////////////////////////////////////////
//
// exception version of pthread_mutexattr_destroy()
//
////////////////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_mutexattr_destroy_ex ( pthread_mutexattr_t * attr )
    throw ( Error )
{
	__BEGIN_TRY

	if ( pthread_mutexattr_destroy( attr ) != 0 )
		throw UnknownError();

	__END_CATCH
}
			  

/*
////////////////////////////////////////////////////////////////////////////////
//
// exception version of pthread_mutexattr_gettype()
//
////////////////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_mutexattr_gettype_ex ( const pthread_mutexattr_t * attr , int * kind )
    throw ( Error )
{
	__BEGIN_TRY

	if ( pthread_mutexattr_gettype ( attr , kind ) < 0 ) 
		throw UnknownError();

	__END_CATCH
}

					 
////////////////////////////////////////////////////////////////////////////////
//
// exception version of pthread_mutexattr_settype()
//
////////////////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_mutexattr_settype_ex ( pthread_mutexattr_t * attr , int kind )
    throw ( Error )
{
	__BEGIN_TRY

	if ( pthread_mutexattr_settype ( attr , kind ) < 0 ) {
		switch ( errno ) {
			case EINVAL :
				throw Error("kind is neither PTHREAD_MUTEX_FAST_NP nor PTHREAD_MUTEX_RECURSIVE_NP nor PTHREAD_MUTEX_ERRORCHECK_NP");
			default :
				throw UnknownError(strerror(errno),errno);
		}
	}

	__END_CATCH
}
*/

////////////////////////////////////////////////////////////////////////////////
//
// exception version of pthread_cond_init()
//
////////////////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_cond_init_ex ( pthread_cond_t * cond , pthread_condattr_t * cond_attr )
     throw ( Error )
{
	__BEGIN_TRY

	if ( pthread_cond_init(cond,cond_attr) != 0 )
		throw UnknownError();

	__END_CATCH
}
		 

////////////////////////////////////////////////////////////////////////////////
//
// exception version of pthread_cond_destroy()
//
////////////////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_cond_destroy_ex ( pthread_cond_t * cond )
     throw ( CondVarException , Error )
{
	__BEGIN_TRY

	switch ( pthread_cond_destroy(cond) ) {
		case EBUSY :
			throw CondVarException("conditional variable is busy now.");
		default :
			throw UnknownError(strerror(errno),errno);
	}

	__END_CATCH
}
		 

////////////////////////////////////////////////////////////////////////////////
//
// exception version of pthread_cond_signal()
//
////////////////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_cond_signal_ex ( pthread_cond_t * cond )
     throw ( Error )
{
	__BEGIN_TRY

	if ( pthread_cond_signal(cond) != 0 )
		throw UnknownError();

	__END_CATCH
}
		 

////////////////////////////////////////////////////////////////////////////////
//
// exception version of pthread_cond_wait()
//
////////////////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_cond_wait_ex ( pthread_cond_t * cond , pthread_mutex_t * mutex )
     throw ( Error )
{
	__BEGIN_TRY

	if ( pthread_cond_wait(cond,mutex) != 0 )
		throw UnknownError();

	__END_CATCH
}
		 

////////////////////////////////////////////////////////////////////////////////
//
// exception version of pthread_cond_timedwait()
//
////////////////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_cond_timedwait_ex ( pthread_cond_t * cond , pthread_mutex_t * mutex , const struct timespec * abstime )
     throw ( CondVarException , InterruptedException , Error )
{
	__BEGIN_TRY
		
	switch ( pthread_cond_timedwait(cond,mutex,abstime) ) {
		case 0 :
			break;
		case ETIMEDOUT :
			throw CondVarException("timeout");
		case EINTR :
			throw InterruptedException();
		default :
			throw UnknownError(strerror(errno),errno);
	}
	
	__END_CATCH
}
		 

////////////////////////////////////////////////////////////////////////////////
//
// exception version of pthread_cond_broadcast()
//
////////////////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_cond_broadcast_ex ( pthread_cond_t * cond )
     throw ( Error )
{
	__BEGIN_TRY

	if ( pthread_cond_broadcast(cond) != 0 )
		throw UnknownError();
	
	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
//
// exception version of pthread_condattr_init_ex ()
//
////////////////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_condattr_init_ex ( pthread_condattr_t * attr )
	 throw ()
{
	__BEGIN_TRY
		
	pthread_condattr_init(attr);

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
//
// exception version of pthread_condattr_destroy_ex()
//
////////////////////////////////////////////////////////////////////////////////
void pthreadAPI::pthread_condattr_destroy_ex ( pthread_condattr_t * attr )
	 throw ()
{
	__BEGIN_TRY
		
	pthread_condattr_destroy(attr);

	__END_CATCH
}
