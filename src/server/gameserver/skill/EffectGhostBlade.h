//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGhostBlade.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GHOST_BLADE__
#define __EFFECT_GHOST_BLADE__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGhostBlade
//////////////////////////////////////////////////////////////////////////////

class EffectGhostBlade : public Effect 
{
public:
	EffectGhostBlade(Creature* pCreature) throw(Error);

public:
	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_GHOST_BLADE; }

	string toString() const throw();

public:
	int getToHitBonus() throw() { return m_ToHitBonus;}
	void setToHitBonus(ToHit_t ToHitBonus) throw(Error) { m_ToHitBonus = ToHitBonus;}

private :
	ToHit_t m_ToHitBonus;
};

#endif // __EFFECT_GHOST_BLADE__
