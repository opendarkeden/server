//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPassingHeal.h
// Written by  : excel96
// Description : 
// PassingHeal에 의해서 생성되는 산성 데미지 약화 이펙트이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PASSING_HEAL__
#define __EFFECT_PASSING_HEAL__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectPassingHeal
//////////////////////////////////////////////////////////////////////////////

class EffectPassingHeal : public Effect 
{
public:
	EffectPassingHeal(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_PASSING_HEAL; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	int getPassingCount() const { return m_PassingCount; }
	void setPassingCount(int PassingCount) { m_PassingCount = PassingCount; }

	int getCureCount() const { return m_CureCount; }
	void setCureCount(int CureCount) { m_CureCount = CureCount; }

	int getHealPoint() const { return m_HealPoint; }
	void setHealPoint(int HealPoint) { m_HealPoint = HealPoint; }

	string toString() const throw();

private:
	int	m_PassingCount;
	int	m_CureCount;
	int	m_HealPoint;
};

#endif // __EFFECT_PASSING_HEAL__
