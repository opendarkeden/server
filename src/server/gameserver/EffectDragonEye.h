//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectDragonEye.h
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __EFFECT_DRAGON_EYE__
#define __EFFECT_DRAGON_EYE__

#include "EffectHasRelic.h"

//////////////////////////////////////////////////////////////////////////////
// class EffectDragonEye
//////////////////////////////////////////////////////////////////////////////

class EffectDragonEye : public EffectHasRelic 
{
public:
	EffectDragonEye(Creature* pCreature) throw(Error);
	EffectDragonEye(Item* pItem) throw(Error);

public:
    EffectClass getEffectClass() const throw() { return EFFECT_CLASS_DRAGON_EYE; }

	void affect(Creature* pCreature) throw(Error);
	void affect(Item* pItem) throw(Error);

	void unaffect(Creature* pCreature) throw(Error);

	string toString() const throw();

	// get/set ItemID
	ItemID_t getItemID() const { return m_ItemID; }
	void setItemID( ItemID_t itemID ) { m_ItemID = itemID; }

private:
	// DragonEye 아이템의 ID. GlobalPostionLoader 를 위한 멤버
	ItemID_t	m_ItemID;
};

#endif 
