//////////////////////////////////////////////////////////////////////////////
// Filename    : Effect.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
Effect::Effect () 
	throw()
{
	__BEGIN_TRY

	m_pZone   = NULL;
	m_X       = 0;
	m_Y       = 0;
	m_pTarget = NULL;
	m_bBroadcastingEffect = true;

	setNextTime(99999999);
	setDeadline(99999999);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
Effect::Effect (Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pTarget , Turn_t delay) 
	throw()
{
	__BEGIN_TRY

	m_pZone   = pZone;
	m_X       = x;
	m_Y       = y;
	m_pTarget = pTarget;

	setNextTime(99999999);
	setDeadline(delay);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
Effect::~Effect () 
{
}

void Effect::setNextTime(Turn_t delay) 
	throw()
{
	__BEGIN_TRY

	// 현재 시간을 측정한다.
	getCurrentTime(m_NextTime);
	
	// 이때, delay 는 0.1 초가 1 이다.
	m_NextTime.tv_sec += delay / 10;
	m_NextTime.tv_usec += (delay % 10)* 100000;

	__END_CATCH
}

void Effect::setDeadline (Turn_t delay) throw()
{
	__BEGIN_TRY

	// 현재 시간을 측정한다.
	getCurrentTime(m_Deadline);
	
	// 데드라인을 결정한다. 
	// 이때, delay 는 0.1 초가 1 이다.
	m_Deadline.tv_sec += delay / 10;
	m_Deadline.tv_usec += (delay % 10)* 100000;

	__END_CATCH
}

// 남은 duration(1/10초 단위)
Duration_t Effect::getRemainDuration() throw()
{
	__BEGIN_TRY

	Timeval currentTime;
	getCurrentTime(currentTime);
	return (m_Deadline.tv_sec  - currentTime.tv_sec)* 10 + 
	       (m_Deadline.tv_usec - currentTime.tv_usec) / 100000;

	__END_CATCH
}

