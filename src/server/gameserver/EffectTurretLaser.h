//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTurretLaser.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TURRET_LASER__
#define __EFFECT_TURRET_LASER__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectTurretLaser
//////////////////////////////////////////////////////////////////////////////

class EffectTurretLaser : public Effect 
{
public:
	EffectTurretLaser(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) ;

public:
    EffectClass getEffectClass() const  { return EFFECT_CLASS_TURRET_LASER; }

	void affect() ;
	void affect(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) ;

	void unaffect() ;

	string toString() const ;
};

#endif
