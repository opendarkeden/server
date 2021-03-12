//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectGreenStalker.h
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_GREEN_STALKER__
#define __EFFECT_GREEN_STALKER__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectGreenStalker
//////////////////////////////////////////////////////////////////////////////

class EffectGreenStalker : public Effect 
{
public:
	EffectGreenStalker(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_GREEN_STALKER; }

	void affect() ;
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect() ;
	void unaffect(Creature* pCreature) ;
	void unaffect(Item* pItem)  {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	string toString() const throw();

public:
	HP_t getDamage() const throw() { return m_Damage; }
	void setDamage(HP_t Damage) throw() { m_Damage = Damage; }

	void setTick(Turn_t Tick) throw() { m_Tick = Tick; }
	Turn_t getTick() const throw() { return m_Tick; }

	Level_t getLevel() const throw() { return m_Level; }
	void setLevel(Level_t Level) throw() { m_Level = Level; }

	void setUserObjectID(ObjectID_t oid) throw() { m_UserObjectID = oid; }
	ObjectID_t getUserObjectID() const throw() { return m_UserObjectID; }

	void setVampire( bool bVampire = true ) { m_bVampire = bVampire; }
	bool isVampire() const { return m_bVampire; }

private:
	Level_t  m_Level;
	HP_t     m_Damage;
	Turn_t   m_Tick;
	ObjectID_t	m_UserObjectID;
	bool		m_bVampire;
};

#endif // __EFFECT_GREEN_STALKER__
