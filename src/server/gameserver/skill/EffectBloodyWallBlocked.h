//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBloodyWallBlocked.h
// Written by  : elca@ewestsoft.com
// Description : 성직마법 BloodyWallBlocked의 Effect를 처리해주기 위한 클래스이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BLOODY_WALL_BLOCKED__
#define __EFFECT_BLOODY_WALL_BLOCKED__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBloodyWallBlocked
//////////////////////////////////////////////////////////////////////////////

class EffectBloodyWallBlocked : public Effect 
{
public:
	EffectBloodyWallBlocked(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_BLOODY_WALL_BLOCKED; }

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
	void setCasterName(const string & CasterName ) { m_CasterName = CasterName; }

	int getPartyID(void) const { return m_PartyID; }
	void setPartyID(int PartyID) { m_PartyID = PartyID; }

	int getDamage(void) const { return m_Damage; }
	void setDamage(int damage) { m_Damage = damage; }

	Turn_t getTick() const { return m_Tick; }
	void setTick(Turn_t Tick) { m_Tick = Tick; }

	int getLevel(void) const { return m_Level; }
	void setLevel(int level) { m_Level = level; }

private:
	string  m_CasterName;
	int	    m_PartyID;
	int     m_Damage;
	Turn_t  m_Tick;
	int     m_Level;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectBloodyWallBlockedLoader
//////////////////////////////////////////////////////////////////////////////

class EffectBloodyWallBlockedLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_BLOODY_WALL_BLOCKED; }
	virtual string getEffectClassName() const throw() { return "EffectBloodyWallBlocked"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};

extern EffectBloodyWallBlockedLoader* g_pEffectBloodyWallBlockedLoader;

#endif // __EFFECT_BLOODY_WALL_BLOCKED__
