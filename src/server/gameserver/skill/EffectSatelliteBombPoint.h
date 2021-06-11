//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSatelliteBombPoint.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SKILL_SATELLITE_BOMB_POINT__
#define __EFFECT_SKILL_SATELLITE_BOMB_POINT__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSatelliteBombPoint
//////////////////////////////////////////////////////////////////////////////

class EffectSatelliteBombPoint : public Effect 
{
public:
	EffectSatelliteBombPoint(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SKILL_SATELLITE_BOMB_POINT; }

	void affect() {}

	void unaffect() ;

	string toString() const throw();

private:
};

#endif
