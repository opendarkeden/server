//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSeduction.h
// Written by  : excel96 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SEDUCTION__
#define __EFFECT_SEDUCTION__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSeduction
//////////////////////////////////////////////////////////////////////////////

class EffectSeduction : public Effect 
{
public:
	EffectSeduction(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SEDUCTION; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	int getLevel() const { return m_Level; }
	void setLevel(int level) throw() { m_Level = level; }

	int getToHitPenalty(void) const { return m_ToHitPenalty; }
	void setToHitPenalty(int penalty) { m_ToHitPenalty = penalty; }

	int getDamagePenalty(void) const { return m_DamagePenalty; }
	void setDamagePenalty(int penalty) { m_DamagePenalty = penalty; }

private:
	int m_Level;
	int m_ToHitPenalty;
	int m_DamagePenalty;
};

#endif // __EFFECT_SEDUCTION__
