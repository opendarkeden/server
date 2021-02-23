//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBloodySnake.h
// Written by  : elca@ewestsoft.com
// Description : 성직마법 BloodySnake의 Effect를 처리해주기 위한 클래스이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BLOODY_SNAKE__
#define __EFFECT_BLOODY_SNAKE__

#include "Effect.h"
#include "EffectLoader.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBloodySnake
//////////////////////////////////////////////////////////////////////////////

class EffectBloodySnake : public Effect 
{
public:
	EffectBloodySnake(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_BLOODY_SNAKE; }

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

	int getDamage(void) const { return m_Damage; }
	void setDamage(int damage) { m_Damage = damage; }

	Turn_t getTick() const { return m_Tick; }
	void setTick(Turn_t Tick) { m_Tick = Tick; }

	int getLevel(void) const { return m_Level; }
	void setLevel(int level) { m_Level = level; }

	Dir_t getDir(void) const { return m_Dir; }
	void setDir(int dir) { m_Dir = dir; }

	void setClan(Creature::CreatureClass clanType, int clanID) { m_CreatureClass=clanType; m_ClanID=clanID; }
	Creature::CreatureClass getCreatureClass() const	{ return m_CreatureClass; }
	int getClanID() const			{ return m_ClanID; }

	POINT getNextPosition();

private:
	string m_CasterName;
	ObjectID_t  m_CasterID;
	Dir_t   m_Dir;
	int     m_Damage;
	Turn_t  m_Tick;
	int     m_Level;
	Creature::CreatureClass m_CreatureClass;
	int      m_ClanID;
};

//////////////////////////////////////////////////////////////////////////////
// class EffectBloodySnakeLoader
//////////////////////////////////////////////////////////////////////////////

class EffectBloodySnakeLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_BLOODY_SNAKE; }
	virtual string getEffectClassName() const throw() { return "EffectBloodySnake"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};

extern EffectBloodySnakeLoader* g_pEffectBloodySnakeLoader;

#endif // __EFFECT_BLOODY_SNAKE__
