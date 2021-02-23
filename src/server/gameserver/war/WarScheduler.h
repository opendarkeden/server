///////////////////////////////////////////////////////////////////
// WarScheduler.h
//
// Zone에 붙어서 돌아간다.
///////////////////////////////////////////////////////////////////

#ifndef __WAR_SCHEDULER_H__
#define __WAR_SCHEDULER_H__

#include "Types.h"
#include "Work.h"
#include "Scheduler.h"
#include "War.h"
#include "Mutex.h"

const int MaxWarSchedule = 10;

class Zone;
class GCWarScheduleList;

class WarScheduler : public Scheduler
{

public:
	WarScheduler( Zone* pZone ) throw (Error);
	virtual ~WarScheduler() throw (Error);

public:
	void load() throw(Error);
	void tinysave( WarID_t warID, const string& query ) throw(Error);

	bool addWar( War* pWar ) throw(Error);
	bool canAddWar( WarType_t warType ) throw(Error);

	Zone* getZone() const { return m_pZone; }

	void	cancelGuildSchedules() throw (Error);
	bool	hasSchedule( GuildID_t gID ) throw(Error);

	int 	getWarTypeCount(WarType_t warType) throw(Error);

	virtual Work* heartbeat() throw(Error);

protected :
	VSDateTime	 			getLastWarDateTime( WarType_t warType ) const;
	VSDateTime 				getNextWarDateTime( WarType_t warType ) const;

public :
	static VSDateTime 		getNextWarDateTime( WarType_t warType, const VSDateTime& dt );
	bool 	makeGCWarScheduleList(GCWarScheduleList* pGCWarScheduleList) const throw (Error);


public :
	void	lock() throw (Error)		{ m_Mutex.lock(); }
	void	unlock() throw (Error)		{ m_Mutex.unlock(); }

private:
	Zone*	m_pZone;

	mutable Mutex	m_Mutex;
};

#endif // __WAR_SCHEDULER_H__
