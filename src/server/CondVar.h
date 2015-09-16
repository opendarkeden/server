//////////////////////////////////////////////////////////////////////
// 
// CondVar.h 
// 
// by Reiot
// 
//////////////////////////////////////////////////////////////////////
//
// represents Conditional Variable (Thread Synchronization Primitive )
//
//////////////////////////////////////////////////////////////////////

#ifndef __COND_VAR_H__
#define __COND_VAR_H__

#include "CondVarAttr.h"
#include "Exception.h"
#include "Mutex.h"
#include "pthreadAPI.h"

class CondVar {
public:
    CondVar(CondVarAttr * attr = NULL) throw(Error);
    virtual ~CondVar() throw(CondVarException, Error);

    // wake up a waiting thread
    void signal() throw(Error);

    // waiting until somebody wake me up
    void wait(Mutex & mutex) throw(Error);

    //
    // waiting until somebody wake me up or specified time elapsed
    //
    // *NOTES* 
    // CondVarException means Timeout
    //
    void timedwait(Mutex & mutex, const struct timespec * timeout) throw(CondVarException, InterruptedException, Error);

    // wake up all waiting threads
    void broadcast() throw(Error);

    pthread_cond_t * getCondVar() throw() { return &m_Cond; }

private:
    pthread_cond_t m_Cond;    
};

#endif
