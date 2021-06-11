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
	EventManager() ;
	virtual ~EventManager() ;

public:
	void   addEvent(Event* pEvent) ;
	Event* getEvent(Event::EventClass EClass) ;
	void   deleteEvent(Event::EventClass EClass) ;

	void   heartbeat() ;

	bool	   isEmpty() const { return m_Events.empty(); }

protected:
	list<Event*> m_Events;
	
};

#endif
