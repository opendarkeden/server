//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectStriking.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_STRIKING__
#define __EFFECT_STRIKING__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectStriking
//////////////////////////////////////////////////////////////////////////////

class EffectStriking : public Effect 
{
public:
	EffectStriking(Item* pItem) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_STRIKING; }

	void affect() {}
	void affect(Item* pItem) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect(Item* pItem) ;
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;
    void unaffect() ;
	void unaffect(Creature* pCreature) {};		

	string toString() const throw();

public:
	void setIncDamage(Damage_t d)  { m_incDamage = d;}

private :
	Damage_t m_incDamage;
};

#endif // __EFFECT_STRIKING__
