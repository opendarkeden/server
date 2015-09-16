//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDancingSword.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DANCING_SWORD__
#define __EFFECT_DANCING_SWORD__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDancingSword
//////////////////////////////////////////////////////////////////////////////

class EffectDancingSword : public Effect 
{
public:
	EffectDancingSword(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DANCING_SWORD; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	int getToHitBonus() throw() { return m_ToHitBonus;}
	void setToHitBonus(ToHit_t ToHitBonus) throw(Error) { m_ToHitBonus = ToHitBonus;}

private :
	ToHit_t m_ToHitBonus;
};

#endif // __EFFECT_DANCING_SWORD__
