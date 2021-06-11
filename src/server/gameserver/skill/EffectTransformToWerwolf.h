//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTransformToWerwolf.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TRANSFORM_TO_WERWOLF__
#define __EFFECT_TRANSFORM_TO_WERWOLF__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectTransformToWerwolf
//////////////////////////////////////////////////////////////////////////////

class EffectTransformToWerwolf : public Effect 
{
public:
	EffectTransformToWerwolf(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TRANSFORM_TO_WERWOLF; }

	void affect()  {}
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect(Creature* pCreature) ;
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;
	void unaffect() ; 
	void unaffect(Item* pItem)  {}

	string toString() const throw();
};

#endif // __EFFECT_TRANSFORM_TO_WERWOLF__
