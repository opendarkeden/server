//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectCauseCriticalWounds.h
// Written by  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_CAUSE_CRITICAL_WOUNDS__
#define __EFFECT_CAUSE_CRITICAL_WOUNDS__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectCauseCriticalWounds
//////////////////////////////////////////////////////////////////////////////

class EffectCauseCriticalWounds : public Effect
{
public:
    EffectCauseCriticalWounds(Creature* pCreature) ;

public:
	EffectClass getEffectClass() const throw() { return EFFECT_CLASS_CAUSE_CRITICAL_WOUNDS; }

	void affect() ;
	void affect(Creature* pCreature) ;

	void unaffect() ;
	void unaffect(Creature* pCreature) ;

	string toString() const throw();

};

#endif // __EFFECT_CAUSE_CRITICAL_WOUNDS__

