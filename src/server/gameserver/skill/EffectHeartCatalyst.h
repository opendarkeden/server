//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHeartCatalyst.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HEART_CATALYST__
#define __EFFECT_HEART_CATALYST__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHeartCatalyst
//////////////////////////////////////////////////////////////////////////////

class EffectHeartCatalyst : public Effect 
{
public:
	EffectHeartCatalyst(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_HEART_CATALYST; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	int getHealPoint() throw() { return m_HealPoint;}
	void setHealPoint(HP_t HealPoint) throw(Error) { m_HealPoint = HealPoint; }

	int getTick() const { return m_Tick; }
	void setTick( int tick ) { m_Tick = tick; }

	bool canGiveExp() { return m_GiveExp=!m_GiveExp; }

private :
	int m_Tick;
	HP_t m_HealPoint;
	bool m_GiveExp;
};

#endif // __EFFECT_HEART_CATALYST__
