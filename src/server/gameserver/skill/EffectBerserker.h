//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBerserker.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BERSERKER__
#define __EFFECT_BERSERKER__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBerserker
//////////////////////////////////////////////////////////////////////////////

class EffectBerserker : public Effect 
{
public:
	EffectBerserker(Creature* pCreature) throw(Error);

public:
	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_BERSERKER; }

	string toString() const throw();

public:
	int getDefensePenalty(void) const { return m_DefensePenalty; }
	void setDefensePenalty(int penalty) { m_DefensePenalty = penalty; }

	int getProtectionPenalty(void) const { return m_ProtectionPenalty; }
	void setProtectionPenalty(int penalty) { m_ProtectionPenalty = penalty; }

	int getToHitBonus(void) const { return m_ToHitBonus; }
	void setToHitBonus(int bonus) { m_ToHitBonus = bonus; }
	
	int getDamageBonus(void) const { return m_DamageBonus; }
	void setDamageBonus(int bonus) { m_DamageBonus = bonus; }

private :
	int m_DefensePenalty;
	int m_ProtectionPenalty;
	int m_ToHitBonus;
	int m_DamageBonus;
};

#endif // __EFFECT_BERSERKER__
