//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGunShotGuidancePoint.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GUN_SHOT_GUIDANCE_POINT__
#define __EFFECT_GUN_SHOT_GUIDANCE_POINT__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGunShotGuidancePoint
//////////////////////////////////////////////////////////////////////////////

class EffectGunShotGuidancePoint : public Effect 
{
public:
	EffectGunShotGuidancePoint(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_GUN_SHOT_GUIDANCE_POINT; }

	void affect() throw(Error){}

	void unaffect() throw(Error);

	string toString() const throw();

private:
};

#endif
