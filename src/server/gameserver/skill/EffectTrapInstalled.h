//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectTrapInstalled.h
// Written by  : bezz
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_TRAP_INSTALLED__
#define __EFFECT_TRAP_INSTALLED__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectTrapInstalled
//////////////////////////////////////////////////////////////////////////////

class EffectTrapInstalled : public Effect 
{
public:
	EffectTrapInstalled(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_TRAP_INSTALLED; }

	void affect() ;
	void affect(Zone* pZone, ZoneCoord_t X, ZoneCoord_t Y) ;
	void affect(Creature* pCreature) ;

	void unaffect() ;

	string toString() const throw();

public:

	void setTick(Turn_t tick) { m_Tick = tick; }
	Turn_t getTick() const { return m_Tick; }

	void setUserOID( ObjectID_t oid ) { m_UserOID = oid; }
	ObjectID_t getUserOID() const { return m_UserOID; }

private:

	Turn_t m_Tick;
	ObjectID_t m_UserOID;
};

#endif
