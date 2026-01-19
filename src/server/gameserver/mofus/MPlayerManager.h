/////////////////////////////////////////////////////////////////////////////
// Filename : MPlayerManager.h
// Desc		:
/////////////////////////////////////////////////////////////////////////////

#ifndef __MPLAYER_MANAGER_H__
#define __MPLAYER_MANAGER_H__

// include files
#include <deque>

#include "Exception.h"
#include "MJob.h"
#include "Mutex.h"
#include "Socket.h"
#include "Thread.h"
#include "Types.h"


/////////////////////////////////////////////////////////////////////////////
// class MPlayerManager
/////////////////////////////////////////////////////////////////////////////
class MPlayerManager : public Thread {
public:
    // typedefinition for MJob
    typedef deque<MJob*> DequeMJob;
    typedef DequeMJob::iterator DequeMJobItr;
    typedef DequeMJob::const_iterator DequeMJobConstItor;

public:
    MPlayerManager();
    ~MPlayerManager();

public:
    void init() {}
    void stop();
    void run();

public:
    void addJob(const string& userID, const string& name, const string& cellnum);

    void processResult();

private:
    MJob* popJob();

private:
    DequeMJob m_Jobs;
    MJob* m_pCurrentJob;
    mutable Mutex m_Mutex;
};

// global variable declaration
extern MPlayerManager* g_pMPlayerManager;

#endif
