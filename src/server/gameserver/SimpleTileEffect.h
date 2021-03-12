//////////////////////////////////////////////////////////////////////////////
// Filename    : SimpleTileEffect.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __SIMPLE_TILE_EFFECT__
#define __SIMPLE_TILE_EFFECT__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class SimpleTileEffect
//////////////////////////////////////////////////////////////////////////////

class SimpleTileEffect : public Effect 
{
public:
	SimpleTileEffect(EffectClass eClass, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) ;

public:
    EffectClass getEffectClass() const  { return m_EffectClass; }

	void affect() {}

	void unaffect() ;

	string toString() const ;

private:
	EffectClass	m_EffectClass;
};

#endif
