//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTransformToWolf.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TRANSFORM_TO_WOLF__
#define __EFFECT_TRANSFORM_TO_WOLF__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectTransformToWolf
//////////////////////////////////////////////////////////////////////////////

class EffectTransformToWolf : public Effect 
{
public:
	EffectTransformToWolf(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TRANSFORM_TO_WOLF; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);
	void unaffect() throw(Error); 
	void unaffect(Item* pItem) throw(Error) {}

	string toString() const throw();
};

#endif // __EFFECT_TRANSFORM_TO_WOLF__
