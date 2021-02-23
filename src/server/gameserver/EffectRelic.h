//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRelic.h
// Written by  : 
// Description : Doom에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_RELIC__
#define __EFFECT_RELIC__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRelic
//////////////////////////////////////////////////////////////////////////////

class EffectRelic : public Effect 
{
public:
	EffectRelic(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_RELIC; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	HP_t getPoint() const throw() { return m_Point; }
	void setPoint(HP_t Point) throw() { m_Point = Point; }

	Turn_t getTick() const throw() { return m_Tick; }
	void   setTick(Turn_t Tick) throw() { m_Tick = Tick; }

private:
	HP_t   m_Point;  // 회복 에너지량
	Turn_t m_Tick;
};

#endif // __EFFECT_DOOM__
