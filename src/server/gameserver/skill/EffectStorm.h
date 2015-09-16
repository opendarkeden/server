//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectStorm.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_STORM__
#define __EFFECT_STORM__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectStorm
//////////////////////////////////////////////////////////////////////////////

class EffectStorm : public Effect 
{
public:
	EffectStorm(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_STORM; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	string toString() const throw();

public:
	Level_t getLevel() const throw() { return m_Level; }
	void setLevel(Level_t Level) throw() { m_Level = Level; }

	HP_t getPoint() const throw() { return m_Point; }
	void setPoint(HP_t Point) throw() { m_Point = Point; }

	void setTick(Turn_t Tick) throw() { m_Tick = Tick; }
	Turn_t getTick() const throw() { return m_Tick; }

private:
	Level_t m_Level;
	HP_t    m_Point;
	Turn_t  m_Tick;
};

#endif // __EFFECT_STORM__
