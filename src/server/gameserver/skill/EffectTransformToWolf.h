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
	EffectTransformToWolf(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TRANSFORM_TO_WOLF; }

	void affect()  {}
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect(Creature* pCreature) ;
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;
	void unaffect() ; 
	void unaffect(Item* pItem)  {}

	string toString() const throw();
};

#endif // __EFFECT_TRANSFORM_TO_WOLF__
