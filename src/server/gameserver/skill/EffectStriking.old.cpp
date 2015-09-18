//////////////////////////////////////////////////////////////////////////////
// Filename    : EffectStriking.cpp
// Written by  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "EffectStriking.h"
#include "Item.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Monster.h"
#include "Player.h"
#include "item/AR.h"
#include "item/SG.h"
#include "item/SMG.h"
#include "item/SR.h"
#include "item/HolyWater.h"
#include "item/Sword.h"
#include "item/Blade.h"
#include "item/Mace.h"
#include "item/Cross.h"
#include "DB.h"

EffectStriking::EffectStriking(Item* pItem)
	throw(Error)
{
	__BEGIN_TRY

	setTarget(pItem);

	__END_CATCH
}

void EffectStriking::affect(Item* pItem)
	throw(Error)
{
	__BEGIN_TRY
																															    	
	__END_CATCH
}

void EffectStriking::affect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void EffectStriking::unaffect()
	throw(Error)
{
    Item* pItem = dynamic_cast<Item*>(m_pTarget);
	unaffect(pItem);
}

void EffectStriking::unaffect(Item* pItem)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "EffectStriking " << "unaffect BEGIN" << endl;

	if (pItem == NULL)
	{
		//cout << "EffectStriking " << "unaffect END" << endl;
		return;
	}

	int damage = 0;

	// 변화된 damage를 되돌린다.
	if (pItem->getItemClass() == Item::ITEM_CLASS_SWORD)
	{
		Sword* pI = dynamic_cast<Sword*>(pItem);
		pI->setBonusDamage(pI->getBonusDamage() - m_incDamage);
		damage = pI->getBonusDamage();
	}
	else if (pItem->getItemClass() == Item::ITEM_CLASS_BLADE)
	{
		Blade* pI = dynamic_cast<Blade*>(pItem);
		pI->setBonusDamage(pI->getBonusDamage() - m_incDamage);
		damage = pI->getBonusDamage();
	}
 	else if (pItem->getItemClass() == Item::ITEM_CLASS_SG)
	{
		SG* pI = dynamic_cast<SG*>(pItem);
		pI->setBonusDamage(pI->getBonusDamage() - m_incDamage);
		damage = pI->getBonusDamage();
	}
   	else if (pItem->getItemClass() == Item::ITEM_CLASS_SMG)
	{
		SMG* pI = dynamic_cast<SMG*>(pItem);
		pI->setBonusDamage(pI->getBonusDamage() - m_incDamage);
		damage = pI->getBonusDamage();
	}
	else if (pItem->getItemClass() == Item::ITEM_CLASS_AR)
	{
		AR* pI = dynamic_cast<AR*>(pItem);
		pI->setBonusDamage(pI->getBonusDamage() - m_incDamage);
		damage = pI->getBonusDamage();
	}
	else if (pItem->getItemClass() == Item::ITEM_CLASS_SR)
	{
		SR* pI = dynamic_cast<SR*>(pItem);
		pI->setBonusDamage(pI->getBonusDamage() - m_incDamage);
		damage = pI->getBonusDamage();
	} 
	else if (pItem->getItemClass() == Item::ITEM_CLASS_MACE)
	{
		Mace* pI = dynamic_cast<Mace*>(pItem);
		pI->setBonusDamage(pI->getBonusDamage() - m_incDamage);
		damage = pI->getBonusDamage();
	}
	else if (pItem->getItemClass() == Item::ITEM_CLASS_CROSS)
	{
		Cross* pI = dynamic_cast<Cross*>(pItem);
		pI->setBonusDamage(pI->getBonusDamage() - m_incDamage);
		damage = pI->getBonusDamage();
	}

	pItem->removeFlag(Effect::EFFECT_CLASS_STRIKING);

	//cout << "EffectStriking " << "unaffect END" << endl;

	__END_CATCH
}

void EffectStriking::unaffect(Zone* pZone , ZoneCoord_t x , ZoneCoord_t y , Object* pObject)
	throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

string EffectStriking::toString()
	const throw()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "EffectStriking("
		<< "ObjectID:" << getObjectID()
		<< ")";
	return msg.toString();

	__END_CATCH
}

