//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectInvisibility.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_INVISIBILITY__
#define __EFFECT_INVISIBILITY__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectInvisibility
//////////////////////////////////////////////////////////////////////////////

class EffectInvisibility : public Effect 
{
public:
	EffectInvisibility(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_INVISIBILITY; }

	void affect() ;
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect() ;
	void unaffect(Creature* pCreature) ;
	void unaffect(Item* pItem)  {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	string toString() const throw();
};

#endif // __EFFECT_INVISIBILITY__
