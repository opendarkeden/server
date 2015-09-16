//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTransformToBat.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TRANSFORM_TO_BAT__
#define __EFFECT_TRANSFORM_TO_BAT__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectTransformToBat
//////////////////////////////////////////////////////////////////////////////

class EffectTransformToBat : public Effect 
{
public:
	EffectTransformToBat(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TRANSFORM_TO_BAT; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);
	void unaffect() throw(Error); 
	void unaffect(Item* pItem) throw(Error) {}

	string toString() const throw();
};

#endif // __EFFECT_TRANSFORM_TO_BAT__
