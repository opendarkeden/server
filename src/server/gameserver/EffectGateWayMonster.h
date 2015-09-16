//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGateWayMonster.h
// Written by  : 
// Description : Doom에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GATEWAY_MONSTER__
#define __EFFECT_GATEWAY_MONSTER__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGateWayMonster
//////////////////////////////////////////////////////////////////////////////

class EffectGateWayMonster : public Effect 
{
public:
	EffectGateWayMonster(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_GATEWAY_MONSTER; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	int  getHPRecovery(void) const { return m_HPRecovery; }
	void setHPRecovery(int hp) { m_HPRecovery = hp; }

private:
	int m_HPRecovery = 1;
};

#endif // __EFFECT_DOOM__
