//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectIceField.h
// Written by  : elca@ewestsoft.com
// Description : 성직마법 IceField의 Effect를 처리해주기 위한 클래스이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ICE_FIELD__
#define __EFFECT_ICE_FIELD__

#include "Effect.h"
#include "EffectLoader.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectIceField
//////////////////////////////////////////////////////////////////////////////

class EffectIceField : public Effect 
{
public:
	EffectIceField(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_ICE_FIELD; }

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

private:
	string m_CasterName;
	ObjectID_t  m_CasterID;
	Turn_t  m_Tick;
	int     m_Duration;
	bool	m_bForce;
};

class EffectIceFieldLoader : public EffectLoader
{

public:
    virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_ICE_FIELD; }
    virtual string getEffectClassName() const throw() { return "EffectIceField"; }

public:
    virtual void load(Creature* pCreature) throw(Error) {}
    virtual void load(Zone* pZone) throw(Error);
};

extern EffectIceFieldLoader* g_pEffectIceFieldLoader;


#endif // __EFFECT_ICE_FIELD__
