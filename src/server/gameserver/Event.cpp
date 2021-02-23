//////////////////////////////////////////////////////////////////////////////
// Filename    : Event.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Event.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// class Event member methods
//////////////////////////////////////////////////////////////////////////////

Event::Event(GamePlayer* pGamePlayer)
	throw(Error)
{
	__BEGIN_TRY

	m_pGamePlayer = pGamePlayer;

	// EventReloadInfo때문에 assert제거했다. NULL일 수 있기 때문에
	// 사실 EventReloadInfo를 Event로 만들 이유는 없었지만(GamePlayer랑 관계없다 -_-;)
	// 개발 시간상.. EventManager를 쓸 수 밖에 없어서리.. -_-
	// by sigi. 2002.9.26
//	Assert(m_pGamePlayer != NULL);

	m_Deadline.tv_sec  = 0;
	m_Deadline.tv_usec = 0;

	__END_CATCH
}

Event::~Event()
	throw()
{
	__BEGIN_TRY
	__END_CATCH
}

void Event::setDeadline(Turn_t delay)
	throw()
{
	__BEGIN_TRY

	// 현재 시간을 측정한다.
	getCurrentTime(m_Deadline);

	// 데드라인을 결정한다. 
	// 이때, delay 는 0.1 초가 1 이다.
	m_Deadline.tv_sec += delay / 10;
	m_Deadline.tv_usec +=(delay % 10)* 100000;

	__END_CATCH
}


