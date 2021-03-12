//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectWillOfLife.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_WILL_OF_LIFE__
#define __EFFECT_WILL_OF_LIFE__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectWillOfLife
//////////////////////////////////////////////////////////////////////////////

class EffectWillOfLife : public Effect 
{
public:
	EffectWillOfLife(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_WILL_OF_LIFE; }

	void affect() ;
	void affect(Creature* pCreature) ;

	void unaffect(Creature* pCreature) ;
	void unaffect() ; 

	string toString() const throw();

public:
	int getBonus() throw() { return m_Bonus;}
	void setBonus(int Bonus)  { m_Bonus = Bonus;}

private:
	int m_Bonus;
};

#endif // __EFFECT_WILL_OF_LIFE__
