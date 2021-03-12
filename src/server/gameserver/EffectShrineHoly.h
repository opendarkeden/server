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
	EffectShrineHoly(Creature* pCreature) ;
	EffectShrineHoly(Item* pItem) ;

public:
    EffectClass getEffectClass() const  { return EFFECT_CLASS_SHRINE_HOLY; }
    EffectClass getSendEffectClass() const  { return (EffectClass)((int)EFFECT_CLASS_SHRINE_HOLY + m_ShrineID); }

	void affect()  {}
	void affect(Creature* pCreature) ;
	void affect(Item* pItem) ;

	void unaffect(Creature* pCreature) ;
	void unaffect(Item* pItem) ;
	void unaffect() ; 

	string toString() const ;

public:
	int getShrineID() const { return m_ShrineID; }
    void setShrineID(int id) { m_ShrineID = id; }

	int getTick(void) const { return m_Tick; }
	void   setTick(Turn_t Tick)  { m_Tick = Tick; }

private:
	int		m_ShrineID;
	Turn_t 	m_Tick;
};

#endif // __EFFECT_DOOM__
