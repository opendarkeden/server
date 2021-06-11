//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPenetrateWheel.h
// Written by  : rallser
// Description : 성직마법PenetrateWheel의 Effect를 처리해주기 위한 클래스이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_Penetrate_Wheel__
#define __EFFECT_Penetrate_Wheel__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectPenetrateWheel
//////////////////////////////////////////////////////////////////////////////

class EffectPenetrateWheel : public Effect 
{
public:
	EffectPenetrateWheel(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_PROMINENCE; }

	void affect() ;
	void unaffect() ;
	string toString() const throw();

public:
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
	int     m_Damage;
	Turn_t  m_Tick;
	int     m_Level;
	bool	m_bForce;

	ObjectID_t	m_UserObjectID;
};

#endif // __EFFECT_Penetrate_Wheel__
