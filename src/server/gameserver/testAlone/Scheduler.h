///////////////////////////////////////////////////////////////////
// 스케줄링된 작업을 위한 Scheduler 클래스.
///////////////////////////////////////////////////////////////////

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <vector>
#include <queue>
#include <hash_map>
#include "Exception.h"
#include "Work.h"
#include "Schedule.h"

class Latter {
public :
	bool operator () ( const Schedule* pt1, const Schedule* pt2 ) const
	{
		return pt1->getScheduledTime() > pt2->getScheduledTime();
	}
};

class RecentSchedules : public priority_queue< Schedule*, vector< Schedule* >, Latter > {
public :
	typedef container_type::iterator 		iterator;
	typedef container_type::const_iterator 	const_iterator;

public :
	const container_type& 	getSchedules() const	{ return c; }
	void					arrange() 				{ make_heap(c.begin(), c.end(), comp); }
};

class Scheduler 
{
public:
	Scheduler() throw();
	virtual ~Scheduler() throw();

	void			clear() throw(Error);

	int 			getSize() const						{ return m_RecentSchedules.size(); }
	bool 			isEmpty() const						{ return m_RecentSchedules.empty(); }

public:
	void 			addSchedule( Schedule* pSchedule ) throw (Error);

	virtual Work* 	heartbeat() throw(Error);

protected :
	Work* 			popRecentWork() throw (Error);

protected:
	RecentSchedules m_RecentSchedules;
};

#endif // __SCHEDULER_H__
