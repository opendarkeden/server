//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectShareHP.h
// Written by  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_SHARE_HP__
#define __EFFECT_SHARE_HP__

#include "Effect.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
// class EffectShareHP
//////////////////////////////////////////////////////////////////////////////

class EffectShareHP : public Effect 
{
public:
	EffectShareHP(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const  { return EFFECT_CLASS_SHARE_HP; }

	void affect() ;
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect() ;
	void unaffect(Creature* pCreature) ;
	void unaffect(Item* pItem)  {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	string toString() const ;

	list<ObjectID_t>&		getSharingCreatures() { return m_SharingCreatures; }
	const list<ObjectID_t>&	getSharingCreatures() const { return m_SharingCreatures; }

private:
	list<ObjectID_t>	m_SharingCreatures;
};

#endif // __EFFECT_SHARE_HP__
