//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectRapidFreeze.h
// Written by  : rallser
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_Rapid_Freeze__
#define __EFFECT_Rapid_Freeze__

#include "Effect.h"
#include <unordered_map>

//////////////////////////////////////////////////////////////////////////////
// class EffectRapidFreeze
//////////////////////////////////////////////////////////////////////////////

class EffectRapidFreeze : public Effect 
{
public:
	EffectRapidFreeze(Zone* pZone, ZoneCoord_t zoneX, ZoneCoord_t zoneY) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_Rapid_Freeze; }

	void affect() ;
	void unaffect() ;
	string toString() const throw();

public:
	int getDamage(void) const { return m_Damage; }
	void setDamage(int damage) { m_Damage = damage; }

	ObjectID_t getUserObjectID() const { return m_UserObjectID; }
	void setUserObjectID( ObjectID_t UserObjectID ) { m_UserObjectID = UserObjectID; }

	void checkPosition();

private:
	int     						m_Damage;
	ObjectID_t						m_UserObjectID;
	unordered_map<ObjectID_t, TPOINT>	m_TargetPositions;
};

#endif // __EFFECT_Rapid_Freeze__
