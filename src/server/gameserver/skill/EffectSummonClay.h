//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSummonClay.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SUMMON_CLAY__
#define __EFFECT_SUMMON_CLAY__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSummonClay
//////////////////////////////////////////////////////////////////////////////

class EffectSummonClay : public Effect 
{
public:
	EffectSummonClay(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SUMMON_CLAY; }

	void affect() ;
	void affect(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) ;

	void unaffect() ;

	string toString() const throw();

public:

private:
};

#endif
