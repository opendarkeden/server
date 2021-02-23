///////////////////////////////////////////////////////////////////
// 스케줄링된 작업을 위한 Schedule 클래스 구현
///////////////////////////////////////////////////////////////////

#include "Exception.h"
#include "Work.h"
#include "StringStream.h"

#include "Schedule.h"

Schedule::Schedule( Work* pWork, const VSDateTime& Time, ScheduleType type )
	throw()
: m_ScheduleType( type ), m_pWork( pWork ), m_ScheduledTime( Time )
{
	__BEGIN_TRY

	//m_LimitCheckDateTime 	= VSDateTime::currentDateTime().addDays(1);
	//m_LimitCheckTime	 	= VSTime::currentTime().addSecs(60);
//	m_WrongCount 			= 0;

	__END_CATCH
}

Schedule::~Schedule()
	throw()
{
	__BEGIN_TRY

	SAFE_DELETE(m_pWork);

	__END_CATCH
}

Work*
Schedule::popWork()
{
	Work* pWork = m_pWork;

	m_pWork = NULL;

	return pWork;
}

bool Schedule::heartbeat()
	throw(Error)
{
	__BEGIN_TRY

	//VSDateTime current( VSDateTime::currentDateTime() );
	VSDate cd = VSDate::currentDate();
	VSTime ct = VSTime::currentTime();

	VSDateTime current = VSDateTime( cd, ct );

	if( current >= m_ScheduledTime )
	{
		filelog("Schedule.txt", "Execute(%s >= %s) : %s", 
					current.toString().c_str(), 
					m_ScheduledTime.toString().c_str(),
					m_pWork->toString().c_str());

		m_pWork->execute();
		return true;
	}

	return false;

	__END_CATCH
}

string Schedule::toString() const
	throw (Error)
{
	__BEGIN_TRY

	StringStream msg;

	msg << "Schedule("
		<< "ScheduleType:" << (int)m_ScheduleType
		<< ",ScheduledTime:" << m_ScheduledTime.toString();

		if (m_pWork==NULL)
			msg << ",Work:NULL";
		else
			msg << ",Work:" << m_pWork->toString();

	msg << ")";

	return msg.toString();

	__END_CATCH
}
