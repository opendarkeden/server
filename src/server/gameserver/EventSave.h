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
	EventSave(GamePlayer* pGamePlayer) ;
	virtual ~EventSave() ;

public:
	virtual EventClass getEventClass() const  { return EVENT_SAVE; }

	// get event life-cycle
	// EventSave 이벤트는 주기적으로 계속 실행되어야 하므로, 삭제되어서는 안된다.
	virtual bool isTemporary() const  { return false; }
	virtual bool isPermanent() const  { return true; }

	virtual void activate() ;
	
	virtual string toString() const  { return "EventSave Event"; }
};

#endif
