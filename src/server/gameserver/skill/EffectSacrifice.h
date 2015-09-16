//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSacrifice.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SACRIFICE__
#define __EFFECT_SACRIFICE__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSacrifice
//////////////////////////////////////////////////////////////////////////////

class EffectSacrifice : public Effect 
{
public:
	EffectSacrifice(Creature* pCreature) throw(Error);

public:
	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SACRIFICE; }

	string toString() const throw();

public:
	int getToHitBonus() throw() { return m_ToHitBonus;}
	void setToHitBonus(ToHit_t ToHitBonus) throw(Error) { m_ToHitBonus = ToHitBonus;}

private :
	ToHit_t m_ToHitBonus;
};

#endif // __EFFECT_SACRIFICE__
