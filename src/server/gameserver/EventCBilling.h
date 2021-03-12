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
	EventCBilling(GamePlayer* pGamePlayer) ;
	virtual ~EventCBilling() ;

public:
	virtual EventClass getEventClass() const  { return EVENT_CLASS_CBILLING; }

	virtual bool isTemporary() const  { return false; }
	virtual bool isPermanent() const  { return true; }

	virtual void activate() ;
	
	virtual string toString() const  { return "CBilling Event"; }

private:
	int		m_TrySendLoginCount;		// Login 패킷을 보내기 시도 회수

};

#endif
