//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBlockHead.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BLOCK_HEAD__
#define __EFFECT_BLOCK_HEAD__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBlockHead
//////////////////////////////////////////////////////////////////////////////

class EffectBlockHead : public Effect 
{
public:
	EffectBlockHead(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_BLOCK_HEAD; }

	void affect() {}

	void unaffect(Creature* pCreature) ;
	void unaffect() ;

	string toString() const throw();

};

#endif // __EFFECT_BLOCK_HEAD__
