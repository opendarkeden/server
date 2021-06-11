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
	EffectMiracleShield(Creature* pCreature) ;

public:
	void affect()  {}
	void affect(Creature* pCreature) ;

	void unaffect(Creature* pCreature) ;
	void unaffect() ; 

    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_MIRACLE_SHIELD; }

	string toString() const throw();

public:
	int getDefenseBonus() throw() { return m_DefenseBonus;}
	void setDefenseBonus(Defense_t DefenseBonus)  { m_DefenseBonus = DefenseBonus;}

	int getProtectionBonus() throw() { return m_ProtectionBonus;}
	void setProtectionBonus(Protection_t ProtectionBonus)  { m_ProtectionBonus = ProtectionBonus;}

private :
	Defense_t    m_DefenseBonus;
	Protection_t m_ProtectionBonus;
};

#endif // __EFFECT_MIRACLE_SHIELD__
