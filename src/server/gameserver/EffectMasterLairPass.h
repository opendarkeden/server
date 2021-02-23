//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectMasterLairPass.h
// Written by  : 
// Description : ZoneID 마스터 레어 출입증
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_MASTER_LAIR_PASS__
#define __EFFECT_MASTER_LAIR_PASS__

#include "Effect.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectMasterLairPass
//////////////////////////////////////////////////////////////////////////////

class EffectMasterLairPass : public Effect 
{
public:
	EffectMasterLairPass(Creature* pCreature, ZoneID_t zoneID) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_MASTER_LAIR_PASS; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);
	void unaffect() throw(Error); 

	string toString() const throw();

public:
	ZoneID_t    getZoneID(void) const { return m_ZoneID; }
	void   setZoneID(ZoneID_t zoneID) throw() { m_ZoneID = zoneID; }

private:
	ZoneID_t m_ZoneID; 
};

#endif
