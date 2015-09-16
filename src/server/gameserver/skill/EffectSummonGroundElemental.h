//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSummonGroundElemental.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SUMMON_GROUND_ELEMENTAL__
#define __EFFECT_SUMMON_GROUND_ELEMENTAL__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSummonGroundElemental
//////////////////////////////////////////////////////////////////////////////

class EffectSummonGroundElemental : public Effect 
{
public:
	EffectSummonGroundElemental(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_GROUND_ELEMENTAL_AURA; }

	void affect() throw(Error);
	void affect(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void unaffect() throw(Error);

	string toString() const throw();

public:

private:
};

#endif
