///////////////////////////////////////////////////////////////////
// 스케줄링된 작업을 위한 Scheduler 클래스 구현
///////////////////////////////////////////////////////////////////

#include "Scheduler.h"
#include "Assert.h"

Scheduler::Scheduler()
	throw()
{
}
Scheduler::~Scheduler()
	throw()
{
	clear();
}

void Scheduler::clear()
	throw (Error)
{
	__BEGIN_TRY

	while ( !m_RecentSchedules.empty() )
	{
		Schedule* pSchedule = m_RecentSchedules.top();
		m_RecentSchedules.pop();

		SAFE_DELETE(pSchedule);
	}

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
// addSchedule( Schedule* )
//
//--------------------------------------------------------------------------------
// Schedule은 RecentSchedules와 Schedules에 동시에 등록되어 있다.
//--------------------------------------------------------------------------------
void Scheduler::addSchedule( Schedule* pSchedule )  
	throw (Error)
{ 
	__BEGIN_TRY

	m_RecentSchedules.push( pSchedule ); 
	pSchedule->m_pScheduler = this;

	__END_CATCH
}

//--------------------------------------------------------------------------------
//
// popRecentWork( Schedule* pSchedule )
//
//--------------------------------------------------------------------------------
// m_RecentSchedules, m_Schedules에서 제거
// pRecentSchedule의 Work는 return하고 pRecentSchedule은 지운다
//--------------------------------------------------------------------------------
Work* Scheduler::popRecentWork()
	throw (Error)
{
	__BEGIN_TRY

	Schedule* pRecentSchedule = m_RecentSchedules.top();

	m_RecentSchedules.pop();

	Work* pWork = pRecentSchedule->popWork();
	SAFE_DELETE( pRecentSchedule );

	return pWork;

	__END_CATCH	
}

//--------------------------------------------------------------------------------
//
// Work* heartbeat()
//
//--------------------------------------------------------------------------------
// 가장 근래?에 실행될 수 있는 Schedule을 체크해보고 실행됐다면,
// Schedule의 Work를 return한다. 이 때, Schedule은 지운다.
//--------------------------------------------------------------------------------
Work* Scheduler::heartbeat()
	throw (Error)
{
	__BEGIN_TRY

	if( m_RecentSchedules.empty() ) return NULL;
	
	// priority queue 의 top()은 가장 작은 (위의 Former 에 의해서) 원소를 리턴한다.
	// 안타깝게도 지금은 가장 빠른 게 나올지 늦은게 나올지 모르겠다. -.-;;;
	// 2003. 1.23. by Sequoia
	// Former 클래스를 Latter 클래스로 바꿔서 지금은 가장 빠른 게 나온다.
	Schedule* pRecentSchedule = m_RecentSchedules.top();

	if( pRecentSchedule->heartbeat() ) 
	{
		return popRecentWork();
	}

	return NULL;

	__END_CATCH
}

