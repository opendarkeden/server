//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMiracleShield.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_MIRACLE_SHIELD__
#define __EFFECT_MIRACLE_SHIELD__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectMiracleShield
//////////////////////////////////////////////////////////////////////////////

class EffectMiracleShield : public Effect 
{
public:
	EffectMiracleShield(Creature* pCreature) throw(Error);

public:
	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_MIRACLE_SHIELD; }

	string toString() const throw();

public:
	int getDefenseBonus() throw() { return m_DefenseBonus;}
	void setDefenseBonus(Defense_t DefenseBonus) throw(Error) { m_DefenseBonus = DefenseBonus;}

	int getProtectionBonus() throw() { return m_ProtectionBonus;}
	void setProtectionBonus(Protection_t ProtectionBonus) throw(Error) { m_ProtectionBonus = ProtectionBonus;}

private :
	Defense_t    m_DefenseBonus;
	Protection_t m_ProtectionBonus;
};

#endif // __EFFECT_MIRACLE_SHIELD__
