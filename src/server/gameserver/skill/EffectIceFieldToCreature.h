//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectIceFieldToCreature.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ICE_FIELD_TO_CREATURE__
#define __EFFECT_ICE_FIELD_TO_CREATURE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectIceFieldToCreature
//////////////////////////////////////////////////////////////////////////////

class EffectIceFieldToCreature : public Effect 
{
public:
	EffectIceFieldToCreature(Creature* pCreature, bool byFrozenArmor = false) throw(Error);

public:
	EffectClass getEffectClass() const throw() { return EFFECT_CLASS_ICE_FIELD_TO_CREATURE; }
	EffectClass getSendEffectClass() const throw() { return (m_bFrozenArmor)?EFFECT_CLASS_FROZEN_ARMOR_TO_ENEMY:EFFECT_CLASS_ICE_FIELD_TO_CREATURE; }

	void affect() throw(Error){}

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	string toString() const throw();

private:
	bool	m_bFrozenArmor;
};

#endif // __EFFECT_ICE_FIELD_TO_CREATURE__
