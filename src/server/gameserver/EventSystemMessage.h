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
	EventSystemMessage(GamePlayer* pGamePlayer) throw();
	~EventSystemMessage() throw();			

public:
	virtual EventClass getEventClass() const throw() { return EVENT_CLASS_SYSTEM_MESSAGE; }

	virtual void activate() throw(Error);
	
	virtual string toString() const throw();

	void	addMessage(const string& msg) throw(Error);

private:
	list<string>	m_Messages;
};

#endif
