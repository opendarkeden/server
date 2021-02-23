//////////////////////////////////////////////////////////////////////////////
// Filename    : EventAuth.h
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_AUTH_H__
#define __EVENT_AUTH_H__

#include "Event.h"

//////////////////////////////////////////////////////////////////////////////
// class EventAuth;
//////////////////////////////////////////////////////////////////////////////

class EventAuth : public Event 
{
public:
	EventAuth(GamePlayer* pGamePlayer) throw(Error);
	virtual ~EventAuth() throw();

public:
	virtual EventClass getEventClass() const throw() { return EVENT_CLASS_AUTH; }

	virtual bool isTemporary() const throw() { return false; }
	virtual bool isPermanent() const throw() { return true; }

	virtual void activate() throw(Error);

	virtual string toString() const throw() { return "Auth Event"; }
};

#endif
