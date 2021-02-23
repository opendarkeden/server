//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectIceOfSoulStone.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ICE_OF_SOUL_STONE__
#define __EFFECT_ICE_OF_SOUL_STONE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectIceOfSoulStone
//////////////////////////////////////////////////////////////////////////////

class EffectIceOfSoulStone : public Effect 
{
public:
	EffectIceOfSoulStone(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_ICE_OF_SOUL_STONE; }

	void affect() throw(Error){}

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	string toString() const throw();

};

#endif // __EFFECT_ICE_OF_SOUL_STONE__
