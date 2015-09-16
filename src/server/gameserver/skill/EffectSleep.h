//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSleep.h
// Written by  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SLEEP__
#define __EFFECT_SLEEP__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSleep
//////////////////////////////////////////////////////////////////////////////

class EffectSleep : public Effect
{
public:
    EffectSleep(Creature* pCreature) throw(Error);

public:
	EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SLEEP; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() const throw();

};

#endif // __EFFECT_SLEEP__

