//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectWhitsuntide.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_WHITSUNTIDE__
#define __EFFECT_WHITSUNTIDE__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectWhitsuntide
//////////////////////////////////////////////////////////////////////////////

class EffectWhitsuntide : public Effect 
{
public:
	EffectWhitsuntide(Creature* pCreature) throw(Error);

public:
	EffectClass getEffectClass() const throw() { return EFFECT_CLASS_WHITSUNTIDE; }

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

	int getBonus() const { return m_Bonus; }
	void setBonus(int bonus) { m_Bonus = bonus; }

private :
	int m_Bonus;
};

#endif // __EFFECT_WHITSUNTIDE__
