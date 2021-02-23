//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectFrozenArmor.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_FROZEN_ARMOR__
#define __EFFECT_FROZEN_ARMOR__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectFrozenArmor
//////////////////////////////////////////////////////////////////////////////

class EffectFrozenArmor : public Effect 
{
public:
	EffectFrozenArmor(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_FROZEN_ARMOR; }

	void affect() throw(Error){}

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	string toString() const throw();

public:
	void setBonus( uint bonus ) { m_Bonus = bonus; }
	uint getBonus() const { return m_Bonus; }

	void setTargetDuration( Duration_t dur ) { m_Dur = dur; }
	Duration_t getTargetDuration() const { return m_Dur; }

private:
	uint	m_Bonus;
	Duration_t	m_Dur;
};

#endif // __EFFECT_FROZEN_ARMOR__
