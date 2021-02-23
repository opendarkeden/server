//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectStriking.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_STRIKING__
#define __EFFECT_STRIKING__

#include "Effect.h"
#include "EffectLoader.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectStriking
//////////////////////////////////////////////////////////////////////////////

class EffectStriking : public Effect 
{
public:
	EffectStriking(Item* pItem) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_STRIKING; }

	void affect() throw(Error){}
	void affect(Item* pItem) throw(Error);
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);

	void unaffect(Item* pItem) throw(Error);
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) throw(Error);
    void unaffect() throw(Error);
	void unaffect(Creature* pCreature) throw(Error){};		

	string toString() const throw();

public:
	void setIncDamage(Damage_t d) throw(Error) { m_incDamage = d;}

private :
	Damage_t m_incDamage;
};

#endif // __EFFECT_STRIKING__
