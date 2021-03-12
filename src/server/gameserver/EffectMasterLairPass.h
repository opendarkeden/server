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
	EffectMasterLairPass(Creature* pCreature, ZoneID_t zoneID) ;

public:
    EffectClass getEffectClass() const  { return EFFECT_CLASS_MASTER_LAIR_PASS; }

	void affect() ;
	void affect(Creature* pCreature) ;

	void unaffect(Creature* pCreature) ;
	void unaffect() ; 

	string toString() const ;

public:
	ZoneID_t    getZoneID(void) const { return m_ZoneID; }
	void   setZoneID(ZoneID_t zoneID)  { m_ZoneID = zoneID; }

private:
	ZoneID_t m_ZoneID; 
};

#endif
