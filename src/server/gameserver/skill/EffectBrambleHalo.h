//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBrambleHalo.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_Bramble_Halo__
#define __EFFECT_Bramble_Halo__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBrambleHalo
//////////////////////////////////////////////////////////////////////////////

class EffectBrambleHalo : public Effect 
{
public:
	EffectBrambleHalo(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return m_EffectClass; }

	void affect() ;
	void affect(Creature* pCreature) ;

	void unaffect() ;
	void unaffect(Creature* pCreature) ;

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
