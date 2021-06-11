//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHarpoonBomb.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HARPOON_BOMB__
#define __EFFECT_HARPOON_BOMB__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHarpoonBomb
//////////////////////////////////////////////////////////////////////////////

class EffectHarpoonBomb : public Effect 
{
public:
	EffectHarpoonBomb(Creature* pCreature) ;
	EffectHarpoonBomb(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_HARPOON_BOMB; }

	void affect() ;
	void crash(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y);

	void unaffect() ;

	string toString() const throw();

public:
	Damage_t getDamage() const throw() { return m_Damage; }
	void setDamage(Damage_t Damage) throw() { m_Damage = Damage; }

	void setUserObjectID(ObjectID_t oid) throw() { m_UserObjectID = oid; }
	ObjectID_t getUserObjectID() const throw() { return m_UserObjectID; }

private:
	Damage_t    m_Damage;
	ObjectID_t m_UserObjectID;
};

#endif // __EFFECT_HARPOON_BOMB__
