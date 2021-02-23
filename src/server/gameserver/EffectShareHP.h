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
	EffectShareHP(Creature* pCreature) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_SHARE_HP; }

	void affect() throw(Error);
	void affect(Creature* pCreature) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error);
	void unaffect(Item* pItem) throw(Error) {}
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	string toString() const throw();

	list<ObjectID_t>&		getSharingCreatures() { return m_SharingCreatures; }
	const list<ObjectID_t>&	getSharingCreatures() const { return m_SharingCreatures; }

private:
	list<ObjectID_t>	m_SharingCreatures;
};

#endif // __EFFECT_SHARE_HP__
