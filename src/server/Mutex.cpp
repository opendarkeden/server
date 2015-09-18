//////////////////////////////////////////////////////////////////////////////
// Filename    : Mutex.cpp
// Written By  : reiot@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "Mutex.h"
#include "MutexAttr.h"
#include "pthreadAPI.h"
#include "Thread.h"
//#include "LogClient.h"
#include "StringStream.h"


Mutex::Mutex(MutexAttr * attr) throw(Error) {
    __BEGIN_TRY

    pthreadAPI::pthread_mutex_init_ex(&m_Mutex, (attr == NULL ? NULL : attr->getAttr()));
    m_LockTID = TID(-1);

    __END_CATCH
}


Mutex::~Mutex() throw(Error) {
    __BEGIN_TRY

    try {
        pthreadAPI::pthread_mutex_destroy_ex(&m_Mutex);
    } catch (MutexException & me) {
        cerr << me.toString() << endl;
        throw Error(me.toString());
    }

    __END_CATCH
}


void Mutex::lock() throw(Error) {
    __BEGIN_TRY

    try {
        TID tid = Thread::self();

        if (tid != m_LockTID) {
            pthreadAPI::pthread_mutex_lock_ex(&m_Mutex);
            m_LockTID = tid;
        } else {
            cerr << "Mutex::lock() : SELF DEAD LOCK [" << m_Name << "]" << endl;
            filelog("MutexError.log", "Mutex::lock() : SELF DEAD LOCK [%s]", m_Name.c_str());
            throw Error("Mutex::lock() : SELF DEAD LOCK");
        }
    } catch (MutexException & me) {
        cerr << me.toString() << endl;
        throw Error(me.toString());
    }

    __END_CATCH
}


void Mutex::trylock() throw(Error) {
    __BEGIN_TRY

    try {
        TID tid = Thread::self();

        if (tid != m_LockTID) {
            pthreadAPI::pthread_mutex_trylock_ex(&m_Mutex);
            m_LockTID = tid;
        } else {
            cerr << "Mutex::trylock() : SELF DEAD LOCK [" << m_Name << "]" << endl;
            filelog("MutexError.log", "Mutex::trylock() : SELF DEAD LOCK [%s]", m_Name.c_str());
            throw Error("Mutex::trylock() : SELF DEAD LOCK");
        }
    } catch (MutexException & me) {
        cerr << me.toString() << endl;
        throw Error(me.toString());
    }

    __END_CATCH
}


void Mutex::unlock() throw(Error) {
    __BEGIN_TRY

    try {
        pthreadAPI::pthread_mutex_unlock_ex(&m_Mutex);
        m_LockTID = TID(-1);
    } catch (MutexException & me) {
        cerr << me.toString() << endl;
        throw Error(me.toString());
    }

    __END_CATCH
}
