//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectShrineHoly.h
// Written by  : 
// Description : Doom에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SHRINE_HOLY__
#define __EFFECT_SHRINE_HOLY__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectShrineHoly
//////////////////////////////////////////////////////////////////////////////
// 성물 보관대에 붙는 이펙트이다.

class EffectShrineHoly : public Effect 
{
public:
	EffectShrineHoly(Creature* pCreature) throw(Error);
	EffectShrineHoly(Item* pItem) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SHRINE_HOLY; }
    EffectClass getSendEffectClass() const throw() { return (EffectClass)((int)EFFECT_CLASS_SHRINE_HOLY + m_ShrineID); }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);
	void affect(Item* pItem) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Item* pItem) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	int getShrineID() const { return m_ShrineID; }
    void setShrineID(int id) { m_ShrineID = id; }

	int getTick(void) const { return m_Tick; }
	void   setTick(Turn_t Tick) throw() { m_Tick = Tick; }

private:
	int		m_ShrineID;
	Turn_t 	m_Tick;
};

#endif // __EFFECT_DOOM__
