//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMagnumSpear.h
// Written by  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_MAGNUM_SPEAR__
#define __EFFECT_MAGNUM_SPEAR__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectMagnumSpear
//////////////////////////////////////////////////////////////////////////////

class EffectMagnumSpear : public Effect 
{
public:
	EffectMagnumSpear(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_MAGNUM_SPEAR; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	Damage_t	getDamage() const { return m_Damage; }
	void		setDamage( Damage_t Damage ) { m_Damage = Damage; }
	
	int			getTimes() const { return m_Times; }
	void		setTimes( int Times ) { m_TotalTimes = m_Times = Times; }

	Turn_t		getTick() const { return m_Tick; }
	void		setTick( Turn_t Tick ) { m_Tick = Tick; }

	ObjectID_t	getCasterOID() const { return m_CasterOID; }
	void		setCasterOID( ObjectID_t CasterOID ) { m_CasterOID = CasterOID; }
	
private:
	Damage_t	m_Damage;
	int			m_Times;
	int			m_TotalTimes;
	Turn_t		m_Tick;
	ObjectID_t	m_CasterOID;

};

#endif // __EFFECT_MAGNUM_SPEAR__
