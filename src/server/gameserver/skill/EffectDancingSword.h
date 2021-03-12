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
	EffectDancingSword(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DANCING_SWORD; }

	void affect()  {}
	void affect(Creature* pCreature) ;

	void unaffect(Creature* pCreature) ;
	void unaffect() ; 

	string toString() const throw();

public:
	int getToHitBonus() throw() { return m_ToHitBonus;}
	void setToHitBonus(ToHit_t ToHitBonus)  { m_ToHitBonus = ToHitBonus;}

private :
	ToHit_t m_ToHitBonus;
};

#endif // __EFFECT_DANCING_SWORD__
