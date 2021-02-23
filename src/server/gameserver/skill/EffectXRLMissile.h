//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectXRLMissile.h
// Written by  : rallser
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_XRL_Missile__
#define __EFFECT_XRL_Missile__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class XRLMissile
//////////////////////////////////////////////////////////////////////////////

class EffectXRLMissile : public Effect 
{
public:
	EffectXRLMissile(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_XRL_Missile; }

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

#endif // __EFFECT_XRLMissile
