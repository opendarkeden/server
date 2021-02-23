//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGunShotGuidanceAim.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GUN_SHOT_GUIDANCE_AIM__
#define __EFFECT_GUN_SHOT_GUIDANCE_AIM__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGunShotGuidanceAim
//////////////////////////////////////////////////////////////////////////////

class EffectGunShotGuidanceAim : public Effect 
{
public:
	EffectGunShotGuidanceAim(Creature* pCreature, Zone* pZone, ZoneCoord_t x, ZoneCoord_t y) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_GUN_SHOT_GUIDANCE_AIM; }

	void affect() throw(Error){}
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() const throw();

public:
	Damage_t getDamage() const { return m_Damage; }
	void setDamage( Damage_t damage ) { m_Damage = damage; }
	
private:

	Damage_t	m_Damage;
};

#endif
