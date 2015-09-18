//////////////////////////////////////////////////////////////////////
// 
// CondVar.cpp 
// 
// by Reiot
// 
//////////////////////////////////////////////////////////////////////

#include "CondVar.h"
#include "Thread.h"
//#include "LogClient.h"
#include "StringStream.h"


CondVar::CondVar(CondVarAttr * attr) throw(Error) { //: m_Cond(PTHREAD_COND_INITIALIZER)
    __BEGIN_TRY

    pthreadAPI::pthread_cond_init_ex(&m_Cond, (attr == NULL ? NULL : attr->getAttr()));
    //log(LOG_DEBUG_MSG, "", "", "CondVar object created.");

    __END_CATCH
}


CondVar::~CondVar() throw(CondVarException, Error) {
    __BEGIN_TRY

    pthreadAPI::pthread_cond_destroy_ex(&m_Cond);
    //log(LOG_DEBUG_MSG, "", "", "CondVar object destroyed.");

    __END_CATCH
}


void CondVar::signal() throw(Error) {
    __BEGIN_TRY

    //StringStream msg;
    //msg << "Thread[" << Thread::self() << "] signal conditional variable.";
    //log(LOG_DEBUG_MSG, "", "", msg.toString());

    pthreadAPI::pthread_cond_signal_ex(&m_Cond);

    __END_CATCH
}


void CondVar::wait(Mutex & mutex) throw(Error) {
    __BEGIN_TRY

    //StringStream msg;
    //msg << "Thread[" << Thread::self() << "] waiting signal.";
    //log(LOG_DEBUG_MSG, "", "", msg.toString());

    pthreadAPI::pthread_cond_wait_ex(&m_Cond , mutex.getMutex());

    __END_CATCH
}


void CondVar::timedwait(Mutex & mutex, const struct timespec * timeout) throw(CondVarException, InterruptedException, Error) {
    __BEGIN_TRY

    //StringStream msg1, msg2;

    //msg1 << "Thread[" << Thread::self() << "] release lock (automatically).";
    //msg2 << "Thread[" << Thread::self() << "] gain lock (automatically).";

    //log(LOG_DEBUG_MSG, "", "", msg1.toString());
    pthreadAPI::pthread_cond_timedwait_ex(&m_Cond, mutex.getMutex(), timeout);
    //log(LOG_DEBUG_MSG, "", "", msg2.toString());

    __END_CATCH
}


void CondVar::broadcast() throw(Error) {
    __BEGIN_TRY

    pthreadAPI::pthread_cond_broadcast_ex(&m_Cond);

    __END_CATCH
}
