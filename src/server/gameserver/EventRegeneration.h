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
	EventRegeneration(GamePlayer* pGamePlayer) ;
	virtual ~EventRegeneration() ;

public:
	virtual EventClass getEventClass() const  { return EVENT_CLASS_REGENERATION; }

	virtual bool isTemporary() const  { return false; }
	virtual bool isPermanent() const  { return true; }

	virtual void activate() ;
	
	virtual string toString() const  { return "Regeneration Event"; }

};

#endif
