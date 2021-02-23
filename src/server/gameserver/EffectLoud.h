//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectLoud.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_LOUD__
#define __EFFECT_LOUD__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectLoud
//////////////////////////////////////////////////////////////////////////////

class EffectLoud : public Effect 
{
public:
	EffectLoud(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_LOUD; }

	void affect() throw(Error){}

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	string toString() const throw();

};

#endif // __EFFECT_LOUD__
