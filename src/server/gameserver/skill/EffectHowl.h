//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHowl.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HOWL__
#define __EFFECT_HOWL__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHowl
//////////////////////////////////////////////////////////////////////////////

class EffectHowl : public Effect 
{
public:
	EffectHowl(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_HOWL; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();
};

#endif // __EFFECT_HOWL__
