//////////////////////////////////////////////////////////////////////////////
// Filename    : EventHeadCount.h
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_HEAD_COUNT_H__
#define __EVENT_HEAD_COUNT_H__

#include "Event.h"
#include "Zone.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////////
// class EventHeadCount;
//////////////////////////////////////////////////////////////////////////////

class EventHeadCount : public Event 
{
public:
	EventHeadCount(GamePlayer* pGamePlayer) ;
	~EventHeadCount() ;			

public:
	virtual EventClass getEventClass() const  { return EVENT_CLASS_HEAD_COUNT; }

	virtual void activate() ;

	virtual string toString() const ;

public:
	void	cutHead()
	{
		m_Count++;
	}

	virtual bool isTemporary() const  { return false; }
	virtual bool isPermanent() const  { return true; }

private:
	Level_t	m_LastLevel;
	uint	m_Count;
};

#endif
