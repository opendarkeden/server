//////////////////////////////////////////////////////////////////////////////
// Filename    : EventManager.h
// Written by  : Reiot
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Event.h"
#include "Timeval.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
// class EventManager;
//////////////////////////////////////////////////////////////////////////////

class EventManager 
{
public:
	EventManager() throw(Error);
	virtual ~EventManager() throw();

public:
	void   addEvent(Event* pEvent) throw();
	Event* getEvent(Event::EventClass EClass) throw();
	void   deleteEvent(Event::EventClass EClass) throw();

	void   heartbeat() throw(Error);

	bool	   isEmpty() const { return m_Events.empty(); }

protected:
	list<Event*> m_Events;
	
};

#endif
