//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectExtreme.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_EXTREME__
#define __EFFECT_EXTREME__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectExtreme
//////////////////////////////////////////////////////////////////////////////

class EffectExtreme : public Effect 
{
public:
	EffectExtreme(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_EXTREME; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	int getDamageBonus() throw() { return m_DamageBonus;}
	void setDamageBonus(ToHit_t DamageBonus) throw(Error) { m_DamageBonus = DamageBonus;}

private:
	Damage_t m_DamageBonus;
};

#endif // __EFFECT_EXTREME__
