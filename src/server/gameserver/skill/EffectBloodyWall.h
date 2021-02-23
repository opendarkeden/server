//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBloodyWall.h
// Written by  : elca@ewestsoft.com
// Description : 성직마법 BloodyWall의 Effect를 처리해주기 위한 클래스이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BLOODY_WALL__
#define __EFFECT_BLOODY_WALL__

#include "Effect.h"
#include "EffectLoader.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBloodyWall
//////////////////////////////////////////////////////////////////////////////

class EffectBloodyWall : public Effect 
{
public:
	EffectBloodyWall(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_BLOODY_WALL; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	string toString() const throw();

public:
	string getCasterName(void) const { return m_CasterName; }
	void setCasterName(const string& CasterName ) { m_CasterName = CasterName; }

	ObjectID_t getCasterID(void) const { return m_CasterID; }
	void setCasterID(ObjectID_t CasterID ) { m_CasterID = CasterID; }

	int getPartyID(void) const { return m_PartyID; }
	void setPartyID(int PartyID) { m_PartyID = PartyID; }

	int getDamage(void) const { return m_Damage; }
	void setDamage(int damage) { m_Damage = damage; }

	Turn_t getTick() const { return m_Tick; }
	void setTick(Turn_t Tick) { m_Tick = Tick; }

	int getLevel(void) const { return m_Level; }
	void setLevel(int level) { m_Level = level; }

	void setClan(Creature::CreatureClass clanType, int clanID) { m_CreatureClass=clanType; m_ClanID=clanID; }
	Creature::CreatureClass getCreatureClass() const	{ return m_CreatureClass; }
	int getClanID() const			{ return m_ClanID; }

	void setForce( bool force ) throw(Error) { m_bForce = force; }
	bool isForce() const throw(Error) { return m_bForce; }

private:
	string m_CasterName;
	ObjectID_t  m_CasterID;
	int	    m_PartyID;
	int     m_Damage;
	Turn_t  m_Tick;
	int     m_Level;
	Creature::CreatureClass m_CreatureClass;
	int      m_ClanID;

	bool	m_bForce;
};

/*
//////////////////////////////////////////////////////////////////////////////
// class EffectBloodyWallLoader
//////////////////////////////////////////////////////////////////////////////

class EffectBloodyWallLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_BLOODY_WALL; }
	virtual string getEffectClassName() const throw() { return "EffectBloodyWall"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
	virtual void load(Zone* pZone) throw(Error); 
};

extern EffectBloodyWallLoader* g_pEffectBloodyWallLoader;
*/

#endif // __EFFECT_BLOODY_WALL__
