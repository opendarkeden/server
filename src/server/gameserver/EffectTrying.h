//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTrying.h
// Written by  : 
// Description : grand master 티 내는거. - -;	 by sigi. 2002.11.8
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TRYING__
#define __EFFECT_TRYING__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectTrying
//////////////////////////////////////////////////////////////////////////////

class EffectTrying : public Effect 
{
public:
//	EffectTrying(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) ;
	EffectTrying(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const  { return EFFECT_CLASS_TRYING; }

	void unaffect() ; 

	string toString() const  { return "EffectTrying"; }

private:
};

#endif
