//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTyphoon.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TYPHOON__
#define __EFFECT_TYPHOON__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectTyphoon
//////////////////////////////////////////////////////////////////////////////

class EffectTyphoon : public Effect 
{
public:
	EffectTyphoon(Creature* pCreature) ;

public:
	void affect()  {}
	void affect(Creature* pCreature) ;

	void unaffect(Creature* pCreature) ;
	void unaffect() ; 

    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TYPHOON; }

	string toString() const throw();
};

#endif // __EFFECT_TYPHOON__
