//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDragonTornado.h
// Written by  : elca@ewestsoft.com
// Description : 성직마법 DragonTornado의 Effect를 처리해주기 위한 클래스이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DRAGON_TORNADO__
#define __EFFECT_DRAGON_TORNADO__

#include "Effect.h"
#include "EffectLoader.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDragonTornado
//////////////////////////////////////////////////////////////////////////////

class EffectDragonTornado : public Effect 
{
public:
	EffectDragonTornado(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DRAGON_TORNADO; }
	EffectClass getSendEffectClass() const throw() { return (m_bCanSplit)?EFFECT_CLASS_DRAGON_TORNADO:EFFECT_CLASS_DRAGON_TORNADO_CHILD; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() const throw();

public:
	ObjectID_t getUserOID(void) const { return m_UserOID; }
	void setUserOID(ObjectID_t UserOID) { m_UserOID = UserOID; }

	Damage_t	getDamage() const { return m_Damage; }
	void		setDamage(Damage_t damage) { m_Damage = damage; }

	Damage_t	getChildDamage() const { return m_ChildDamage; }
	void		setChildDamage(Damage_t damage) { m_ChildDamage = damage; }

	bool		canSplit() const { return m_bCanSplit; }
	void		setSplit(bool split) { m_bCanSplit = split; }

private:
	ObjectID_t  m_UserOID;
	Damage_t	m_Damage;
	Damage_t	m_ChildDamage;
	bool		m_bCanSplit;
};

#endif // __EFFECT_DRAGON_TORNADO__
