//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDoom.h
// Written by  : 
// Description : Doom에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DOOM__
#define __EFFECT_DOOM__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDoom
//////////////////////////////////////////////////////////////////////////////

class EffectDoom : public Effect 
{
public:
	EffectDoom(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DOOM; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	int  getLevel() const { return m_Level; }
	void setLevel(int level) throw() { m_Level = level; }

	int getDefensePenalty(void) const { return m_DefensePenalty; }
	void setDefensePenalty(int penalty) { m_DefensePenalty = penalty; }

	int getProtectionPenalty(void) const { return m_ProtectionPenalty; }
	void setProtectionPenalty(int penalty) { m_ProtectionPenalty = penalty; }

private:
	int m_Level;
	int m_DefensePenalty;
	int m_ProtectionPenalty;
};

#endif // __EFFECT_DOOM__
