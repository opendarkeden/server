//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectSharpChakram.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SHARP_CHAKRAM__
#define __EFFECT_SHARP_CHAKRAM__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectSharpChakram
//////////////////////////////////////////////////////////////////////////////

class EffectSharpChakram : public Effect 
{
public:
	EffectSharpChakram(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SHARP_CHAKRAM; }

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

#endif // __EFFECT_SHARP_CHAKRAM__
