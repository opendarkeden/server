//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectArmageddon.h
// Written by  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_ARMAGEDDON__
#define __EFFECT_ARMAGEDDON__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectArmageddon
//////////////////////////////////////////////////////////////////////////////

class EffectArmageddon : public Effect 
{
public:
	EffectArmageddon(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_ARMAGEDDON; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error);

	string toString() const throw();

public:
//	string getCasterName(void) const { return m_CasterName; }
//	void setCasterName(const string & CasterName ) { m_CasterName = CasterName; }

//	int getPartyID(void) const { return m_PartyID; }
//	void setPartyID(int PartyID) { m_PartyID = PartyID; }

	ObjectID_t getUserObjectID() const { return m_UserObjectID; }
	void setUserObjectID( ObjectID_t UserObjectID ) { m_UserObjectID = UserObjectID; }

	HP_t getHP() const { return m_HP; }
	void setHP( HP_t hp ) { m_HP = hp; }
	void decreaseHP( Damage_t damage ) throw();

	Damage_t getDamage() const { return m_Damage; }
	void setDamage( Damage_t damage ) { m_Damage = damage; }

	Turn_t getDelay() const { return m_Delay; }
	void setDelay( Turn_t delay ) { m_Delay = delay; }

private:
	ObjectID_t	m_UserObjectID;	// 시전자 Object ID
//	string		m_CasterName;	// 시전자
//	int			m_PartyID;		// 파티ID

	HP_t		m_HP;			// 체력
	Damage_t	m_Damage;		// 데미지
	Turn_t		m_Delay;		// Tick
};

//////////////////////////////////////////////////////////////////////////////
// class EffectArmageddonLoader
//////////////////////////////////////////////////////////////////////////////

class EffectArmageddonLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_ARMAGEDDON; }
	virtual string getEffectClassName() const throw() { return "EffectArmageddon"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};


#endif // __EFFECT_ARMAGEDDON__
