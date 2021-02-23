//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBlindness.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BLINDNESS__
#define __EFFECT_BLINDNESS__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBlindness
//////////////////////////////////////////////////////////////////////////////

class EffectBlindness : public Effect 
{
public:
	EffectBlindness(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_BLINDNESS; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() const throw();

public:
	void		setDamage( Damage_t damage ) { m_Damage = damage; }
	Damage_t	getDamage() const { return m_Damage; }

private:
	Damage_t	m_Damage;
};

#endif // __EFFECT_BLINDNESS__
