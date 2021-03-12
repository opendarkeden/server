//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSatelliteBombAim.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SKILL_SATELLITE_BOMB_AIM__
#define __EFFECT_SKILL_SATELLITE_BOMB_AIM__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSatelliteBombAim
//////////////////////////////////////////////////////////////////////////////

class EffectSatelliteBombAim : public Effect 
{
public:
	EffectSatelliteBombAim(Creature* pCreature, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SKILL_SATELLITE_BOMB_AIM; }

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
