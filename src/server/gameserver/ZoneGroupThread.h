//////////////////////////////////////////////////////////////////////
//
// Filename    : ZoneGroupThread.h
// Written by  : reiot@ewestsoft.com
// Description : 
//
//////////////////////////////////////////////////////////////////////

#ifndef __ZONE_THREAD_H__
#define __ZONE_THREAD_H__

// include files
#include "Types.h"
#include "Exception.h"
#include "Thread.h"
#include "ZoneGroup.h"

//////////////////////////////////////////////////////////////////////
//
// class ZoneGroupThread;
//
// 하나의 존그룹(ZoneGroup)을 맡아서 관리하는 쓰레드로서, 존그룹에 
// 종속된 PC, 존에 소속된 NPC와 MOB, 존의 각종 처리.. 등을 전담한다.
// 즉 존그룹에서는 순차 처리가 이루어지게 된다.
//
//////////////////////////////////////////////////////////////////////

class ZoneGroupThread : public Thread {

public:

	// constructor
	ZoneGroupThread(ZoneGroup* pZoneGroup) throw();

	// destructor
	~ZoneGroupThread() throw();

	// main method
	void run() throw();

	// get debug string
	string toString() const throw();

	// get thread's name
	string getName() const throw() { return "ZoneGroupThread"; }

	ZoneGroup* getZoneGroup(){ return m_pZoneGroup; }

private:

	ZoneGroup* m_pZoneGroup;
};

#endif
