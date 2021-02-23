//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMercyGround.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_MERCY_GROUND__
#define __EFFECT_MERCY_GROUND__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectMercyGround
//////////////////////////////////////////////////////////////////////////////

class EffectMercyGround : public Effect 
{
public:
	EffectMercyGround(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_MERCY_GROUND; }

	void affect() throw(Error);
	void affect(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void unaffect() throw(Error);

	string toString() const throw();

public:

private:
};

#endif
