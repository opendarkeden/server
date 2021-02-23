//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGroundBless.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GROUND_BLESS__
#define __EFFECT_GROUND_BLESS__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGroundBless
//////////////////////////////////////////////////////////////////////////////

class EffectGroundBless : public Effect 
{
public:
	EffectGroundBless(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_GROUND_BLESS; }

	void affect() throw(Error){}

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	string toString() const throw();

public:
	void setBonus( uint bonus ) { m_Bonus = bonus; }
	uint getBonus() const { return m_Bonus; }

private:
	uint	m_Bonus;
};

#endif // __EFFECT_GROUND_BLESS__
