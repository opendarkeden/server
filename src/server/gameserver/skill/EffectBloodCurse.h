//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectBloodCurse.h
// Written by  : elca@ewestsoft.com
// Description : 성직마법 BloodCurse의 Effect를 처리해주기 위한 클래스이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_BLOOD_CURSE__
#define __EFFECT_BLOOD_CURSE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectBloodCurse
//////////////////////////////////////////////////////////////////////////////

class EffectBloodCurse : public Effect 
{
public:
	EffectBloodCurse(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY, bool bPlayer = false) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_BLOOD_CURSE; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);

	string toString() const throw();

public:
	int getDamage(void) const { return m_Damage; }
	void setDamage(int damage) { m_Damage = damage; }

	Turn_t getDelay() const { return m_Delay; }
	void setDelay(Turn_t Delay) { m_Delay = Delay; }

//	string getCasterName(void) const { return m_CasterName; }
//	void setCasterName(const string & CasterName ) { m_CasterName = CasterName; }

	ObjectID_t getUserObjectID(void) const { return m_UserObjectID; }
	void setUserObjectID(ObjectID_t UserObjectID ) { m_UserObjectID = UserObjectID; }

	void setSplashRatio(int index, uint ratio) { m_SplashRatio[index] = ratio; }

private:
	int     m_Damage;
	Turn_t  m_Delay;
//	string  m_CasterName;
	ObjectID_t   m_UserObjectID;
	bool	m_bPlayer;			// 유저가 사용한 기술인가?
	uint	m_SplashRatio[3];
};

//////////////////////////////////////////////////////////////////////////////
// class EffectBloodCurseLoader
//////////////////////////////////////////////////////////////////////////////

class EffectBloodCurseLoader : public EffectLoader 
{
public:
	virtual Effect::EffectClass getEffectClass() const throw() { return Effect::EFFECT_CLASS_BLOOD_CURSE; }
	virtual string getEffectClassName() const throw() { return "EffectBloodCurse"; }

public:
	virtual void load(Creature* pCreature) throw(Error) {}
};

extern EffectBloodCurseLoader* g_pEffectBloodCurseLoader;

#endif // __EFFECT_BLOOD_CURSE__
