//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGhost.h
// Written by  : 
// Description : ZoneID 마스터 레어 출입증
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GHOST__
#define __EFFECT_GHOST__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGhost
//////////////////////////////////////////////////////////////////////////////

class EffectGhost : public Effect 
{
public:
	EffectGhost(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_GHOST; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

private:
};

#endif
