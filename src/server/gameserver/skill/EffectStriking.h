//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectStriking.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_STRIKING__
#define __EFFECT_STRIKING__

#include "Effect.h"
#include "EffectLoader.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectStriking
//////////////////////////////////////////////////////////////////////////////

class EffectStriking : public Effect 
{
public:
	EffectStriking(Creature* pCreature) ;

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_STRIKING; }

	void affect() {}
	void affect(Creature* pCreature) ;
	void affect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;

	void unaffect(Creature* pCreature) ;
	void unaffect(Zone* pZone, ZoneCoord_t x, ZoneCoord_t y, Object* pObject) ;
    void unaffect() ;

	string toString() const throw();

public:
	Damage_t getDamageBonus(void) const { return m_DamageBonus; }
	void setDamageBonus(Damage_t bonus) { m_DamageBonus = bonus; }

	Item::ItemClass getItemClass() const { return m_ItemClass; }
	ItemID_t		getItemID() const { return m_ItemID; }
	void	setTargetItem( Item* pItem ) { m_ItemClass = pItem->getItemClass(); m_ItemID = pItem->getItemID(); }
	bool	isTargetItem( Item* pItem ) { return m_ItemClass == pItem->getItemClass() && m_ItemID == pItem->getItemID(); }

private :
	Damage_t   m_DamageBonus;
	Item::ItemClass	m_ItemClass;
	ItemID_t	m_ItemID;
};

#endif // __EFFECT_STRIKING__
