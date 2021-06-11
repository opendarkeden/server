//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectActivation.h
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ACTIVATION__
#define __EFFECT_ACTIVATION__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectActivation
//////////////////////////////////////////////////////////////////////////////

class EffectActivation : public Effect 
{
public:
	EffectActivation(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_ACTIVATION; }

	void affect() {}
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect() ;
	void unaffect(Creature* pCreature) ;
	void unaffect(Item* pItem)  {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	string toString() const throw();

private:

};

#endif // __EFFECT_ACTIVATION__
