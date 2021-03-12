//////////////////////////////////////////////////////////////////////////////
// Filename    : EventResurrect.h
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENTRESURRECT_H__
#define __EVENTRESURRECT_H__

#include "Event.h"
#include "Zone.h"

//////////////////////////////////////////////////////////////////////////////
// class EventResurrect;
//////////////////////////////////////////////////////////////////////////////

class EventResurrect : public Event 
{
public:
	EventResurrect(GamePlayer* pGamePlayer) ;
	~EventResurrect() ;			

public:
	virtual EventClass getEventClass() const  { return EVENT_CLASS_RESURRECT; }

	virtual void activate() ;
	
	virtual string toString() const ;

public:
	/*
	Zone* getResurrectZone()  { return m_pResurrectZone; }
	void setResurrectZone(Zone* ResurrectZone)  { m_pResurrectZone = ResurrectZone; }

	// 부활할 위치
	ZoneCoord_t getX() const  { return m_X; }
	void setX(ZoneCoord_t x)  { m_X = x; }

	ZoneCoord_t getY() const  { return m_Y; }
	void setY(ZoneCoord_t y)  { m_Y = y; }

 	void setXY(ZoneCoord_t x, ZoneCoord_t y)  { m_X = x; m_Y = y; }
	*/


private:
	//Zone* m_pResurrectZone;

	//ZoneCoord_t  m_X;
	//ZoneCoord_t  m_Y;
};

#endif
