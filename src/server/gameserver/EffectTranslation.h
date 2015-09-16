//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTranslation.h
// Written by  : 
// Description : Doom에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TRANSLATION__
#define __EFFECT_TRANSLATION__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectTranslation
//////////////////////////////////////////////////////////////////////////////

class EffectTranslation : public Effect 
{
public:
	EffectTranslation(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TRANSLATION; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();
};

#endif // __EFFECT_DOOM__
