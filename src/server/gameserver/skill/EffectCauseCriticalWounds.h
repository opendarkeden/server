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
    EffectCauseCriticalWounds(Creature* pCreature) throw(Error);

public:
	EffectClass getEffectClass() const throw() { return EFFECT_CLASS_CAUSE_CRITICAL_WOUNDS; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() const throw();

};

#endif // __EFFECT_CAUSE_CRITICAL_WOUNDS__

