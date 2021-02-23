/////////////////////////////////////////////////////////////////////////////
// Filename : MPlayerManager.h
// Desc		:
/////////////////////////////////////////////////////////////////////////////

#ifndef __MPLAYER_MANAGER_H__
#define __MPLAYER_MANAGER_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Thread.h"
#include "Socket.h"
#include "Mutex.h"
#include "MJob.h"

#include <deque>


/////////////////////////////////////////////////////////////////////////////
// class MPlayerManager
/////////////////////////////////////////////////////////////////////////////
class MPlayerManager : public Thread
{
public:
	// typedefinition for MJob
	typedef deque<MJob*>				DequeMJob;
	typedef DequeMJob::iterator			DequeMJobItr;
	typedef DequeMJob::const_iterator	DequeMJobConstItor;

public:
	MPlayerManager() throw(Error);
	~MPlayerManager() throw(Error);

public:
	void init() throw(Error) {}
	void stop() throw(Error);
	void run() throw();

public:
	void addJob( const string& userID, const string& name, const string& cellnum );

	void processResult();

private:
	MJob* popJob();

private:
	DequeMJob		m_Jobs;
	MJob*			m_pCurrentJob;
	mutable Mutex	m_Mutex;
};

// global variable declaration
extern MPlayerManager* g_pMPlayerManager;

#endif

