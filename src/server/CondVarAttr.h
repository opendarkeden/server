//////////////////////////////////////////////////////////////////////
//
// CondVarAttr.h
//
// by Reiot
//
//////////////////////////////////////////////////////////////////////

#ifndef __COND_VAR_ATTR_H__
#define __COND_VAR_ATTR_H__

#include <pthread.h>
#include "pthreadAPI.h"

class CondVarAttr {
public:
    CondVarAttr() throw() { pthreadAPI::pthread_condattr_init_ex(&m_Attr); }
    ~CondVarAttr() throw() { pthreadAPI::pthread_condattr_destroy_ex(&m_Attr); }

    pthread_condattr_t * getAttr() throw() { return &m_Attr; }

private:
    pthread_condattr_t m_Attr;
};

#endif
