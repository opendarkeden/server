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
	EffectWillOfLife(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_WILL_OF_LIFE; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	int getBonus() throw() { return m_Bonus;}
	void setBonus(int Bonus) throw(Error) { m_Bonus = Bonus;}

private:
	int m_Bonus;
};

#endif // __EFFECT_WILL_OF_LIFE__
