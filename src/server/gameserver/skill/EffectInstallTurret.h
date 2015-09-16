//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectInstallTurret.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_INSTALL_TURRET__
#define __EFFECT_INSTALL_TURRET__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectInstallTurret
//////////////////////////////////////////////////////////////////////////////

class EffectInstallTurret : public Effect 
{
public:
	EffectInstallTurret(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_INSTALL_TURRET; }

	void affect() throw(Error) {}
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	int getDamage(void) const { return m_Damage; }
	void setDamage(int bonus) { m_Damage = bonus; }

	int getDefense(void) const { return m_Defense; }
	void setDefense(int bonus) { m_Defense = bonus; }

private :
	int m_Damage;
	int m_Defense;
};

#endif // __EFFECT_INSTALL_TURRET__
