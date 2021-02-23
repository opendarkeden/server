//////////////////////////////////////////////////////////////////////////////
// Filename    : EventKick.h
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_KICK_H__
#define __EVENT_KICK_H__

#include "Event.h"
#include "Zone.h"

//////////////////////////////////////////////////////////////////////////////
// class EventKick;
//////////////////////////////////////////////////////////////////////////////

class EventKick : public Event 
{
public:
	EventKick(GamePlayer* pGamePlayer) throw();
	~EventKick() throw();			

public:
	virtual EventClass getEventClass() const throw() { return EVENT_CLASS_KICK; }

	virtual void activate() throw(Error);
	void sendMessage() throw (Error);

	virtual string toString() const throw();
};

#endif
