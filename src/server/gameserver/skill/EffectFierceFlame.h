//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectFierceFlame.h
// Written by  : elca@ewestsoft.com
// Description : 성직마법 FierceFlame의 Effect를 처리해주기 위한 클래스이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_FIRECE_FLAME__
#define __EFFECT_FIRECE_FLAME__

#include "Effect.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectFierceFlame
//////////////////////////////////////////////////////////////////////////////

class EffectFierceFlame : public Effect 
{
public:
	EffectFierceFlame(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_FIERCE_FLAME; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() const throw();

public:
	ObjectID_t getUserOID(void) const { return m_UserOID; }
	void setUserOID(ObjectID_t UserOID ) { m_UserOID = UserOID; }

	Damage_t getDamage(void) const { return m_Damage; }
	void setDamage(Damage_t Damage ) { m_Damage = Damage; }

	Turn_t getDuration(void) const { return m_Duration; }
	void setDuration(Turn_t Duration ) { m_Duration = Duration; }

private:
	ObjectID_t  			m_UserOID;
	Damage_t				m_Damage;
	Turn_t					m_Duration;
};

#endif // __EFFECT_FIRECE_FLAME__
