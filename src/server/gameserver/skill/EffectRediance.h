//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRediance.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_REDIANCE__
#define __EFFECT_REDIANCE__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectRediance
//////////////////////////////////////////////////////////////////////////////

class EffectRediance : public Effect 
{
public:
	EffectRediance(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_REDIANCE; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	int getDexBonus() throw() { return m_DexBonus;}
	void setDexBonus(Attr_t DexBonus) throw(Error) { m_DexBonus = DexBonus;}

	bool canGiveExp() { return m_GiveExp=!m_GiveExp; }

private :
	Attr_t m_DexBonus;
	bool m_GiveExp;
};

#endif // __EFFECT_REDIANCE__
