//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTendril.h
// Written by  : 
// Description : Tendril에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TENDRIL__
#define __EFFECT_TENDRIL__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectTendril
//////////////////////////////////////////////////////////////////////////////

class EffectTendril : public Effect 
{
public:
	EffectTendril(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TENDRIL; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	int  getLevel() const { return m_Level; }
	void setLevel(int level) throw() { m_Level = level; }

	int getDefensePenalty(void) const { return m_DefensePenalty; }
	void setDefensePenalty(int penalty) { m_DefensePenalty = penalty; }

private:
	int m_Level;
	int m_DefensePenalty;
};

#endif // __EFFECT_TENDRIL__
