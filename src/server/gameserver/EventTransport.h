//////////////////////////////////////////////////////////////////////////////
// Filename    : EventTransport.h
// Written by  : Reiot
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EVENT_TRANSPORT_H__
#define __EVENT_TRANSPORT_H__

#include "Event.h"
#include "Zone.h"

//////////////////////////////////////////////////////////////////////////////
// class EventTransport;
//////////////////////////////////////////////////////////////////////////////

class EventTransport : public Event 
{
public:
	EventTransport(GamePlayer* pGamePlayer) ;
	~EventTransport() ;			

public:
	virtual EventClass getEventClass() const  { return EVENT_CLASS_TRANSPORT; }

	virtual void activate() ;
	void setTargetZone(ZoneID_t ZoneID, ZoneCoord_t ZoneX, ZoneCoord_t ZoneY) 
	{
		m_ZoneID = ZoneID;
		m_X = ZoneX;
		m_Y = ZoneY;
	}
	void setZoneName(const string& zoneName) { m_ZoneName = zoneName; }
	void sendMessage() ;
	
	virtual string toString() const ;

public:
	ZoneID_t getTransportZoneID()  { return m_ZoneID; }
	void setTransportZoneID(ZoneID_t ZoneID)  { m_ZoneID = ZoneID; }

	ZoneCoord_t getX() const  { return m_X; }
	void setX(ZoneCoord_t x)  { m_X = x; }

	ZoneCoord_t getY() const  { return m_Y; }
	void setY(ZoneCoord_t y)  { m_Y = y; }

 	void setXY(ZoneCoord_t x, ZoneCoord_t y)  { m_X = x; m_Y = y; }


private:
	ZoneID_t 	m_ZoneID;
	string		m_ZoneName;

	ZoneCoord_t  m_X;
	ZoneCoord_t  m_Y;
};

#endif
