//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectCannonade.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_CANNONADE__
#define __EFFECT_CANNONADE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectCannonade
//////////////////////////////////////////////////////////////////////////////

class EffectCannonade : public Effect 
{
public:
	EffectCannonade(Creature* pCreature, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_MAX; }

	void affect() {}
	void affect(Creature* pCreature) ;

	void unaffect() ;
	void unaffect(Creature* pCreature) ;

	string toString() const throw();

public:
	Damage_t getDamage() const { return m_Damage; }
	void setDamage( Damage_t damage ) { m_Damage = damage; }
	
private:

	Damage_t	m_Damage;
};

#endif
