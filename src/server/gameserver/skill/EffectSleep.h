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
    EffectSleep(Creature* pCreature) ;

public:
	EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SLEEP; }

	void affect() ;
	void affect(Creature* pCreature) ;

	void unaffect() ;
	void unaffect(Creature* pCreature) ;

	string toString() const throw();

};

#endif // __EFFECT_SLEEP__

