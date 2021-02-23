
//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectReputoFactum.h
// Written by  : 
// Description : ReputoFactum에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_REPUTO_FACTUM__
#define __EFFECT_REPUTO_FACTUM__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectReputoFactum
//////////////////////////////////////////////////////////////////////////////

class EffectReputoFactum : public Effect 
{
public:
	EffectReputoFactum(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_REPUTO_FACTUM_LAST; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

};

#endif // __EFFECT_REPUTO_FACTUM__
