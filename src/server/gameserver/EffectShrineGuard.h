//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectShrineGuard.h
// Written by  : 
// Description : Doom에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SHRINE_GUARD__
#define __EFFECT_SHRINE_GUARD__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectShrineGuard
//////////////////////////////////////////////////////////////////////////////
// 성물 보관대에 붙는 이펙트이다.

class EffectShrineGuard : public Effect 
{
public:
	EffectShrineGuard(Creature* pCreature) throw(Error);
	EffectShrineGuard(Item* pItem) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SHRINE_GUARD; }
    EffectClass getSendEffectClass() const throw() { return (EffectClass)((int)EFFECT_CLASS_SHRINE_GUARD + m_ShrineID); }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);
	void affect(Item* pItem) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Item* pItem) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	int getTick(void) const { return m_Tick; }
	void   setTick(Turn_t Tick) throw() { m_Tick = Tick; }

	int getShrineID() const { return m_ShrineID; }
	void setShrineID(int id) { m_ShrineID = id; }

private:
	int		m_ShrineID;
	Turn_t 	m_Tick;
};

#endif // __EFFECT_DOOM__
