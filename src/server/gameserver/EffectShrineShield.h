//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectShrineShield.h
// Written by  : 
// Description : Doom에 의한 방어력 하강 effect
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SHRINE_SHIELD__
#define __EFFECT_SHRINE_SHIELD__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectShrineShield
//////////////////////////////////////////////////////////////////////////////
// 성물 보관대에 붙는 이펙트이다.

class EffectShrineShield : public Effect 
{
public:
	EffectShrineShield(Creature* pCreature) ;
	EffectShrineShield(Item* pItem) ;

public:
    EffectClass getEffectClass() const  { return EFFECT_CLASS_SHRINE_SHIELD; }

	void affect()  {}
	void affect(Creature* pCreature) ;
	void affect(Item* pItem) ;

	void unaffect(Creature* pCreature) ;
	void unaffect(Item* pItem) ;
	void unaffect() ; 

	string toString() const ;

public:
	int getTick(void) const { return m_Tick; }
	void   setTick(Turn_t Tick)  { m_Tick = Tick; }

	int getShrineID() const { return m_ShrineID; }
	void setShrineID(int id) { m_ShrineID = id; }

private:
	int		m_ShrineID;
	Turn_t 	m_Tick;
};

#endif // __EFFECT_DOOM__
