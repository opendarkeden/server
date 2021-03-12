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
	WarScheduler( Zone* pZone ) ;
	virtual ~WarScheduler() ;

public:
	void load() ;
	void tinysave( WarID_t warID, const string& query ) ;

	bool addWar( War* pWar ) ;
	bool canAddWar( WarType_t warType ) ;

	Zone* getZone() const { return m_pZone; }

	void	cancelGuildSchedules() ;
	bool	hasSchedule( GuildID_t gID ) ;

	int 	getWarTypeCount(WarType_t warType) ;

	virtual Work* heartbeat() ;

protected :
	VSDateTime	 			getLastWarDateTime( WarType_t warType ) const;
	VSDateTime 				getNextWarDateTime( WarType_t warType ) const;

public :
	static VSDateTime 		getNextWarDateTime( WarType_t warType, const VSDateTime& dt );
	bool 	makeGCWarScheduleList(GCWarScheduleList* pGCWarScheduleList) const ;


public :
	void	lock() 		{ m_Mutex.lock(); }
	void	unlock() 		{ m_Mutex.unlock(); }

private:
	Zone*	m_pZone;

	mutable Mutex	m_Mutex;
};

#endif // __WAR_SCHEDULER_H__
