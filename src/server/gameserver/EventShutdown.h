//////////////////////////////////////////////////////////////////////////////
// Filename    : EventShutdown.h
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_SHUTDOWN_H__
#define __EVENT_SHUTDOWN_H__

#include "Event.h"

//////////////////////////////////////////////////////////////////////////////
// class EventShutdown
//////////////////////////////////////////////////////////////////////////////

class EventShutdown : public Event 
{
public:
	EventShutdown( GamePlayer* pGamePlayer ) throw();
	~EventShutdown() throw() {}
			
public:
	virtual EventClass getEventClass() const throw() { return EVENT_CLASS_SHUTDOWN; }
	virtual void activate() throw(Error);
	virtual string toString() const throw();

private:
};

#endif
