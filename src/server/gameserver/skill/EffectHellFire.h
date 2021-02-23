//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectHellFire.h
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_HELLFIRE__
#define __EFFECT_HELLFIRE__

#include "Effect.h"
#include "EffectLoader.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectHellFire
//////////////////////////////////////////////////////////////////////////////

class EffectHellFire : public Effect 
{
public:
	EffectHellFire(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_HELLFIRE; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() const throw();

public:
	string getCasterName(void) const { return m_CasterName; }
	void setCasterName(const string& CasterName ) { m_CasterName = CasterName; }

	ObjectID_t getCasterID(void) const { return m_CasterID; }
	void setCasterID(ObjectID_t CasterID ) { m_CasterID = CasterID; }

	Turn_t getTick() const { return m_Tick; }
	void setTick(Turn_t Tick) { m_Tick = Tick; }

	int getDuration(void) const { return m_Duration; }
	void setDuration(int dur) { m_Duration = dur; }

	bool isForce(void) const { return m_bForce; }
	void setForce(bool force) { m_bForce = force; }

	Damage_t    getDamage() const { return m_Damage; }
	void        setDamage( Damage_t Damage ) { m_Damage = Damage; }

private:
	string 			m_CasterName;
	ObjectID_t  	m_CasterID;
	Turn_t  		m_Tick;
	int     		m_Duration;
	bool			m_bForce;
	Damage_t		m_Damage;
};

class EffectHellFireLoader : public EffectLoader
{

public:
    virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_HELLFIRE; }
    virtual string getEffectClassName() const throw() { return "EffectHellFire"; }

public:
    virtual void load(Creature* pCreature) throw(Error) {}
};

extern EffectHellFireLoader* g_pEffectHellFireLoader;


#endif // __EFFECT_HELLFIRE__
