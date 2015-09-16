//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectStoneSkin.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_STONE_SKIN__
#define __EFFECT_STONE_SKIN__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectStoneSkin
//////////////////////////////////////////////////////////////////////////////

class EffectStoneSkin : public Effect 
{
public:
	EffectStoneSkin(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_STONE_SKIN; }

	void affect() throw(Error) {}
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

#endif // __EFFECT_STONE_SKIN__
