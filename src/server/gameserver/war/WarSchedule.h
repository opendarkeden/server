///////////////////////////////////////////////////////////////////
// 전쟁 스케줄. DB I/O 지원용
///////////////////////////////////////////////////////////////////

#ifndef __WAR_SCHEDULE_H__
#define __WAR_SCHEDULE_H__

#include "Types.h"
#include "Work.h"
#include "Schedule.h"
#include "Exception.h"
#include "War.h"

struct WarScheduleInfo;
struct WarInfo;

class WarSchedule : public Schedule
{
public:
	WarSchedule( Work* pWork, const VSDateTime& Time, ScheduleType type = SCHEDULE_TYPE_ONCE ) throw(Error);
	virtual ~WarSchedule() throw (Error);

public:
	void		create() throw(Error);
	void		tinysave( const string& query ) throw(Error);
#ifndef __OLD_GUILD_WAR__
	void		save() throw(Error);
#endif
	const War*	getWar() const 		{ return dynamic_cast<const War*>( getWork() ); }
	War*		getWar() 			{ return dynamic_cast<War*>( getWork() ); }
	WarID_t 	getWarID() const 	{ return getWar()->getWarID(); }

	virtual bool heartbeat() throw(Error);

public :
	void	makeWarScheduleInfo( WarScheduleInfo* pWSI ) const throw (Error);
	void	makeWarInfo( WarInfo* pWarInfo ) const throw (Error);

private:
};

#endif // __WAR_SCHEDULE_H__
