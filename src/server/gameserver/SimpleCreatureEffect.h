//////////////////////////////////////////////////////////////////////////////
// Filename    : SimpleCreatureEffect.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SIMPLE_CREATURE_EFFECT__
#define __EFFECT_SIMPLE_CREATURE_EFFECT__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class SimpleCreatureEffect
//////////////////////////////////////////////////////////////////////////////

class SimpleCreatureEffect : public Effect 
{
public:
	SimpleCreatureEffect(EffectClass eClass, Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return m_EffectClass; }

	void affect() throw(Error){}

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	string toString() const throw();

private:
	EffectClass	m_EffectClass;
};

#endif // __EFFECT_SIMPLE_CREATURE_EFFECT__
