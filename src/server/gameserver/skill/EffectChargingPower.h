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
	EffectChargingPower(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_CHARGING_POWER; }

	void affect()  {}
	void affect(Creature* pCreature) ;

	void unaffect(Creature* pCreature) ;
	void unaffect() ; 

	string toString() const throw();

public:
	int getDamageBonus() throw() { return m_DamageBonus;}
	void setDamageBonus(ToHit_t DamageBonus)  { m_DamageBonus = DamageBonus;}

private:
	Damage_t m_DamageBonus;
};

#endif // __EFFECT_CHARGING_POWER__
