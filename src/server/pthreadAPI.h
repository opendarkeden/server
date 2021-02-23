//////////////////////////////////////////////////////////////////////
//
// pthreadAPI.h
//
// by Reiot
//
//////////////////////////////////////////////////////////////////////

#ifndef __PTHREAD_API_H__
#define __PTHREAD_API_H__

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////
#include <pthread.h>
#include "Exception.h"


//////////////////////////////////////////////////
// type redefinition
//////////////////////////////////////////////////
typedef pthread_t TID;


namespace pthreadAPI {
	
//
// exception version of pthread_create()
//
void pthread_create_ex ( pthread_t * thread , pthread_attr_t * attr , void * (*start_routine)(void *), void * arg ) 
	throw ( ThreadException , Error );

//
// exception version of pthread_join()
//
void pthread_join_ex ( pthread_t th , void ** thread_return ) 
	throw ( ThreadException , Error );

//
// exception version of pthread_detach()
//
void pthread_detach_ex ( pthread_t th ) 
	throw ( Error );

//
// exception version of pthread_attr_exit()
//
void pthread_exit_ex ( void * retval ) 
	throw ();

//
// exception version of pthread_self()
//
pthread_t pthread_self_ex ()
	      throw ();

//
// exception version of pthread_attr_init()
//
void pthread_attr_init_ex ( pthread_attr_t * attr ) 
	throw ( Error );

//
// exception version of pthread_attr_destroy()
//
void pthread_attr_destroy_ex ( pthread_attr_t * attr ) 
	throw ( Error );
			  
//
// exception version of pthread_attr_setgetachstate()
//
void pthread_attr_getdetachstate_ex ( const pthread_attr_t * attr , int * detachstate ) 
	throw ( Error );
					 
//
// exception version of pthread_attr_setdetachstate()
//
void pthread_attr_setdetachstate_ex ( pthread_attr_t * attr , int detachstate ) 
	throw ( Error );

/*
void pthreadAPI::pthread_attr_setschedpolicy_ex (pthread_attr_t *attr, int policy);
void pthreadAPI::pthread_attr_getschedpolicy_ex (const pthread_attr_t *attr, int *policy);
void pthreadAPI::pthread_attr_setschedparam_ex (pthread_attr_t *attr, const struct sched_param *param);
void pthreadAPI::pthread_attr_getschedparam_ex (const pthread_attr_t *attr, struct sched_param *param);
void pthreadAPI::pthread_attr_setinheritsched_ex (pthread_attr_t *attr, int inherit);
void pthreadAPI::pthread_attr_getinheritsched_ex (const pthread_attr_t *attr, int *inherit);
void pthreadAPI::pthread_attr_setscope_ex (pthread_attr_t *attr, int scope);
void pthreadAPI::pthread_attr_getscope_ex (const pthread_attr_t *attr, int *scope);
*/

//
// exception version of pthread_mutex_init()
//
void pthread_mutex_init_ex ( pthread_mutex_t * mutex , const pthread_mutexattr_t * mutexattr) 
	throw ( Error );
						   
//
// exception version of pthread_mutex_destroy()
//
void pthread_mutex_destroy_ex ( pthread_mutex_t * mutex ) 
	throw ( MutexException , Error );

//
// exception version of pthread_mutex_lock()
//
void pthread_mutex_lock_ex (pthread_mutex_t *mutex) 
	throw ( MutexException , Error );
			 
//
// exception version of pthread_mutex_unlock()
//
void pthread_mutex_unlock_ex ( pthread_mutex_t * mutex ) 
	throw ( MutexException , Error );
							  
//
// exception version of pthread_mutex_trylock()
//
void pthread_mutex_trylock_ex ( pthread_mutex_t * mutex ) 
	throw ( MutexException , Error );

//
// exception version of pthread_mutexattr_init()
//
void pthread_mutexattr_init_ex ( pthread_mutexattr_t * attr ) 
	throw ( Error );
	   
//
// exception version of pthread_mutexattr_destroy()
//
void pthread_mutexattr_destroy_ex ( pthread_mutexattr_t * attr ) 
	throw ( Error );
			  
/*

//
//
// exception version of pthread_mutexattr_getkind()
//
void pthread_mutexattr_gettype_ex ( const pthread_mutexattr_t * attr , int * kind ) 
	throw ( Error );

//
// exception version of pthread_mutexattr_setkind()
//
void pthread_mutexattr_settype_ex ( pthread_mutexattr_t * attr , int kind ) 
	throw ( Error );

*/
					 
//
// exception version of pthread_cond_init()
//
void pthread_cond_init_ex ( pthread_cond_t * cond , pthread_condattr_t * cond_attr )
	 throw ( Error );

//
// exception version of pthread_cond_destroy()
//
void pthread_cond_destroy_ex ( pthread_cond_t * cond )
	 throw ( CondVarException , Error );

//
// exception version of pthread_cond_signal()
//
void pthread_cond_signal_ex ( pthread_cond_t * cond )
	 throw ( Error );

//
// exception version of pthread_cond_wait()
//
void pthread_cond_wait_ex ( pthread_cond_t * cond , pthread_mutex_t * mutex )
	 throw ( Error );

//
// exception version of pthread_cond_timedwait()
//
void pthread_cond_timedwait_ex ( pthread_cond_t * cond , pthread_mutex_t * mutex , const struct timespec * abstime )
	 throw ( CondVarException , InterruptedException , Error );

//
// exception version of pthread_cond_broadcast()
//
void pthread_cond_broadcast_ex ( pthread_cond_t * cond )
	 throw ( Error );

//
// exception version of pthread_condattr_init()
//
void pthread_condattr_init_ex ( pthread_condattr_t * attr )
	 throw ();

//
// exception version of pthread_condattr_destroy()
//
void pthread_condattr_destroy_ex ( pthread_condattr_t * attr )
	 throw ();

}//end of namespace pthreadAPI

#endif
