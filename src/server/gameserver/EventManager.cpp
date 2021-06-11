//////////////////////////////////////////////////////////////////////////////
// Filename    : EventManager.cpp
// Written by  : Reiot
//////////////////////////////////////////////////////////////////////////////

#include "EventManager.h"
#include "Assert.h"

//////////////////////////////////////////////////////////////////////////////
// constructor
//////////////////////////////////////////////////////////////////////////////
EventManager::EventManager () 
    
{
	__BEGIN_TRY

	Assert(m_Events.empty());

	__END_CATCH
}
	
//////////////////////////////////////////////////////////////////////////////
// destructor
//////////////////////////////////////////////////////////////////////////////
EventManager::~EventManager () 
    
{
	__BEGIN_TRY
		
	while (!m_Events.empty()) 
	{
		SAFE_DELETE(m_Events.front());
		m_Events.pop_front();
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// add effect and affect it to its target
// priority_queue에 등록하고, affect한다.
//////////////////////////////////////////////////////////////////////////////
void EventManager::addEvent (Event* pEvent) 
     
{
	__BEGIN_TRY
	__END_DEBUG

	Assert(pEvent != NULL);
	
	Event* pPrevEvent = getEvent(pEvent->getEventClass());

	if (pPrevEvent == NULL)
	{
		// push to priority queue
		m_Events.push_back(pEvent);
	}
	else 
	{
		//cerr << "EventManager::addEvent() : Duplicated event class" << endl;
		throw ("EventManager::addEvent() : Duplicated event class");
	}

	__BEGIN_DEBUG
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
Event* EventManager::getEvent(Event::EventClass EClass) 
	
{
	__BEGIN_TRY

	list<Event*>::iterator itr = m_Events.begin();

	for (; itr != m_Events.end(); itr++)
	{
		Event* pEvent = *itr;
		if (pEvent->getEventClass() == EClass) return pEvent;
	}

	return NULL;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EventManager::deleteEvent (Event::EventClass EClass) 
     
{
	__BEGIN_TRY

	list<Event*>::iterator current = m_Events.begin();

	while (current != m_Events.end()) 
	{
		Assert(*current != NULL);
		Event* pEvent = *current;

		if (pEvent->getEventClass() == EClass) 
		{
			m_Events.erase(current);
			SAFE_DELETE(pEvent);
			break;
		}

		current++;
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void EventManager::heartbeat () 
     
{
	__BEGIN_TRY
		
	// 현재 시간을 측정한다.
	Timeval currentTime;
	getCurrentTime(currentTime);

	list<Event*>::iterator before  = m_Events.end();
	list<Event*>::iterator current = m_Events.begin();

	while (current != m_Events.end()) 
	{
		Assert(*current != NULL);

		Event* pEvent = *current;
		
		//--------------------------------------------------------------------------------
		// *WARNING*
		//
		// EventResurrect Event 의 경우, GamePlayer 객체가 ZPM 에서 IPM 으로 
		// 소속이 바뀌게 된다.  문제는 ZPM 과 IPM 이 서로 다른 쓰레드이기 
		// 때문에, IPM 에서 또다시 EventResurrect 가 activate 될 가능성이 있다는
		// 것이다. (어차피 GamePlayer 객체에서 EventResurrect 가 완전히 삭제되지
		// 않은 상태에서 IPM 으로 옮겨지기 때문이다.) 따라서, 이런 오류를
		// 피하기 위해서는 일회용 이벤트의 경우, 우선 이벤트를 
		// 이벤트매니저에서 삭제하고 나서 IPM 으로 옮기든지 해야 한다. 
		// 이때, 영구적인 이벤트의 경우 PM 사이를 옮겨 다니는 일이 없도록
		// 해야 할 것이다!!!! - 피할 방도가 없다 -
		//--------------------------------------------------------------------------------
		if (currentTime > pEvent->getDeadline())
		{
			// 일회용 이벤트의 경우
			if (pEvent->isTemporary())
			{
				// 이벤트를 삭제한다.
				m_Events.erase(current);

				if (before == m_Events.end()) { // first effect
					current = m_Events.begin();
				} else { // !first effect
					current = before;
					current ++;
				}
			}

			// 이벤트를 실행한다.
			pEvent->activate();

			// 일회용 이벤트의 경우
			if (pEvent->isTemporary())
			{
				// 이벤트 객체를 삭제한다.
				SAFE_DELETE(pEvent);
			}
		} 
		else 
		{
			before = current ++;
		}
	}

	__END_CATCH
}
