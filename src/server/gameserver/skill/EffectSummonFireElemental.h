//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSummonFireElemental.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SUMMON_FIRE_ELEMENTAL__
#define __EFFECT_SUMMON_FIRE_ELEMENTAL__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSummonFireElemental
//////////////////////////////////////////////////////////////////////////////

class EffectSummonFireElemental : public Effect 
{
public:
	EffectSummonFireElemental(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_FIRE_ELEMENTAL; }

	void affect() throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	string toString() const throw();

public:
	void setDamage( uint bonus ) { m_Damage = bonus; }
	uint getDamage() const { return m_Damage; }

	void setRange( Range_t Range ) { m_Range = Range; }
	Range_t getRange() const { return m_Range; }

private:
	uint	m_Damage;
	Range_t	m_Range;
};

#endif // __EFFECT_SUMMON_FIRE_ELEMENTAL__
