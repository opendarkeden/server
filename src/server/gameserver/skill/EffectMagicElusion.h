//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMagicElusion.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_MAGIC_ELUSION__
#define __EFFECT_MAGIC_ELUSION__

#include "Effect.h"
#include "EffectLoader.h"
#include "Tile.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectMagicElusion
//////////////////////////////////////////////////////////////////////////////

class EffectMagicElusion : public Effect 
{
public:
	EffectMagicElusion(Zone* pZone, ZoneCoord_t ZoneX, ZoneCoord_t ZoneY) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_MAGIC_ELUSION; }

	void affect() throw(Error){}

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error) {};

	string toString() const throw();
};

#endif // __EFFECT_MAGIC_ELUSION__
