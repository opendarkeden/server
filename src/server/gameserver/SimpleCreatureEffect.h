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
	SimpleCreatureEffect(EffectClass eClass, Creature* pCreature) ;

public:
    EffectClass getEffectClass() const  { return m_EffectClass; }

	void affect() {}

	void unaffect(Creature* pCreature) ;
	void unaffect() ;

	string toString() const ;

private:
	EffectClass	m_EffectClass;
};

#endif // __EFFECT_SIMPLE_CREATURE_EFFECT__
