//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectReactiveArmor.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_REACTIVE_ARMOR__
#define __EFFECT_REACTIVE_ARMOR__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectReactiveArmor
//////////////////////////////////////////////////////////////////////////////

class EffectReactiveArmor : public Effect 
{
public:
	EffectReactiveArmor(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_REACTIVE_ARMOR; }

	void affect() throw(Error){}

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	string toString() const throw();

public:
	void setBonus(uint bonus ) { m_Bonus = bonus; }
	uint getBonus() const { return m_Bonus; }

	void setDamageReduce(uint dr ) { m_DamageReduce = dr; }
	uint getDamageReduce() const { return m_DamageReduce; }

private:
	uint	m_Bonus;
	uint	m_DamageReduce;
};

#endif // __EFFECT_REACTIVE_ARMOR__
