//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectAutoTurret.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_AUTO_TURRET__
#define __EFFECT_AUTO_TURRET__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectAutoTurret
//////////////////////////////////////////////////////////////////////////////

class EffectAutoTurret : public Effect 
{
public:
	EffectAutoTurret(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) ;

public:
    EffectClass getEffectClass() const  { return EFFECT_CLASS_AUTO_TURRET; }

	void affect() ;
	void affect(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) ;

	void unaffect() ;

	string toString() const ;
};

#endif
