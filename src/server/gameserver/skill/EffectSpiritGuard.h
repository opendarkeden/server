//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSpiritGuard.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SPIRIT_GUARD__
#define __EFFECT_SPIRIT_GUARD__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSpiritGuard
//////////////////////////////////////////////////////////////////////////////

class EffectSpiritGuard : public Effect 
{
public:
	EffectSpiritGuard(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return m_EffectClass; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() const throw();

public:

	Damage_t getDamage() const { return m_Damage; }
	void setDamage( Damage_t damage ) { m_Damage = damage; }
	
	void setLevel(SkillLevel_t level);

	void setDelay(Turn_t delay) { m_Delay = delay; }
	Turn_t getDelay() const { return m_Delay; }

private:

	Turn_t m_Delay;
	Damage_t m_Damage;
	EffectClass m_EffectClass;
};

#endif
