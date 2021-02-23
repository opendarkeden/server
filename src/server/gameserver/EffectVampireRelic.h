//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectVampireRelic.h
// Written by  : 
// Description : Doom에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_VAMPIRE_RELIC__
#define __EFFECT_VAMPIRE_RELIC__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectVampireRelic
//////////////////////////////////////////////////////////////////////////////

class EffectVampireRelic : public Effect 
{
public:
	EffectVampireRelic(Creature* pCreature) throw(Error);
	EffectVampireRelic(Item* pItem) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_VAMPIRE_RELIC; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);
	void affect(Item* pItem) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Item* pItem) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	int  getHPRecovery(void) const { return m_HPRecovery; }
	void setHPRecovery(int hp) { m_HPRecovery = hp; }

	int getTick(void) const { return m_Tick; }
	void   setTick(Turn_t Tick) throw() { m_Tick = Tick; }
private:
	int m_HPRecovery; 
	Turn_t m_Tick;
};

#endif // __EFFECT_DOOM__
