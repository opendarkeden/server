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
	SimpleTileEffect(EffectClass eClass, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return m_EffectClass; }

	void affect() throw(Error){}

	void unaffect() throw(Error);

	string toString() const throw();

private:
	EffectClass	m_EffectClass;
};

#endif
