//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBurningSolCharging.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BURNING_SOL_CHARGE__
#define __EFFECT_BURNING_SOL_CHARGE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBurningSolCharging
//////////////////////////////////////////////////////////////////////////////

class EffectBurningSolCharging : public Effect 
{
public:
	EffectBurningSolCharging(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_BURNING_SOL_CHARGE_1; }
	EffectClass getSendEffectClass() const throw() { return (EffectClass)(EFFECT_CLASS_BURNING_SOL_CHARGE_1 + m_Level); }

	void affect() ;
	void affect(Creature* pCreature) ;
	void unaffect(Creature* pCreature) ;
	void unaffect() ;

	string toString() const throw();

public:
	Level_t getLevel() const throw() { return m_Level; }
	void setLevel(Level_t Level) throw() { m_Level = Level; }

private:
	Level_t 		m_Level;				// 스킬 레벨
};

#endif // __EFFECT_BURNING_SOL_CHARGE__
