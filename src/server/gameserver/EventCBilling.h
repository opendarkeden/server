//////////////////////////////////////////////////////////////////////////////
// Filename    : EventCBilling.h
// Written by  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_CBILLING_H__
#define __EVENT_CBILLING_H__

#include "Event.h"

//////////////////////////////////////////////////////////////////////////////
// class EventCBilling;
//////////////////////////////////////////////////////////////////////////////

class EventCBilling : public Event 
{
public:
	EventCBilling(GamePlayer* pGamePlayer) throw(Error);
	virtual ~EventCBilling() throw();

public:
	virtual EventClass getEventClass() const throw() { return EVENT_CLASS_CBILLING; }

	virtual bool isTemporary() const throw() { return false; }
	virtual bool isPermanent() const throw() { return true; }

	virtual void activate() throw(Error);
	
	virtual string toString() const throw() { return "CBilling Event"; }

private:
	int		m_TrySendLoginCount;		// Login 패킷을 보내기 시도 회수

};

#endif
