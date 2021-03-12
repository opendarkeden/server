//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectPeace.h
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_PEACE__
#define __EFFECT_PEACE__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectPeace
//////////////////////////////////////////////////////////////////////////////

class EffectPeace : public Effect 
{
public:
	// pCreature(나)가 pPeaceCreature한테 peace상태를 유지한다.
	EffectPeace(Creature* pCreature, ObjectID_t PeaceCreatureID) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_PEACE; }

	void affect() {}
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect() ;
	void unaffect(Creature* pCreature) ;
	void unaffect(Item*  pItem)  {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	string toString() const throw();
	
public:
	ObjectID_t getPeaceCreatureID() const throw() { return m_PeaceCreatureID; }
	void setPeaceCreatureID(ObjectID_t PeaceCreatureID) throw() { m_PeaceCreatureID = PeaceCreatureID; }

private:
	ObjectID_t m_PeaceCreatureID;

};

#endif // __EFFECT_YELLOW_POISON_TO_CREATURE__
