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
	EffectRelicPosition(Item* pItem) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_RELIC_POSITION; }

	void affect() throw(Error);
	void affect(Item* pItem) throw(Error);

	void unaffect() throw(Error); 
	void unaffect(Item* pItem) throw(Error);

	string toString() const throw();

public:
	int getTick(void) const { return m_Tick; }
	void   setTick(Turn_t Tick) throw() { m_Tick = Tick; }

	ZoneID_t getZoneID() const { return m_ZoneID; }
	void setZoneID( ZoneID_t zoneID ) throw() { m_ZoneID = zoneID; }

	int getPart() const { return m_Part; }
	void setPart( int Part ) throw() { m_Part = Part; }

	ZoneCoord_t getX() const { return m_X; }
	void setX( ZoneCoord_t x ) throw() { m_X = x; }

	ZoneCoord_t getY() const { return m_Y; }
	void setY( ZoneCoord_t y ) throw() { m_Y = y; }

private:
	Turn_t m_Tick;

	ZoneID_t 	m_ZoneID;
	int	 		m_Part;
	ZoneCoord_t m_X;
	ZoneCoord_t m_Y;
};

#endif
