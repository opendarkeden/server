//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMephisto.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_MEPHISTO__
#define __EFFECT_MEPHISTO__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectMephisto
//////////////////////////////////////////////////////////////////////////////

class EffectMephisto : public Effect 
{
public:
	EffectMephisto(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_MEPHISTO; }

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

#endif // __EFFECT_MEPHISTO__
