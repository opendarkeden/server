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
	EffectGhost(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const  { return EFFECT_CLASS_GHOST; }

	void affect() ;
	void affect(Creature* pCreature) ;

	void unaffect(Creature* pCreature) ;
	void unaffect() ; 

	string toString() const ;

private:
};

#endif
