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
	EventAuth(GamePlayer* pGamePlayer) ;
	virtual ~EventAuth() ;

public:
	virtual EventClass getEventClass() const  { return EVENT_CLASS_AUTH; }

	virtual bool isTemporary() const  { return false; }
	virtual bool isPermanent() const  { return true; }

	virtual void activate() ;

	virtual string toString() const  { return "Auth Event"; }
};

#endif
