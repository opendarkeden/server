//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRelicPosition.h
// Written by  : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_RELIC_POSITION__
#define __EFFECT_RELIC_POSITION__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRelicPosition
//////////////////////////////////////////////////////////////////////////////

class EffectRelicPosition : public Effect 
{
public:
	EffectRelicPosition(Item* pItem) ;

public:
    EffectClass getEffectClass() const  { return EFFECT_CLASS_RELIC_POSITION; }

	void affect() ;
	void affect(Item* pItem) ;

	void unaffect() ; 
	void unaffect(Item* pItem) ;

	string toString() const ;

public:
	int getTick(void) const { return m_Tick; }
	void   setTick(Turn_t Tick)  { m_Tick = Tick; }

	ZoneID_t getZoneID() const { return m_ZoneID; }
	void setZoneID( ZoneID_t zoneID )  { m_ZoneID = zoneID; }

	int getPart() const { return m_Part; }
	void setPart( int Part )  { m_Part = Part; }

	ZoneCoord_t getX() const { return m_X; }
	void setX( ZoneCoord_t x )  { m_X = x; }

	ZoneCoord_t getY() const { return m_Y; }
	void setY( ZoneCoord_t y )  { m_Y = y; }

private:
	Turn_t m_Tick;

	ZoneID_t 	m_ZoneID;
	int	 		m_Part;
	ZoneCoord_t m_X;
	ZoneCoord_t m_Y;
};

#endif
