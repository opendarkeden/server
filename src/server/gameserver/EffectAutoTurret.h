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
	EffectAutoTurret(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_AUTO_TURRET; }

	void affect() throw(Error);
	void affect(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void unaffect() throw(Error);

	string toString() const throw();
};

#endif
