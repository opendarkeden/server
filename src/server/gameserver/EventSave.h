//////////////////////////////////////////////////////////////////////////////
// Filename    : EventSave.h
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SAVE_H__
#define __SAVE_H__

#include "Event.h"

//////////////////////////////////////////////////////////////////////////////
// class EventSave;
// 각 캐릭터를 주기적으로 저장하도록 해주는 이벤트이다.
//////////////////////////////////////////////////////////////////////////////

class EventSave : public Event 
{
public:
	EventSave(GamePlayer* pGamePlayer) throw(Error);
	virtual ~EventSave() throw();

public:
	virtual EventClass getEventClass() const throw() { return EVENT_SAVE; }

	// get event life-cycle
	// EventSave 이벤트는 주기적으로 계속 실행되어야 하므로, 삭제되어서는 안된다.
	virtual bool isTemporary() const throw() { return false; }
	virtual bool isPermanent() const throw() { return true; }

	virtual void activate() throw(Error);
	
	virtual string toString() const throw() { return "EventSave Event"; }
};

#endif
