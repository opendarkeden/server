//////////////////////////////////////////////////////////////////////////////
// Filename    : EventSystemMessage.h
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_SYSTEM_MESSAGE_H__
#define __EVENT_SYSTEM_MESSAGE_H__

#include "Event.h"
#include "Zone.h"

//////////////////////////////////////////////////////////////////////////////
// class EventSystemMessage;
//////////////////////////////////////////////////////////////////////////////

class EventSystemMessage : public Event 
{
public:
	EventSystemMessage(GamePlayer* pGamePlayer) ;
	~EventSystemMessage() ;			

public:
	virtual EventClass getEventClass() const  { return EVENT_CLASS_SYSTEM_MESSAGE; }

	virtual void activate() ;
	
	virtual string toString() const ;

	void	addMessage(const string& msg) ;

private:
	list<string>	m_Messages;
};

#endif
