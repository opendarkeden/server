#ifndef __EFFECT_POISON_STORM__
#define __EFFECT_POISON_STORM__

#include "Effect.h"
#include "EffectLoader.h"

class EffectPoisonStorm : public Effect
{
public:
	EffectPoisonStorm(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) throw(Error);

	EffectClass getEffectClass() const throw() { return EFFECT_CLASS_POISON_STORM; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	string toString() const throw();

public:
	int getDamage(void) const { return m_Damage; }
	void setDamage(int damage) { m_Damage = damage; }

	Turn_t getTick() const { return m_Tick; }
	void setTick(Turn_t Tick) { m_Tick = Tick; }

	int getLevel(void) const { return m_Level; }
	void setLevel(int level) { m_Level = level; }

	void setUserObjectID(ObjectID_t oid) throw() { m_UserObjectID = oid; }
	ObjectID_t getUserObjectID() const throw() { return m_UserObjectID; }

	void setVampire( bool bVampire = true ) { m_bVampire = bVampire; }
	bool isVampire() const { return m_bVampire; }

	bool affectCreature(Creature* pCreature, bool bAffectByMove) throw(Error); 
private:
	int 	 	m_Damage;  	    // EffectPoisonStorm Damage;
	Turn_t 		m_Tick;			// EffectPoisonStorm turn;	
	int 		m_Level;		// EffectPoisonStorm level;
	Duration_t 	m_Duration;		// EffectPoisonStorm Duration;
	Duration_t  m_StormDuration; // PoisonStorm Effect 지속 시간 
	ObjectID_t	m_UserObjectID;
	bool		m_bVampire;
};

class EffectPoisonStormLoader : public EffectLoader
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_POISON_STORM; }
	virtual string getEffectClassName() const throw() { return "EffectPoisonStorm"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};

extern EffectPoisonStormLoader* g_pEffectPoisonStormLoader;

#endif
