//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectProminence.h
// Written by  : elca@ewestsoft.com
// Description : 성직마법 Prominence의 Effect를 처리해주기 위한 클래스이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PROMINENCE__
#define __EFFECT_PROMINENCE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectProminence
//////////////////////////////////////////////////////////////////////////////

class EffectProminence : public Effect 
{
public:
	EffectProminence(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_PROMINENCE; }
	EffectClass getSendEffectClass() const throw() { return m_SendEffectClass; }

	void affect() throw(Error);
	void unaffect() throw(Error);
	string toString() const throw();

public:
	void setSendEffectClass(EffectClass eClass) throw() { m_SendEffectClass = eClass; }

	int getDamage(void) const { return m_Damage; }
	void setDamage(int damage) { m_Damage = damage; }

	Turn_t getTick() const { return m_Tick; }
	void setTick(Turn_t Tick) { m_Tick = Tick; }

	int getLevel(void) const { return m_Level; }
	void setLevel(int level) { m_Level = level; }

	void setForce( bool force ) { m_bForce = force; }
	bool isForce() const { return m_bForce; }

	ObjectID_t getUserObjectID() const { return m_UserObjectID; }
	void setUserObjectID( ObjectID_t UserObjectID ) { m_UserObjectID = UserObjectID; }

private:
	EffectClass m_SendEffectClass;
	int     m_Damage;
	Turn_t  m_Tick;
	int     m_Level;
	bool	m_bForce;

	ObjectID_t	m_UserObjectID;
};

class EffectProminenceLoader : public EffectLoader
{

public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_PROMINENCE; }
	virtual string getEffectClassName() const throw() { return "EffectProminence"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
	virtual void load(Zone* pZone) throw(Error);
};

extern EffectProminenceLoader* g_pEffectProminenceLoader;

#endif // __EFFECT_PROMINENCE__
