//////////////////////////////////////////////////////////////////////////////
// Filename    : EventRegeneration.h
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENTREGENERATION_H__
#define __EVENTREGENERATION_H__

#include "Event.h"

//////////////////////////////////////////////////////////////////////////////
// class EventRegeneration;
//////////////////////////////////////////////////////////////////////////////

class EventRegeneration : public Event 
{
public:
	EventRegeneration(GamePlayer* pGamePlayer) throw(Error);
	virtual ~EventRegeneration() throw();

public:
	virtual EventClass getEventClass() const throw() { return EVENT_CLASS_REGENERATION; }

	virtual bool isTemporary() const throw() { return false; }
	virtual bool isPermanent() const throw() { return true; }

	virtual void activate() throw(Error);
	
	virtual string toString() const throw() { return "Regeneration Event"; }

};

#endif
