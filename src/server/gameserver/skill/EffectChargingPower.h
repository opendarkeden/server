//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectChargingPower.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_CHARGING_POWER__
#define __EFFECT_CHARGING_POWER__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectChargingPower
//////////////////////////////////////////////////////////////////////////////

class EffectChargingPower : public Effect 
{
public:
	EffectChargingPower(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_CHARGING_POWER; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	int getDamageBonus() throw() { return m_DamageBonus;}
	void setDamageBonus(ToHit_t DamageBonus) throw(Error) { m_DamageBonus = DamageBonus;}

private:
	Damage_t m_DamageBonus;
};

#endif // __EFFECT_CHARGING_POWER__
