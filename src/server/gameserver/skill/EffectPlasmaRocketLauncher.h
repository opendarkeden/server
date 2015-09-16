//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPlasmaRocketLauncher.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PLASMA_ROCKET_LAUNCHER__
#define __EFFECT_PLASMA_ROCKET_LAUNCHER__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectPlasmaRocketLauncher
//////////////////////////////////////////////////////////////////////////////

class EffectPlasmaRocketLauncher : public Effect 
{
public:
	EffectPlasmaRocketLauncher(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_PLASMA_ROCKET_LAUNCHER; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect() throw(Error);
	string toString() const throw();

public:
	HP_t getPoint() const throw() { return m_Point; }
	void setPoint(HP_t Point) throw() { m_Point = Point; }

	void setUserObjectID(ObjectID_t oid) throw() { m_UserObjectID = oid; }
	ObjectID_t getUserObjectID() const throw() { return m_UserObjectID; }

private:
	HP_t    m_Point;
	ObjectID_t m_UserObjectID;
};

#endif // __EFFECT_PLASMA_ROCKET_LAUNCHER__
