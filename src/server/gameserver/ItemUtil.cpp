//////////////////////////////////////////////////////////////////////////////
// Filename    : ItemUtil.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "DB.h"
#include "ItemUtil.h"
#include "ItemInfo.h"
#include "ItemInfoManager.h"
#include "OptionInfo.h"
#include "Player.h"
#include "PlayerCreature.h"
#include "Inventory.h"
#include "Utility.h"
#include "VSDateTime.h"
#include "Slayer.h"
#include "Vampire.h"
#include "Ousters.h"
#include "Treasure.h"
#include "UniqueItemManager.h"
#include "RelicUtil.h"
#include "GoodsInfoManager.h"
#include "ItemGradeManager.h"

#include "item/AR.h"
#include "item/SR.h"
#include "item/SG.h"
#include "item/SMG.h"
#include "item/Magazine.h"
#include "item/SlayerPortalItem.h"
#include "item/Relic.h"
#include "item/OustersSummonItem.h"
#include "ItemFactoryManager.h"
#include "VariableManager.h"

#include "GCCreateItem.h"

#include <fstream>
#include <stdio.h>

#include "Corpse.h"
#include "MonsterCorpse.h"
#include "ctf/FlagManager.h"

#include "PetInfo.h"
#include "PetExpInfo.h"
#include "PetTypeInfo.h"
#include "item/PetItem.h"

#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)
	
	#include "SystemAvailabilitiesManager.h"

#endif // __THAILAND_SERVER__

//////////////////////////////////////////////////////////////////////////////
// ���� �� �ִ� �������ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isStackable(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_POTION:
		case Item::ITEM_CLASS_MAGAZINE:
		case Item::ITEM_CLASS_EVENT_STAR:
		case Item::ITEM_CLASS_SKULL:
		case Item::ITEM_CLASS_SERUM:
		case Item::ITEM_CLASS_VAMPIRE_ETC:
		case Item::ITEM_CLASS_WATER:
		case Item::ITEM_CLASS_HOLYWATER:
		case Item::ITEM_CLASS_BOMB_MATERIAL:
		case Item::ITEM_CLASS_BOMB:
		case Item::ITEM_CLASS_MINE:
		case Item::ITEM_CLASS_EVENT_ETC:
		case Item::ITEM_CLASS_RESURRECT_ITEM:
		case Item::ITEM_CLASS_ETC:
		case Item::ITEM_CLASS_MIXING_ITEM:
		case Item::ITEM_CLASS_LARVA:
		case Item::ITEM_CLASS_PUPA:
		case Item::ITEM_CLASS_COMPOS_MEI:
		case Item::ITEM_CLASS_EFFECT_ITEM:
		case Item::ITEM_CLASS_MOON_CARD:
		case Item::ITEM_CLASS_PET_ENCHANT_ITEM:
		case Item::ITEM_CLASS_LUCKY_BAG:
		case Item::ITEM_CLASS_PET_FOOD:
		case Item::ITEM_CLASS_MONEY://add by sonic 2006.10.30  ����Ǯ��Ϊ�ɵ���
			return true;
		default:
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// ���� �� �ִ� �������ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isStackable(const Item* pItem)
{
	//if (pItem == NULL) return false;

	/*
	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_POTION:
		case Item::ITEM_CLASS_MAGAZINE:
		case Item::ITEM_CLASS_EVENT_STAR:
		case Item::ITEM_CLASS_SKULL:
		case Item::ITEM_CLASS_SERUM:
		case Item::ITEM_CLASS_VAMPIRE_ETC:
		case Item::ITEM_CLASS_WATER:
		case Item::ITEM_CLASS_HOLYWATER:
		case Item::ITEM_CLASS_BOMB_MATERIAL:
		case Item::ITEM_CLASS_BOMB:
		case Item::ITEM_CLASS_MINE:
			return true;
		default:
			return false;
	}
	*/

	// by sigi. 2002.5.13
	return pItem!=NULL 
			&& pItem->isStackable();
}

//////////////////////////////////////////////////////////////////////////////
// ���� Ŭ����, Ÿ���� �������ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isSameItem(Item::ItemClass IClass1, Item::ItemClass IClass2, ItemType_t type1, ItemType_t type2)
{
	return IClass1 == IClass2 
			&& type1 == type2;
}

//////////////////////////////////////////////////////////////////////////////
// ���� Ŭ����, Ÿ���� �������ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isSameItem(const Item* pItem1, const Item* pItem2)
{
	return pItem1!=NULL && pItem2!=NULL
			&& pItem1->getItemClass() == pItem2->getItemClass() 
			&& pItem1->getItemType() == pItem2->getItemType();
}

//////////////////////////////////////////////////////////////////////////////
// �� �������� ���� �� �ִ°�?
//////////////////////////////////////////////////////////////////////////////
bool canStack(const Item* pItem1, const Item* pItem2)
{
	return isStackable(pItem1) 
			&& isSameItem(pItem1, pItem2);
}

//////////////////////////////////////////////////////////////////////////////
// �� �� �����ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isTwohandWeapon(const Item* pItem)
{
	if (pItem == NULL) return false;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_BLADE:
		case Item::ITEM_CLASS_AR:
		case Item::ITEM_CLASS_SR:
		case Item::ITEM_CLASS_SG:
		case Item::ITEM_CLASS_SMG:
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_MACE:
		case Item::ITEM_CLASS_VAMPIRE_WEAPON:
			return true;
		default:
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// ������ �����ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isMeleeWeapon(const Item* pItem)
{
	if (pItem == NULL) return false;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_SWORD:
		case Item::ITEM_CLASS_BLADE:
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_MACE:
		case Item::ITEM_CLASS_VAMPIRE_WEAPON:
		case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
		case Item::ITEM_CLASS_OUSTERS_WRISTLET:
			return true;
		default:
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// ����, ���� ������ �����ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isFighterWeapon(const Item* pItem)
{
	if (pItem == NULL) return false;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_SWORD:
		case Item::ITEM_CLASS_BLADE:
			return true;
		default:
			return false;
	}

	return false;
}

bool isArmsWeapon(const Item* pItem)
{
	if (pItem == NULL) return false;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_AR:
		case Item::ITEM_CLASS_SR:
		case Item::ITEM_CLASS_SG:
		case Item::ITEM_CLASS_SMG:
			return true;
			break;
		default:
			return false;
			break;
	}

	return false;
}

bool isClericWeapon(const Item* pItem)
{
	if (pItem == NULL) return false;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_MACE:
			return true;
		default:
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// �ѿ� �´� źâ�ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isSuitableMagazine(const Item* pGun, const Item* pMagazine, bool hasVivid)
{
	if (pGun == NULL || pMagazine == NULL) return false;
	if (pMagazine->getItemClass() != Item::ITEM_CLASS_MAGAZINE) return false;

	ItemType_t magazineType = pMagazine->getItemType();
	MagazineInfo* pInfo = dynamic_cast<MagazineInfo*>(g_pItemInfoManager->getItemInfo( Item::ITEM_CLASS_MAGAZINE, magazineType ));

	switch (pGun->getItemClass())
	{
		case Item::ITEM_CLASS_SG:
			if ( pInfo->getGunType() != MagazineInfo::SG ) return false;
//			if (magazineType == 0) return true;
//			if (magazineType == 1) return true;
//			if (magazineType == 8) return true;
//			if (magazineType == 9) return true;
			break;
		case Item::ITEM_CLASS_AR:
			if ( pInfo->getGunType() != MagazineInfo::AR ) return false;
//			if (magazineType == 2) return true;
//			if (magazineType == 3) return true;
//			if (magazineType == 10) return true;
//			if (magazineType == 11) return true;
			break;
		case Item::ITEM_CLASS_SMG:
			if ( pInfo->getGunType() != MagazineInfo::SMG ) return false;
//			if (magazineType == 4) return true;
//			if (magazineType == 5) return true;
//			if (magazineType == 12) return true;
//			if (magazineType == 13) return true;
			break;
		case Item::ITEM_CLASS_SR:
			if ( pInfo->getGunType() != MagazineInfo::SR ) return false;
//			if (magazineType == 6) return true;
//			if (magazineType == 7) return true;
//			if (magazineType == 14) return true;
//			if (magazineType == 15) return true;
			break;
		default:
			return false;
	}

	if ( pInfo->isVivid() && !hasVivid ) return false;

	return true;
}

//////////////////////////////////////////////////////////////////////////////
// �����̾�� �����ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isSlayerWeapon(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_SWORD:
		case Item::ITEM_CLASS_BLADE:
		case Item::ITEM_CLASS_CROSS:
		case Item::ITEM_CLASS_MACE:
		case Item::ITEM_CLASS_AR:
		case Item::ITEM_CLASS_SR:
		case Item::ITEM_CLASS_SG:
		case Item::ITEM_CLASS_SMG:
			return true;
		default:
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// �����̾�� �����ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isVampireWeapon(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_VAMPIRE_WEAPON:
			return true;
		default:
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// �ƿ콺�ͽ��� �����ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isOustersWeapon(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
		case Item::ITEM_CLASS_OUSTERS_WRISTLET:
			return true;
		default:
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// �����̾�� ���ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isSlayerArmor(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_COAT:
		case Item::ITEM_CLASS_TROUSER:
		case Item::ITEM_CLASS_GLOVE:
		case Item::ITEM_CLASS_BELT:
		case Item::ITEM_CLASS_SHOES:
		case Item::ITEM_CLASS_SHIELD:
		case Item::ITEM_CLASS_HELM:
		case Item::ITEM_CLASS_SHOULDER_ARMOR:
			return true;
		default:
			break;
	}

	return false;
}
//////////////////////////////////////////////////////////////////////////////
// �����̾�� ���ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isVampireArmor(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_VAMPIRE_COAT:
		case Item::ITEM_CLASS_PERSONA:
			return true;
		default:
			break;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// �ƿ콺�ͽ� ���ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isOustersArmor(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_OUSTERS_COAT:
		case Item::ITEM_CLASS_OUSTERS_BOOTS:
		case Item::ITEM_CLASS_OUSTERS_CIRCLET:
		case Item::ITEM_CLASS_OUSTERS_ARMSBAND:
		case Item::ITEM_CLASS_MITTEN:
			return true;
		default:
			break;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// �����̾�� �Ǽ��縮�ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isSlayerAccessory(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_NECKLACE:
		case Item::ITEM_CLASS_BRACELET:
		case Item::ITEM_CLASS_RING:
		case Item::ITEM_CLASS_CARRYING_RECEIVER:
			return true;
		default:
			break;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////
// �����̾�� �Ǽ��縮�ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isVampireAccessory(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_VAMPIRE_NECKLACE:
		case Item::ITEM_CLASS_VAMPIRE_BRACELET:
		case Item::ITEM_CLASS_VAMPIRE_RING:
		case Item::ITEM_CLASS_VAMPIRE_AMULET:
		case Item::ITEM_CLASS_VAMPIRE_EARRING:
		case Item::ITEM_CLASS_DERMIS:
			return true;
		default:
			break;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////
// �ƿ콺�ͽ��� �Ǽ��縮�ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isOustersAccessory(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_OUSTERS_ARMSBAND:
		case Item::ITEM_CLASS_OUSTERS_PENDENT:
		case Item::ITEM_CLASS_OUSTERS_RING:
		case Item::ITEM_CLASS_OUSTERS_STONE:
		case Item::ITEM_CLASS_FASCIA:
			return true;
		default:
			break;
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////////
// ���������� �������ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isRepairableItem(const Item* pItem)
{
	// ����ũ �������� ������ �ʿ䰡 ����.
	if (pItem == NULL
		|| pItem->isUnique()
		|| pItem->isTimeLimitItem()) return false;
	if ( pItem->isFlagItem() ) return false;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_MOTORCYCLE:
		case Item::ITEM_CLASS_POTION:
		case Item::ITEM_CLASS_MAGAZINE:
		case Item::ITEM_CLASS_WATER:
		case Item::ITEM_CLASS_HOLYWATER:
		case Item::ITEM_CLASS_BOMB_MATERIAL:
		case Item::ITEM_CLASS_ETC:
		case Item::ITEM_CLASS_KEY:
		case Item::ITEM_CLASS_BOMB:
		case Item::ITEM_CLASS_MINE:
		case Item::ITEM_CLASS_LEARNINGITEM:
		case Item::ITEM_CLASS_CORPSE:
		case Item::ITEM_CLASS_SKULL:
		case Item::ITEM_CLASS_SERUM:
		case Item::ITEM_CLASS_VAMPIRE_ETC:
		case Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM:
		case Item::ITEM_CLASS_EVENT_GIFT_BOX:
		case Item::ITEM_CLASS_EVENT_STAR:
		case Item::ITEM_CLASS_MONEY:
		case Item::ITEM_CLASS_VAMPIRE_AMULET:
		case Item::ITEM_CLASS_QUEST_ITEM:
		case Item::ITEM_CLASS_RELIC:
		case Item::ITEM_CLASS_BLOOD_BIBLE:
		case Item::ITEM_CLASS_CASTLE_SYMBOL:
		case Item::ITEM_CLASS_COUPLE_RING:
		case Item::ITEM_CLASS_VAMPIRE_COUPLE_RING:
		case Item::ITEM_CLASS_EVENT_ITEM:
		case Item::ITEM_CLASS_MOON_CARD:
		case Item::ITEM_CLASS_SWEEPER:
//		case Item::ITEM_CLASS_PET_ITEM:
		case Item::ITEM_CLASS_LUCKY_BAG:
		case Item::ITEM_CLASS_CARRYING_RECEIVER:
		case Item::ITEM_CLASS_DERMIS:
		case Item::ITEM_CLASS_FASCIA:
			return false;
		default:
			return true;
	}

	return true;
}


//////////////////////////////////////////////////////////////////////////////
// �������� �����Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void repairItem(Item* pItem)
{
	if (pItem != NULL
		&& !pItem->isUnique()
		&& isRepairableItem(pItem))
	{
		Item::ItemClass IClass = pItem->getItemClass();

		if (IClass == Item::ITEM_CLASS_SLAYER_PORTAL_ITEM)
		{
			SlayerPortalItem* pSlayerPortalItem = dynamic_cast<SlayerPortalItem*>(pItem);
			pSlayerPortalItem->setCharge(pSlayerPortalItem->getMaxCharge());
		}
		else if ( IClass == Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM )
		{
			OustersSummonItem* pOustersSummonItem = dynamic_cast<OustersSummonItem*>(pItem);
			pOustersSummonItem->setCharge(pOustersSummonItem->getMaxCharge());
		}
		else
		{
			// �ֳ� ����ġ�� ����
			Durability_t maxDurability = computeMaxDurability(pItem);
			// �����Ѵ�.
			pItem->setDurability(maxDurability);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
// �������� �ִ� �������� ����.
//////////////////////////////////////////////////////////////////////////////
Durability_t computeMaxDurability(Item* pItem)
{
	if (pItem == NULL) return 0;

//	ItemInfo*    pItemInfo     = g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType());
//	unsigned long maxDurability = pItemInfo->getDurability();

	unsigned long maxDurability = pItem->getMaxDurability();

	// 100%���� ����
	unsigned long plusPoint = 100;

	const list<OptionType_t>& optionTypes = pItem->getOptionTypeList();
	//OptionType_t OptionType = pItem->getOptionType();

	list<OptionType_t>::const_iterator itr;

	for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
	{
		OptionType_t OptionType = *itr;

		if (OptionType != 0)
		{
			OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo(OptionType);

			if (pOptionInfo->getClass() == OPTION_DURABILITY)
			{
				plusPoint += (pOptionInfo->getPlusPoint()-100);
			}
		}
	}

	maxDurability = (maxDurability * plusPoint / 100);
	// 65000 �Ѿ�� ��縮���� -_-;;;
//	maxDurability = min( (unsigned long)65000, maxDurability );

	return (Durability_t)maxDurability;
}

//////////////////////////////////////////////////////////////////////////////
// źâ�� ���Ƴ����ش�. 
//////////////////////////////////////////////////////////////////////////////
Bullet_t reloadArmsItem(Item* pGun, Item* pMagazine)
{
	Assert(pGun != NULL);
	Assert(pMagazine != NULL);

	// vivid magazine üũ�� ���� ������ ���� �Ѵ�. �� �Լ��� ������ reload���ش�.
	if (isSuitableMagazine(pGun, pMagazine, true) == false) return false;

	Item::ItemClass IClass        = pGun->getItemClass();
	ItemType_t      MagazineType  = pMagazine->getItemType();
	ItemInfo*       pItemInfo     = g_pItemInfoManager->getItemInfo(Item::ITEM_CLASS_MAGAZINE, MagazineType);
	MagazineInfo*   pMagazineInfo = dynamic_cast<MagazineInfo*>(pItemInfo);
	Bullet_t        BulletCount   = pMagazineInfo->getMaxBullets();
	Silver_t        Silver        = pMagazineInfo->getMaxSilver();

	if (IClass == Item::ITEM_CLASS_AR)
	{
		AR* pAR = dynamic_cast<AR*>(pGun);
		pAR->setBulletCount(BulletCount);
		pAR->setSilver(Silver);
		return pAR->getBulletCount();
	}
	else if (IClass == Item::ITEM_CLASS_SR)
	{
		SR* pSR = dynamic_cast<SR*>(pGun);
		pSR->setBulletCount(BulletCount);
		pSR->setSilver(Silver);
		return pSR->getBulletCount();
	}
	else if (IClass == Item::ITEM_CLASS_SG)
	{
		SG* pSG = dynamic_cast<SG*>(pGun);
		pSG->setBulletCount(BulletCount);
		pSG->setSilver(Silver);
		return pSG->getBulletCount();
	}
	else if (IClass == Item::ITEM_CLASS_SMG)
	{
		SMG* pSMG = dynamic_cast<SMG*>(pGun);
		pSMG->setBulletCount(BulletCount);
		pSMG->setSilver(Silver);
		return pSMG->getBulletCount();
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////
// �Ѿ��� ���ش�.
//////////////////////////////////////////////////////////////////////////////
Bullet_t decreaseBullet(Item* pWeapon) 
	
{
	__BEGIN_TRY

	if (pWeapon == NULL)
	{
		ofstream file("bulletBug.txt", ios::out | ios::app);
		file << "decreaseBullet() : pWeapon is NULL" <<  endl;
		return 0;
	}

	Item::ItemClass IClass = pWeapon->getItemClass();
	Bullet_t        bullet = 0;
	Silver_t        silver = 0;

	// Gun class�� �߰��ߴ�. by sigi. 2002.5.8
	/*
	if (IClass == Item::ITEM_CLASS_AR
		|| IClass == Item::ITEM_CLASS_SMG
		|| IClass == Item::ITEM_CLASS_SR
		|| IClass == Item::ITEM_CLASS_SG)
	{
		Gun* pGun = dynamic_cast<Gun*>(pWeapon);

		bullet = max(0, (int)(pGun->getBulletCount() - 1));
		pGun->setBulletCount(bullet);

		silver = max(0, (int)(pGun->getSilver() - 1));
		pGun->setSilver(silver);
	}
	else
	{
		filelog("bulletBug.log", "decreaseBullet() : Invalid item class : %s\n", ItemClass2String[IClass].c_str());
		throw ("decreaseBullet() : Invalid item class");
	}
	*/

	///*
	if (IClass == Item::ITEM_CLASS_AR)
	{
		AR* pAR = dynamic_cast<AR*>(pWeapon);
		bullet = max(0, (int)(pAR->getBulletCount() - 1));
		pAR->setBulletCount(bullet);

		silver = max(0, (int)(pAR->getSilver() - 1));
		pAR->setSilver(silver);
	}
	else if (IClass == Item::ITEM_CLASS_SR)
	{
		SR* pSR = dynamic_cast<SR*>(pWeapon);
		bullet = max(0, (int)(pSR->getBulletCount() - 1));
		pSR->setBulletCount(bullet);

		silver = max(0, (int)(pSR->getSilver() - 1));
		pSR->setSilver(silver);
	}
	else if (IClass == Item::ITEM_CLASS_SG)
	{
		SG* pSG = dynamic_cast<SG*>(pWeapon);
		bullet = max(0, (int)(pSG->getBulletCount() - 1));
		pSG->setBulletCount(bullet);

		silver = max(0, (int)(pSG->getSilver() - 1));
		pSG->setSilver(silver);
	}
	else if (IClass == Item::ITEM_CLASS_SMG)
	{
		SMG* pSMG = dynamic_cast<SMG*>(pWeapon);
		bullet = max(0, (int)(pSMG->getBulletCount() - 1));
		pSMG->setBulletCount(bullet);

		silver = max(0, (int)(pSMG->getSilver() - 1));
		pSMG->setSilver(silver);
	}
	else
	{
		filelog("bulletBug.log", "decreaseBullet() : Invalid item class : %s\n", ItemClass2String[IClass].c_str());
		throw ("decreaseBullet() : Invalid item class");
	}
	//*/

	return bullet;

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// ���� �Ѿ��� ������ ����
//////////////////////////////////////////////////////////////////////////////
Bullet_t getRemainBullet(Item* pWeapon) 
	
{
	__BEGIN_TRY

	if (pWeapon == NULL) 
	{
		return 0;
	}

	Item::ItemClass IClass = pWeapon->getItemClass();

	// by sigi. 2002.5.16
	/*
	if (pWeapon->isGun())
	{
		Gun* pGun = dynamic_cast<Gun*>(pGun);

		return pGun->getBulletCount();
	}
	*/
	if (IClass == Item::ITEM_CLASS_AR)
	{
		AR* pAR = dynamic_cast<AR*>(pWeapon);
		return pAR->getBulletCount();
	}
	else if (IClass == Item::ITEM_CLASS_SR)
	{
		SR* pSR = dynamic_cast<SR*>(pWeapon);
		return pSR->getBulletCount();
	}
	else if (IClass == Item::ITEM_CLASS_SG)
	{
		SG* pSG = dynamic_cast<SG*>(pWeapon);
		return pSG->getBulletCount();
	}
	else if (IClass == Item::ITEM_CLASS_SMG)
	{
		SMG* pSMG = dynamic_cast<SMG*>(pWeapon);
		return pSMG->getBulletCount();
	}
	else
	{
		filelog("bullet.log", "getRemainBullet() : Invalid item class : %s\n", ItemClass2String[IClass].c_str());
		throw ("getRemainBullet() : Invalid item class");
	}

	return 0;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// ���� �� �ִ� �������ΰ�? 
//////////////////////////////////////////////////////////////////////////////
bool isPortableItem(Item* pItem)
{
	Assert(pItem != NULL);

//	if ( pItem->isTimeLimitItem() ) return false;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_CORPSE:
		case Item::ITEM_CLASS_MOTORCYCLE:
		case Item::ITEM_CLASS_COUPLE_RING:
		case Item::ITEM_CLASS_VAMPIRE_COUPLE_RING:
			return false;
		default:
			return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// ����� �� �ִ� �������ΰ�?
// ���⼭�� ����̶�, ����ؼ� ������� �Ҹ� �������� ���Ѵ�.
//////////////////////////////////////////////////////////////////////////////
bool isUsableItem(Item* pItem, Creature* pUser)
{
	Assert(pItem != NULL);
	Assert(pUser != NULL);

	// ���߿� ���� Ŭ��������, � ���� ����� �� �ְ�,
	// � ���� ����� �� ���� ���� ������ ������?
	//ItemType_t IType = pItem->getItemType();

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_POTION:
			if (pUser->isSlayer()) return true;
			break;
		case Item::ITEM_CLASS_MAGAZINE:
			if (pUser->isSlayer()) return true;
			break;
		case Item::ITEM_CLASS_KEY:
			if (g_pVariableManager->isSummonMotorcycle() && pUser->isSlayer()) return true;
			break;
		case Item::ITEM_CLASS_ETC:
			if (pUser->isSlayer() && pItem->getItemType() == 1) return true;
			break;
		case Item::ITEM_CLASS_SERUM:
			if (pUser->isVampire()) return true;
			break;
		case Item::ITEM_CLASS_VAMPIRE_ETC:
			if (pUser->isVampire()) return true;
			break;
		case Item::ITEM_CLASS_SLAYER_PORTAL_ITEM:
			if (pUser->isSlayer()) return true;
			break;
		case Item::ITEM_CLASS_EVENT_TREE:
			if ( pItem->getItemType() == 12 || ( pItem->getItemType() >= 26 && pItem->getItemType() <=28 ) ) return true;	// �ϼ��� Ʈ��
			break;

		case Item::ITEM_CLASS_EVENT_ETC:
			return true;
			break;

		case Item::ITEM_CLASS_COUPLE_RING:
			if ( pUser->isSlayer() ) return true;
			break;
		case Item::ITEM_CLASS_VAMPIRE_COUPLE_RING:
			if ( pUser->isVampire() ) return true;
			break;

		case Item::ITEM_CLASS_DYE_POTION:
			return true;

		case Item::ITEM_CLASS_RESURRECT_ITEM:
			if ( pUser->isFlag(Effect::EFFECT_CLASS_COMA) ) return true;
			break;

		case Item::ITEM_CLASS_PUPA:
			if (pUser->isOusters()) return true;
			break;

		case Item::ITEM_CLASS_COMPOS_MEI:
			if (pUser->isOusters()) return true;
			break;

		case Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM:
			if (pUser->isOusters()) return true;
			break;

		case Item::ITEM_CLASS_EFFECT_ITEM:
		case Item::ITEM_CLASS_PET_ITEM:
		case Item::ITEM_CLASS_PET_FOOD:
		case Item::ITEM_CLASS_PET_ENCHANT_ITEM:
			return true;
			break;

		case Item::ITEM_CLASS_EVENT_GIFT_BOX:
			if ( pItem->getItemType() >= 6  && pItem->getItemType() <= 15 ) return true;
			if ( pItem->getItemType() >= 19 && pItem->getItemType() <= 21 ) return true;
			break;

		case Item::ITEM_CLASS_SMS_ITEM:
			return true;
			break;

		case Item::ITEM_CLASS_TRAP_ITEM:
			return true;
			break;
		// add by Coffee 2007-6-9
		case Item::ITEM_CLASS_MOON_CARD:
			if ( pItem->getItemType() >=5 && pItem->getItemType() <=7 ) return true;
			break;
		default :
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// �������� ���ڸ� ���δ�.
//////////////////////////////////////////////////////////////////////////////
ItemNum_t decreaseItemNum(Item* pItem, Inventory* pInventory, 
	const string& OwnerID, Storage storage, StorageID_t storageID, BYTE x, BYTE y)
{
	Assert(pItem != NULL);
	Assert(pInventory != NULL);
	Assert(OwnerID != "");
	Assert(isStackable(pItem));

	if (pItem->getNum() > 1)
	{
		pItem->setNum(pItem->getNum() - 1); // �������� ������ �ϳ� ���δ�.
		pInventory->decreaseItemNum(); // �κ��丮 �� ������ ���δ�.
		pInventory->decreaseWeight(pItem->getWeight()); // �κ��丮 �� ���Ը� ���δ�.
		//pItem->save(OwnerID, storage, storageID, x, y); // ������ ������ �����Ѵ�.
		// ������ ���� ����ȭ. 2002.7.25 by sigi
		char pField[80];
		sprintf(pField, "Num=%d", pItem->getNum());
		pItem->tinysave(pField);


		return pItem->getNum();
	}
	else // �������� 1��¥��������, �����Ѵ�.
	{
		pInventory->deleteItem(x, y);
		pItem->destroy();
		SAFE_DELETE(pItem);
		return 0;
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void processItemBug(Creature* pCreature, Item* pItem)
{
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC != NULL);
	Assert(pItem != NULL);

	pPC->addItemToGarbage(pItem);
}

void processItemBugEx(Creature* pCreature, Item* pItem)
{
	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC != NULL);
	Assert(pItem != NULL);

	pPC->addItemToGarbage(pItem);
	pItem->save(pCreature->getName(), STORAGE_GARBAGE, 0, 0, 0);
}

bool hasOptionType(const list<OptionType_t>& optionTypes, OptionType_t optionType)
{
	if (optionTypes.empty())
		return false;

	list<OptionType_t>::const_iterator itr;

	for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
	{
		if (*itr==optionType)
			return true;
	}

	return false;
}

bool hasOptionClass(const list<OptionType_t>& optionTypes, OptionType_t optionType)
{
	if (optionTypes.empty())
		return false;

	try {

		OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo( optionType );

		if (pOptionInfo==NULL)
			return false;

		OptionClass newOptionClass = pOptionInfo->getClass();
			
		list<OptionType_t>::const_iterator itr;

		for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
		{
			pOptionInfo = g_pOptionInfoManager->getOptionInfo( *itr );
			if (pOptionInfo==NULL) return false;
			if (pOptionInfo->getClass()==newOptionClass)
				return true;
		}
	} catch (Throwable& t) {
		// ����..
		filelog("hasOptionClassBug.txt", "%s", t.toString().c_str());
	}

	return false;
}

void setOptionTypeFromField(list<OptionType_t>& optionTypes, const string& optionField)
{
	if (optionField.empty()) return;

	const char* pOptionField = optionField.c_str();
	  const char *sep = " ";
	  char *s = new char[optionField.size()+1];
	  strcpy(s,optionField.c_str());
	  char *p;
	  int aa;
	  p = strtok(s, sep);
	  while(p)
	 {
		aa = atoi(p);
	   optionTypes.push_back( (OptionType_t)aa );
	    p = strtok(NULL, sep);
	  }
}


void setOptionTypeToField(const list<OptionType_t>& optionTypes, string& optionField)
{
	if (optionTypes.empty()) return;

	int ch;
	char string[128];
	list<OptionType_t>::const_iterator itr;
	for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
	{
		if (itr != optionTypes.begin()) {
		    optionField += " ";
		}
		ch = *itr;
 		sprintf(string, "%d", ch);
		optionField += string;
	}
}

string getOptionTypeToString(const list<OptionType_t>& optionTypes)
{
	if (optionTypes.empty()) return string("NONE");

	string optionField;
	unsigned char ch;

	char str[12];

	list<OptionType_t>::const_iterator itr;
	for (itr=optionTypes.begin(); itr!=optionTypes.end(); itr++)
	{
		if (itr != optionTypes.begin()) {
			optionField += " ";
		}
		ch = *itr;
		sprintf(str, "%d", (int)ch);
		optionField += str;
	}

	return optionField;
}


//////////////////////////////////////////////////////////////////////////////
// ���� ������ : ���� �ɼ��� ���ϱ�?
//////////////////////////////////////////////////////////////////////////////
bool isPossibleNextOption(ITEM_TEMPLATE* pTemplate)
{
	// ����� �ɼ��� 2�������ۿ� �� �ٴ´�.
	if (pTemplate->OptionType.size()>=5)
		return false;

	// �ƹ��͵� ���ٸ� ������ ���δ�...�� �ϴ°� �ƴ����� ��¶�� �׷��� - -;
	if (pTemplate->OptionType.empty())
		return true;

	// �����ۿ� Ư���� ����Ǿ� �ִ� �ɼ� Ȯ���� �����Ų��.
	if (pTemplate->NextOptionRatio!=0)
	{
		int dice = rand()%100;
		//cout << "NextOptionRatio : " << dice << " < " << (int)pTemplate->NextOptionRatio << endl;
		return dice < pTemplate->NextOptionRatio;
	}

	try {
		// ������ ��������.. ���� �ɼ��� ���� Ȯ���� ���Ѵ�.
		ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo(pTemplate->ItemClass, pTemplate->ItemType);
		Ratio_t nextItemRatio = pItemInfo->getNextOptionRatio();

		// ���� ���� �ɼǿ� ���ؼ�.. ���� �ɼ��� ���� Ȯ���� ���Ѵ�.
		list<OptionType_t>::const_iterator itr = pTemplate->OptionType.begin();
		Ratio_t nextOptionRatio = nextItemRatio;	// ��� ���Ϸ���..
		Ratio_t baseMultiplier = 100;				// 100%
		for (; itr!=pTemplate->OptionType.end(); itr++)
		{
			OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo( *itr );
			if (pOptionInfo==NULL)
				return false;
			nextOptionRatio *= pOptionInfo->getNextOptionRatio();
			baseMultiplier *= 100;
		}

		// [����] �ɼ��� �� �� �پ� �ִ� �����ۿ��� 
		//        ����° �ɼ��� ���� Ȯ���̶��..
		//
		// nextItemRatio = 10 %
		// nextOptionRatio1 = 20 %
		// nextOptionRatio2 = 30 %
		//
		// total nextOptionRatio = nextItemRatio * nextOptionRatio1 * nextOptionRatio2
		//                       = 10 * 20 * 30 = 6000
		//
		// baseMultiplier = 100(�ʱⰪ) * 100(option1) * 100(option2)
		//                = 1000000
		//
		// selectRatio = 0~baseMultiplier = 0~1000000
		//
		// Succeed = nextOptionRatio/baseMultiplier 
		//         = 6000/1000000
		//         = 6 / 1000
		//         = 0.6%

		Ratio_t selectRatio = rand()%baseMultiplier;

		// ���� ������ ���� Ȯ���� �����Ų��.
		nextOptionRatio = getPercentValue( nextOptionRatio, g_pVariableManager->getRareItemRatio() );

		// Ȯ�� üũ
		return selectRatio < nextOptionRatio;

	} catch (Throwable& t) {
		// �ϴ� �����Ѵ�.
		filelog("nextOptionBug.txt", "%s", t.toString().c_str());
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// ���� ������ ����
//////////////////////////////////////////////////////////////////////////////
Item* getRandomMysteriousItem(Creature* pCreature, Item::ItemClass itemClass, int maxLevel)
	
{
	__BEGIN_TRY

	Assert(pCreature!=NULL);

	InfoClassManager* pInfoClass = g_pItemInfoManager->getInfoManager( itemClass );
	Assert(pInfoClass!=NULL);

	ItemType_t itemType = 0;
	OptionType_t optionType = 1;

	ItemInfo* pItemInfo = NULL;

	//----------------------------------------------------------------------
	// Slayer�� ���
	//----------------------------------------------------------------------
	if (pCreature->isSlayer())
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
		
		Attr_t CSTR = pSlayer->getSTR(ATTR_BASIC);
		Attr_t CDEX = pSlayer->getDEX(ATTR_BASIC);
		Attr_t CINT = pSlayer->getINT(ATTR_BASIC);
		Attr_t CSUM = CSTR + CDEX + CINT;

		Attr_t    ReqSTR, ReqSTR2;
		Attr_t    ReqDEX, ReqDEX2;
		Attr_t    ReqINT, ReqINT2;
		Attr_t    ReqSum, ReqSum2;
		Attr_t    ReqGender;

		// gamble�� �� �ִ� �Ѱ踦 �� �� ��������.
		CSTR += 3;
		CDEX += 3;
		CINT += 3;
		CSUM += 5;

		// level����
		if (maxLevel!=0)
		{
			int maxAttr = maxLevel * 2 / 3;	// attr�� SUM�� 2/3���� ����.
			CSTR = min((int)maxAttr, (int)CSTR);
			CDEX = min((int)maxAttr, (int)CDEX);
			CINT = min((int)maxAttr, (int)CINT);
			CSUM = min((int)maxLevel, (int)CSUM);
		}

		// 10���� ��������.
		int i = 10;
		do
		{
			itemType = pInfoClass->getRandomItemType();

			// �� itemType�� �����ص� �Ǵ� level���� Ȯ���Ѵ�.
			pItemInfo = g_pItemInfoManager->getItemInfo(itemClass, itemType);

			ReqSTR2 = ReqSTR    = pItemInfo->getReqSTR();
			ReqDEX2 = ReqDEX    = pItemInfo->getReqDEX();
			ReqINT2 = ReqINT    = pItemInfo->getReqINT();
			ReqSum2 = ReqSum    = pItemInfo->getReqSum();
			ReqGender = pItemInfo->getReqGender();

			if (CSTR >= ReqSTR
				&& CDEX >= ReqDEX
				&& CINT >= ReqINT
				&& CSUM >= ReqSum
				&& (ReqGender==GENDER_BOTH
					|| pSlayer->getSex() == MALE && ReqGender == GENDER_MALE
					|| pSlayer->getSex() == FEMALE && ReqGender == GENDER_FEMALE))
			{
				// �� item type���� �����Ѵ�.
				break;
			}

		} while (--i);

		if (i==0)
		{
			// ������ ���� �⺻ item type�� �ٸ���.
			if ((itemClass==Item::ITEM_CLASS_COAT || itemClass==Item::ITEM_CLASS_TROUSER)
				&& pSlayer->getSex()==FEMALE)
			{
				itemType = 1;
			}
			else
			{
				itemType = 0;
			}

			// �ؿ��� üũ�Ҷ� �����ϱ� ���ؼ�..
			pItemInfo = NULL;
		}


		// �������� �ɼ��� ������ �ִٸ�, 
		// �ɼ��� ������ ���� �ɷ�ġ ������ �÷��ش�.
		int maxOptionLevel = max(1, min(100, (int)(CSUM/3)));

		const vector<OptionType_t>& optionVector = g_pOptionInfoManager->getPossibleGambleOptionVector((Item::ItemClass)itemClass, maxOptionLevel);
		vector<OptionType_t>::const_iterator iOption;

		/*
		cout << "optionVector[" << (int)itemClass << "][" << (int)maxOptionLevel << "] = (" << optionVector.size() << ") = ";

		for (iOption=optionVector.begin(); iOption!=optionVector.end(); iOption++)
		{
			cout << (int)*iOption << "  ";
		}
		cout << endl;
		*/

		// Total OptionRatio�� ���Ѵ�.
		int itemOptionRatio = g_pOptionInfoManager->getTotalGambleRatio((Item::ItemClass)itemClass, maxOptionLevel);

		if (optionVector.size()>0 && itemOptionRatio>0
			&& (pItemInfo==NULL || !pItemInfo->isUnique()))
		{
			// 10���� ��������.
			int i = 10;
			
			do {
				// random���� option�� �����Ѵ�.
				int optionRatio = random()%itemOptionRatio;
				int ratioSum      = 0;

				//cout << "Ratio = " << optionRatio << "/" << itemOptionRatio << endl;

				OptionInfo* pOptionInfo = NULL;

				for (iOption=optionVector.begin(); iOption!=optionVector.end(); iOption++)
				{
					optionType = *iOption;

					pOptionInfo = g_pOptionInfoManager->getOptionInfo( optionType );
					ratioSum += pOptionInfo->getRatio();

					if (optionRatio < ratioSum)
					{
						// �� option�� �����Ѵ�.
						//cout << "select : " << (int)optionType << endl;
						break;
					}
				}

				// option�� �䱸 �ɷ�ġ�� ���ؼ�
				if (ReqSTR != 0) ReqSTR = ReqSTR2 + (pOptionInfo->getReqSum() * 2);
				if (ReqDEX != 0) ReqDEX = ReqDEX2 + (pOptionInfo->getReqSum() * 2);
				if (ReqINT != 0) ReqINT = ReqINT2 + (pOptionInfo->getReqSum() * 2);
				if (ReqSum != 0) ReqSum = ReqSum2 + (pOptionInfo->getReqSum());

				//if (ReqSTR != 0) cout << "CSTR = " << (int)CSTR << ", ReqSTR = " << (int)ReqSTR2 << " + " << (int)pOptionInfo->getReqSum() << "*2 = " << (int)ReqSTR << endl;
				//if (ReqDEX != 0) cout << "CDEX = " << (int)CDEX << ", ReqDEX = " << (int)ReqDEX2 << " + " << (int)pOptionInfo->getReqSum() << "*2 = " << (int)ReqDEX << endl;
				//if (ReqINT != 0) cout << "CINT = " << (int)CINT << ", ReqINT = " << (int)ReqINT2 << " + " << (int)pOptionInfo->getReqSum() << "*2 = " << (int)ReqINT << endl;
				//if (ReqSum != 0) cout << "CSUM = " << (int)CSUM << ", ReqSum = " << (int)ReqSum2 << " + " << (int)pOptionInfo->getReqSum() << " = " << (int)ReqSum << endl;

				//cout << "CSTR=" << CSTR << ", "
				//	<< "CDEX=" << CDEX << ", "
				//	<< "CINT=" << CINT << endl;

				// player�� �ɷ�ġ�� �´� ���������� Ȯ���Ѵ�.
				if (CSTR >= ReqSTR
					&& CDEX >= ReqDEX
					&& CINT >= ReqINT
					&& CSUM >= ReqSum)
				{
					// �� option type���� �����Ѵ�.
					//cout << "OK!" << endl;
					break;
				}

			} while (--i);

			if (i==0)
			{
				optionType = 0;	//(rand()%3==0? 1: (rand()%2? 6:11));
			}
		}
		// ���� 	// �����Ѱ� ������ STR+1, DEX+1, INT+1 �߿��� �ϰų�..
		else optionType = 0;	//(rand()%3==0? 1: (rand()%2? 6:11));
	}
	//----------------------------------------------------------------------
	// Vampire�� ���
	//----------------------------------------------------------------------
	else if (pCreature->isVampire())
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
	
		Level_t	CLevel = pVampire->getLevel();

		// gamble�� �� �ִ� �Ѱ踦 �� �� ��������.
		CLevel += 3;

		// level����
		if (maxLevel!=0)
		{
			CLevel = min((int)maxLevel, (int)CLevel);
		}

		Attr_t    ReqLevel, ReqLevel2;
		Attr_t    ReqGender;


		// 10���� ��������.
		int i = 10;
		do
		{
			itemType = pInfoClass->getRandomItemType();

			// �� itemType�� �����ص� �Ǵ� level���� Ȯ���Ѵ�.
			pItemInfo = g_pItemInfoManager->getItemInfo(itemClass, itemType);

			ReqLevel2 = ReqLevel  = pItemInfo->getReqLevel();
			ReqGender = pItemInfo->getReqGender();

			// ���� ������ ���ų� ���� ������ ����
			// ������ �¾ƾ� �Ѵ�.
			if ((ReqLevel <= 0 || CLevel >= ReqLevel)
				&& (ReqGender==GENDER_BOTH
					|| pVampire->getSex()==MALE && ReqGender==GENDER_MALE
					|| pVampire->getSex()==FEMALE && ReqGender==GENDER_FEMALE)
				)
			{
				break;
			}

		} while (--i);

		if (i==0)
		{
			// ������ ���� �⺻ item type�� �ٸ���.
			if (Item::ITEM_CLASS_VAMPIRE_COAT && pVampire->getSex()==FEMALE)
			{
				itemType = 1;
			}
			else
			{
				itemType = 0;
			}
		}

		// �������� �ɼ��� ������ �ִٸ�, 
		// �ɼ��� ������ ���� �ɷ�ġ ������ �÷��ش�.
		int maxOptionLevel = max(1, min(100, (int)CLevel));

		const vector<OptionType_t>& optionVector = g_pOptionInfoManager->getPossibleGambleOptionVector((Item::ItemClass)itemClass, maxOptionLevel);
		vector<OptionType_t>::const_iterator iOption;

		// Total OptionRatio�� ���Ѵ�.
		int itemOptionRatio = g_pOptionInfoManager->getTotalGambleRatio((Item::ItemClass)itemClass, maxOptionLevel);

		/*
		cout << "optionVector[" << (int)itemClass << "][" << (int)maxOptionLevel << "] = (" << optionVector.size() << ") = ";

		for (iOption=optionVector.begin(); iOption!=optionVector.end(); iOption++)
		{
			cout << (int)*iOption << "  ";
		}
		cout << endl;
		*/


		if (optionVector.size()>0 && itemOptionRatio>0
			&& (pItemInfo==NULL || !pItemInfo->isUnique()))
		{
			// 10���� ��������.
			int i = 10;
			
			do {
				// random���� option�� �����Ѵ�.
				int optionRatio = random()%itemOptionRatio;
				int ratioSum      = 0;

				//cout << "Ratio = " << optionRatio << "/" << itemOptionRatio << endl;

				OptionInfo* pOptionInfo = NULL;

				for (iOption=optionVector.begin(); iOption!=optionVector.end(); iOption++)
				{
					optionType = *iOption;

					pOptionInfo = g_pOptionInfoManager->getOptionInfo( optionType );
					ratioSum += pOptionInfo->getRatio();

					if (optionRatio < ratioSum)
					{
						// �� option�� �����Ѵ�.
						break;
					}
				}

				// option�� �䱸 �ɷ�ġ�� ���ؼ�
				ReqLevel = ReqLevel2 + pOptionInfo->getReqLevel();

				// player�� �ɷ�ġ�� �´� ���������� Ȯ���Ѵ�.
				if (ReqLevel <= 0 || CLevel >= ReqLevel)
				{
					// �� option type���� �����Ѵ�.
					break;
				}

			} while (--i);

			if (i==0)
			{
				optionType = 0;//(rand()%3==0? 1: (rand()%2? 6:11));
			}
		}
		// ����!  // �����Ѱ� ������ STR+1, DEX+1, INT+1 �߿��� �ϰų�..
		else optionType = 0;//(rand()%3==0? 1: (rand()%2? 6:11));
	}
	//----------------------------------------------------------------------
	// Ousters�� ���
	//----------------------------------------------------------------------
	else if (pCreature->isOusters())
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
	
		Level_t	CLevel = pOusters->getLevel();

		// gamble�� �� �ִ� �Ѱ踦 �� �� ��������.
		CLevel += 3;

		// level����
		if (maxLevel!=0)
		{
			CLevel = min((int)maxLevel, (int)CLevel);
		}

		Attr_t    ReqLevel, ReqLevel2;

		// 10���� ��������.
		int i = 10;
		do
		{
			itemType = pInfoClass->getRandomItemType();

			// �� itemType�� �����ص� �Ǵ� level���� Ȯ���Ѵ�.
			pItemInfo = g_pItemInfoManager->getItemInfo(itemClass, itemType);

			ReqLevel2 = ReqLevel  = pItemInfo->getReqLevel();

			// ���� ������ ���ų� ���� ������ ����
			// ������ �¾ƾ� �Ѵ�.
			if ((ReqLevel <= 0 || CLevel >= ReqLevel))
			{
				break;
			}

		} while (--i);

		if (i==0)
		{
			itemType = 0;
		}

		// �������� �ɼ��� ������ �ִٸ�, 
		// �ɼ��� ������ ���� �ɷ�ġ ������ �÷��ش�.
		int maxOptionLevel = max(1, min(100, (int)CLevel));

		const vector<OptionType_t>& optionVector = g_pOptionInfoManager->getPossibleGambleOptionVector((Item::ItemClass)itemClass, maxOptionLevel);
		vector<OptionType_t>::const_iterator iOption;

		// Total OptionRatio�� ���Ѵ�.
		int itemOptionRatio = g_pOptionInfoManager->getTotalGambleRatio((Item::ItemClass)itemClass, maxOptionLevel);

		/*
		cout << "optionVector[" << (int)itemClass << "][" << (int)maxOptionLevel << "] = (" << optionVector.size() << ") = ";

		for (iOption=optionVector.begin(); iOption!=optionVector.end(); iOption++)
		{
			cout << (int)*iOption << "  ";
		}
		cout << endl;
		*/


		if (optionVector.size()>0 && itemOptionRatio>0
			&& (pItemInfo==NULL || !pItemInfo->isUnique()))
		{
			// 10���� ��������.
			int i = 10;
			
			do {
				// random���� option�� �����Ѵ�.
				int optionRatio = random()%itemOptionRatio;
				int ratioSum      = 0;

				//cout << "Ratio = " << optionRatio << "/" << itemOptionRatio << endl;

				OptionInfo* pOptionInfo = NULL;

				for (iOption=optionVector.begin(); iOption!=optionVector.end(); iOption++)
				{
					optionType = *iOption;

					pOptionInfo = g_pOptionInfoManager->getOptionInfo( optionType );
					ratioSum += pOptionInfo->getRatio();

					if (optionRatio < ratioSum)
					{
						// �� option�� �����Ѵ�.
						break;
					}
				}

				// option�� �䱸 �ɷ�ġ�� ���ؼ�
				ReqLevel = ReqLevel2 + pOptionInfo->getReqLevel();

				// player�� �ɷ�ġ�� �´� ���������� Ȯ���Ѵ�.
				if (ReqLevel <= 0 || CLevel >= ReqLevel)
				{
					// �� option type���� �����Ѵ�.
					break;
				}

			} while (--i);

			if (i==0)
			{
				optionType = 0;//(rand()%3==0? 1: (rand()%2? 6:11));
			}
		}
		// ����!  // �����Ѱ� ������ STR+1, DEX+1, INT+1 �߿��� �ϰų�..
		else optionType = 0;//(rand()%3==0? 1: (rand()%2? 6:11));
	}

	// item�� �����ؼ� �Ѱ��ش�.
	list<OptionType_t> optionTypes;
	if (optionType!=0)
		optionTypes.push_back( optionType );
	Item* pItem = g_pItemFactoryManager->createItem(itemClass, itemType, optionTypes);

	pItem->setGrade( min(6,ItemGradeManager::Instance().getRandomGambleGrade()) );

	return pItem;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// �ɼ��� ���� �� �ִ� �������ΰ�?
//////////////////////////////////////////////////////////////////////////////
bool isPossibleOptionItemClass(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_HELM :
		case Item::ITEM_CLASS_NECKLACE :
		case Item::ITEM_CLASS_RING :
		case Item::ITEM_CLASS_BRACELET :
		case Item::ITEM_CLASS_SHIELD :
		case Item::ITEM_CLASS_GLOVE :
		case Item::ITEM_CLASS_COAT :
		case Item::ITEM_CLASS_BELT :
		case Item::ITEM_CLASS_TROUSER :
		case Item::ITEM_CLASS_SHOES :
		case Item::ITEM_CLASS_SWORD :
		case Item::ITEM_CLASS_BLADE :
		case Item::ITEM_CLASS_CROSS :
		case Item::ITEM_CLASS_MACE :
		case Item::ITEM_CLASS_AR :
		case Item::ITEM_CLASS_SR :
		case Item::ITEM_CLASS_SG :
		case Item::ITEM_CLASS_SMG :
		case Item::ITEM_CLASS_CARRYING_RECEIVER :
		case Item::ITEM_CLASS_SHOULDER_ARMOR :

		case Item::ITEM_CLASS_VAMPIRE_NECKLACE :
		case Item::ITEM_CLASS_VAMPIRE_RING :
		case Item::ITEM_CLASS_VAMPIRE_BRACELET :
		case Item::ITEM_CLASS_VAMPIRE_EARRING :
		case Item::ITEM_CLASS_VAMPIRE_COAT :
		case Item::ITEM_CLASS_VAMPIRE_WEAPON :
		case Item::ITEM_CLASS_VAMPIRE_AMULET :
		case Item::ITEM_CLASS_DERMIS :
		case Item::ITEM_CLASS_PERSONA :

		case Item::ITEM_CLASS_OUSTERS_ARMSBAND:
		case Item::ITEM_CLASS_OUSTERS_BOOTS:
		case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
		case Item::ITEM_CLASS_OUSTERS_CIRCLET:
		case Item::ITEM_CLASS_OUSTERS_COAT:
		case Item::ITEM_CLASS_OUSTERS_PENDENT:
		case Item::ITEM_CLASS_OUSTERS_RING:
		case Item::ITEM_CLASS_OUSTERS_STONE:
		case Item::ITEM_CLASS_OUSTERS_WRISTLET:
		case Item::ITEM_CLASS_FASCIA :
		case Item::ITEM_CLASS_MITTEN :

		case Item::ITEM_CLASS_CORE_ZAP:

			return true;

		default :
			return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
// ���� �ܰ�� ���׷��̵�� �� �ִ� ItemType�ΰ�
//////////////////////////////////////////////////////////////////////////////
bool isPossibleUpgradeItemType(Item::ItemClass IClass)
{
	switch (IClass)
	{
		case Item::ITEM_CLASS_HELM :
		case Item::ITEM_CLASS_NECKLACE :
		case Item::ITEM_CLASS_RING :
		case Item::ITEM_CLASS_BRACELET :
		case Item::ITEM_CLASS_SHIELD :
		case Item::ITEM_CLASS_GLOVE :
		case Item::ITEM_CLASS_COAT :
		case Item::ITEM_CLASS_BELT :
		case Item::ITEM_CLASS_TROUSER :
		case Item::ITEM_CLASS_SHOES :
		case Item::ITEM_CLASS_SWORD :
		case Item::ITEM_CLASS_BLADE :
		case Item::ITEM_CLASS_CROSS :
		case Item::ITEM_CLASS_MACE :
		case Item::ITEM_CLASS_AR :
		case Item::ITEM_CLASS_SR :
		case Item::ITEM_CLASS_SG :
		case Item::ITEM_CLASS_SMG :

		case Item::ITEM_CLASS_VAMPIRE_NECKLACE :
		case Item::ITEM_CLASS_VAMPIRE_RING :
		case Item::ITEM_CLASS_VAMPIRE_BRACELET :
		case Item::ITEM_CLASS_VAMPIRE_EARRING :
		case Item::ITEM_CLASS_VAMPIRE_COAT :
		case Item::ITEM_CLASS_VAMPIRE_WEAPON :
		case Item::ITEM_CLASS_VAMPIRE_AMULET :

		case Item::ITEM_CLASS_OUSTERS_ARMSBAND:
		case Item::ITEM_CLASS_OUSTERS_BOOTS:
		case Item::ITEM_CLASS_OUSTERS_CHAKRAM:
		case Item::ITEM_CLASS_OUSTERS_CIRCLET:
		case Item::ITEM_CLASS_OUSTERS_COAT:
		case Item::ITEM_CLASS_OUSTERS_PENDENT:
		case Item::ITEM_CLASS_OUSTERS_RING:
		case Item::ITEM_CLASS_OUSTERS_STONE:
		case Item::ITEM_CLASS_OUSTERS_WRISTLET:

			return true;

		default :
			return false;
	}

	return false;
}

ItemType_t getUpgradeItemType(Item::ItemClass IClass, ItemType_t itemType, ItemType_t upgradeCount)
{
	if (upgradeCount==0)
		return itemType;

	InfoClassManager* pInfoClass = g_pItemInfoManager->getInfoManager(IClass);
	Assert(pInfoClass!=NULL);

	// ������ ���׷��̵� ������ DB�� ����. ���⼭�� �־��� ȸ����ŭ ���� ItemType���� �Űܰ���.
	ItemType_t newItemType = itemType;

	for ( int i=0; i<upgradeCount; i++ )
	{
		ItemInfo* pItemInfo = pInfoClass->getItemInfo( newItemType );
		Assert(pItemInfo!=NULL);

		newItemType = pItemInfo->getNextItemType();
	}

	//cout << "ItemType Upgrade By Luck: " << itemType << " --[+" << upgradeCount << "]--> ";

/*	int maxItemType = pInfoClass->getInfoCount()-1;

	// �̹� �ְ� �������� ���
	if (itemType==maxItemType)
	{
		//cout << itemType << "(max)" << endl;
		return itemType;
	}

	int itemTypeGap = 1;

	// ������ �ܰ� ������ 2�ܰ辿 �Ǿ� �ִ� ������
	if (IClass==Item::ITEM_CLASS_COAT
		|| IClass==Item::ITEM_CLASS_TROUSER
		|| IClass==Item::ITEM_CLASS_VAMPIRE_COAT)
	{
		itemTypeGap = 2;
	}

	int newItemType = min(maxItemType, itemType + upgradeCount*itemTypeGap);

	// 2�ܰ辿 �ǳʶ����� ���
	if (itemTypeGap==2
		&& (itemType & 0x01)!=(newItemType & 0x01)) newItemType -= 1;

	// �ְ� �������� ����ũ�� ���� �ִµ�.. �̰� ������..
	while (newItemType > itemType)
	{
		ItemInfo* pItemInfo = pInfoClass->getItemInfo( newItemType );
		Assert(pItemInfo!=NULL);

		// ����ũ���.. �� �ܰ辿 �����ش�.
		if (pItemInfo->isUnique()) newItemType-=itemTypeGap;
		else break;
	}

	//cout << newItemType << endl;*/

	return newItemType;
}

ItemType_t getDowngradeItemType(Item::ItemClass IClass, ItemType_t itemType)
{
	InfoClassManager* pInfoClass = g_pItemInfoManager->getInfoManager(IClass);
	Assert(pInfoClass!=NULL);

	for ( int i=0; i<pInfoClass->getInfoCount(); ++i )
	{
		ItemInfo* pItemInfo = pInfoClass->getItemInfo( i );
		Assert(pItemInfo!=NULL);

		if ( pItemInfo->getNextItemType() == itemType ) return i;
	}

	return itemType;
}

/*
//////////////////////////////////////////////////////////////////////////////
// ũ�������� Ʈ�� �̺�Ʈ��
//////////////////////////////////////////////////////////////////////////////
// Ʈ�� ������ �˻�
TPOINT checkEventTree( PlayerCreature* pPC, CoordInven_t iX, CoordInven_t iY )
{
	__BEGIN_TRY

	Assert( pPC != NULL );

	TPOINT pt;
	pt.x = -1;
	pt.y = -1;

	Inventory*		pInventory		= pPC->getInventory();
	Item*			pCurItem		= pInventory->getItem( iX, iY );

	if ( pCurItem == NULL )
		return pt;

	ItemType_t		itemType		= pCurItem->getItemType();

	CoordInven_t	startX = iX - itemType % 3; 
	CoordInven_t	startY = iY - itemType / 3;

	if ( pInventory->getWidth() - 3 < startX )
		return pt;
	if ( pInventory->getHeight() - 4 < startY )
		return pt;

	CoordInven_t curIX = 0, curIY = 0;
	ItemType_t compType = 0;

	// Ʈ�� ������ ����� ������ �ִ��� Ȯ���Ѵ�.
	for ( curIY = startY; curIY < startY + 4; curIY++ )
	{
		for ( curIX = startX; curIX < startX + 3; curIX++ )
		{
			pCurItem = pInventory->getItem( curIX, curIY );
			if ( pCurItem == NULL )
				return pt;

			if ( pCurItem->getItemClass() != Item::ITEM_CLASS_EVENT_TREE || 
				 pCurItem->getItemType() != compType )
				return pt;

			compType++;
		}
	}

	pt.x = startX;
	pt.y = startY;

	return pt;

	__END_CATCH
}

// ��빮��
TPOINT checkEventDocument( PlayerCreature* pPC, CoordInven_t iX, CoordInven_t iY )
{
	__BEGIN_TRY

	Assert( pPC != NULL );

	TPOINT pt;
	pt.x = -1;
	pt.y = -1;

	Inventory*		pInventory		= pPC->getInventory();
	Item*			pCurItem		= pInventory->getItem( iX, iY );

	if ( pCurItem == NULL )
		return pt;

	ItemType_t		itemType		= pCurItem->getItemType();

	// ��빮�� ������ 13���� �����Ѵ�
	itemType = itemType - 13;

	CoordInven_t	startX = iX - itemType % 3; 
	CoordInven_t	startY = iY - itemType / 3;

	if ( pInventory->getWidth() - 3 < startX )
		return pt;
	if ( pInventory->getHeight() - 4 < startY )
		return pt;

	CoordInven_t curIX = 0, curIY = 0;

	// ��빮�� ������ 13���� �����Ѵ�
	ItemType_t compType = 13;

	// ��� ���� ������ ����� ������ �ִ��� Ȯ���Ѵ�.
	for ( curIY = startY; curIY < startY + 4; curIY++ )
	{
		for ( curIX = startX; curIX < startX + 3; curIX++ )
		{
			pCurItem = pInventory->getItem( curIX, curIY );
			if ( pCurItem == NULL )
				return pt;

			if ( pCurItem->getItemClass() != Item::ITEM_CLASS_EVENT_TREE || 
				 pCurItem->getItemType() != compType )
				return pt;

			compType++;
		}
	}

	pt.x = startX;
	pt.y = startY;

	return pt;

	__END_CATCH
}

// ���� -_-;; �̰� �Ϲ�ȭ �ݹ� ��ų �� ������ ;; ���ڸ� �ϳ� �� �޵��� �ϸ� -_-;
// �㿡 ����Ʈ ���� �Ϲ�ȭ ��Ű���� ����. ��.��a
TPOINT checkEventDoll( PlayerCreature* pPC, CoordInven_t iX, CoordInven_t iY )
{
	__BEGIN_TRY

	Assert( pPC != NULL );

	TPOINT pt;
	pt.x = -1;
	pt.y = -1;

	Inventory*		pInventory		= pPC->getInventory();
	Item*			pCurItem		= pInventory->getItem( iX, iY );

	if ( pCurItem == NULL )
		return pt;

	ItemType_t		itemType		= pCurItem->getItemType();

	// ���� ������ 29���� �����Ѵ�
	itemType = itemType - 29;

	CoordInven_t	startX = iX - itemType % 3; 
	CoordInven_t	startY = iY - itemType / 3;

	if ( pInventory->getWidth() - 3 < startX )
		return pt;
	if ( pInventory->getHeight() - 4 < startY )
		return pt;

	CoordInven_t curIX = 0, curIY = 0;

	// ���� ������ 29���� �����Ѵ�
	ItemType_t compType = 29;

	// ��� ���� ������ ����� ������ �ִ��� Ȯ���Ѵ�.
	for ( curIY = startY; curIY < startY + 4; curIY++ )
	{
		for ( curIX = startX; curIX < startX + 3; curIX++ )
		{
			pCurItem = pInventory->getItem( curIX, curIY );
			if ( pCurItem == NULL )
				return pt;

			if ( pCurItem->getItemClass() != Item::ITEM_CLASS_EVENT_TREE || 
				 pCurItem->getItemType() != compType )
				return pt;

			compType++;
		}
	}

	pt.x = startX;
	pt.y = startY;

	return pt;

	__END_CATCH
}
*/

// �Ϲ�ȭ ��Ų �� checkEventTree �� checkEventDocument �� checkEventDoll �� ������
TPOINT checkEventPuzzle( PlayerCreature* pPC, CoordInven_t iX, CoordInven_t iY, int start)
{
	__BEGIN_TRY

	Assert( pPC != NULL );

	TPOINT pt;
	pt.x = -1;
	pt.y = -1;

	Inventory*		pInventory		= pPC->getInventory();
	Item*			pCurItem		= pInventory->getItem( iX, iY );

	if ( pCurItem == NULL )
		return pt;

	ItemType_t		itemType		= pCurItem->getItemType();

	itemType = itemType - start;

	CoordInven_t	startX = iX - itemType % 3; 
	CoordInven_t	startY = iY - itemType / 3;

	if ( pInventory->getWidth() - 3 < startX )
		return pt;
	if ( pInventory->getHeight() - 4 < startY )
		return pt;

	CoordInven_t curIX = 0, curIY = 0;

	ItemType_t compType = start;

	for ( curIY = startY; curIY < startY + 4; curIY++ )
	{
		for ( curIX = startX; curIX < startX + 3; curIX++ )
		{
			pCurItem = pInventory->getItem( curIX, curIY );
			if ( pCurItem == NULL )
				return pt;

			if ( pCurItem->getItemClass() != Item::ITEM_CLASS_EVENT_TREE || 
				 pCurItem->getItemType() != compType )
				return pt;

			compType++;
		}
	}

	pt.x = startX;
	pt.y = startY;

	return pt;

	__END_CATCH
}

// �κ��丮�� (X0, Y0) - (X1, y1) ������ �������� �����.
void deleteInventoryItem( Inventory* pInventory, CoordInven_t invenX0, CoordInven_t invenY0, CoordInven_t invenX1, CoordInven_t invenY1 )
{
	__BEGIN_TRY
	
	CoordInven_t curIX = 0, curIY = 0;
	Item* pCurItem = 0;

	// ������ Ʈ�� ������ �����.
	for ( curIY = invenY0; curIY <= invenY1; curIY++ )
	{
		for ( curIX = invenX0; curIX <= invenX1; curIX++ )
		{
			pCurItem = pInventory->getItem( curIX, curIY );

			if ( pCurItem != NULL )
			{
				// �κ��丮���� �����.
				pInventory->deleteItem( pCurItem->getObjectID() );

				// DB ���� ������.
				pCurItem->destroy();

				SAFE_DELETE( pCurItem );
			}
		}
	}

	__END_CATCH
}

typedef struct {
	Item::ItemClass itemClass;
	ItemType_t		itemType;
	CoordInven_t	x;
	CoordInven_t	y;
	ItemNum_t		num;
} NewbieItem;

const int maxNewbieItemNum = 8;

const NewbieItem NewbieItems[maxNewbieItemNum] =
{
	{ Item::ITEM_CLASS_SWORD,	0, 4, 3, 1 },
	{ Item::ITEM_CLASS_BLADE,	0, 2, 3, 1 },
	{ Item::ITEM_CLASS_CROSS,	0, 0, 3, 1 },
	{ Item::ITEM_CLASS_MACE,	0, 0, 0, 1 },
	{ Item::ITEM_CLASS_AR,		0, 2, 0, 1 },
	{ Item::ITEM_CLASS_MAGAZINE,2, 4, 0, 20 },
	{ Item::ITEM_CLASS_POTION,	0, 9, 4, 9 },
	{ Item::ITEM_CLASS_POTION,	5, 9, 5, 9 },
};

// �κ��丮�� �ʺ��ڿ� �������� �־��ش�.
bool addNewbieItemToInventory( Slayer* pSlayer, bool sendPacket )
	
{
	__BEGIN_TRY

	if( sendPacket )
	{
		filelog("NewbieItemError.log", "Someone request packet to addNewbieItemToInventory() function!");
		return false;
	}

	Zone* pZone = pSlayer->getZone();
	Inventory* pInventory = pSlayer->getInventory();
	ObjectRegistry& objectRegister = pZone->getObjectRegistry();

	if( pInventory == NULL ) return false;
	if( pZone == NULL ) return false;

	if( pInventory->getItemNum() != 0 ) return false;

	list<OptionType_t> olist;
	GCCreateItem gcCreateItem;

	Item::ItemClass bestWeapon = getBestNewbieWeaponClass( pSlayer );

	for( int i=0; i<maxNewbieItemNum; i++ )
	{
		Item* pItem = g_pItemFactoryManager->createItem( NewbieItems[i].itemClass, NewbieItems[i].itemType, olist );
		pItem->setCreateType( Item::CREATE_TYPE_GAME );
		objectRegister.registerObject( pItem );

		pItem->setNum( NewbieItems[i].num );

		bool weared = false;

		if( pItem->getItemClass() == bestWeapon )
		{

			if( !pSlayer->isWear( Slayer::WEAR_RIGHTHAND ) )
			{
				pSlayer->wearItem( Slayer::WEAR_RIGHTHAND , pItem );
				pItem->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_RIGHTHAND, 0, pItem->getItemID() );
				weared = true;
			}
			
		}
		if( !weared )
		if( pInventory->addItem( NewbieItems[i].x, NewbieItems[i].y, pItem ) )
		{
			pItem->create( pSlayer->getName(), STORAGE_INVENTORY, 0, NewbieItems[i].x, NewbieItems[i].y, pItem->getItemID() );

			if( sendPacket )
			{
			/*gcCreateItem.setObjectID( pItem->getObjectID() );
			gcCreateItem.setItemClass( pItem->getItemClass() );
			gcCreateItem.setItemType( pItem->getItemType() );
			gcCreateItem.setObjectType( pItem->getOptionTypeList() );
			gcCreateItem.setDurability( pItem->getDurability() );
			gcCreateItem.setSilver( pItem->getSilver() );
			if (pItem->getItemClass() == Item::ITEM_CLASS_MAGAZINE)
			{
				Magazine* pMag = dynamic_cast<Magazine*>(pItem);
				gcCreateItem.setItemNum(pMag->getNum());
			}
			else
			{
				gcCreateItem.setItemNum(pItem->getNum());
			}

			gcCreateItem.setInvenX( NewbieItems[i][2] );
			gcCreateItem.setInvenY( NewbieItems[i][3] );

			pPlayer->sendPacket( &gcCreateItem );*/
			}
		}
	}

	return true;
	
	__END_CATCH
}

bool addNewbieGoldToInventory( Slayer* pSlayer, bool sendPacket )
	
{
	__BEGIN_TRY

	if( sendPacket )
	{
		filelog("NewbieItemError.log", "Someone request packet to addNewbieGoldToInventory() function!");
		return false;
	}

	if( pSlayer == NULL ) return false;
	if( pSlayer->getGold() != 0 ) return false;

	pSlayer->setGoldEx(500);

	return true;

	__END_CATCH
}

bool addNewbieItemToGear( Slayer* pSlayer, bool sendPacket )
	
{
	__BEGIN_TRY

	if( sendPacket )
	{
		filelog("NewbieItemError.log", "Someone request packet to addNewbieItemToGear() function!");
		return false;
	}

	if( pSlayer == NULL ) return false;

	Zone* pZone = pSlayer->getZone();
	ObjectRegistry& objectRegister = pZone->getObjectRegistry();

	if( pZone == NULL ) return false;
	
	list<OptionType_t> olist;

	if( !pSlayer->isWear( Slayer::WEAR_BODY ) && !pSlayer->isWear( Slayer::WEAR_LEG ) )
	{
		Item* pCoat = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_COAT, ((pSlayer->getSex()==MALE)?0:1), olist );
		Item* pTrouser = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_TROUSER, ((pSlayer->getSex()==MALE)?0:1), olist );
		pCoat->setCreateType( Item::CREATE_TYPE_GAME );
		pTrouser->setCreateType( Item::CREATE_TYPE_GAME );

		objectRegister.registerObject( pCoat );
		objectRegister.registerObject( pTrouser );

		pCoat->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_BODY, 0, pCoat->getItemID() );
		pTrouser->create( pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_LEG, 0, pTrouser->getItemID() );
		
		pSlayer->wearItem( Slayer::WEAR_BODY, pCoat );
		pSlayer->wearItem( Slayer::WEAR_LEG , pTrouser );
	}

	return true;
	
	__END_CATCH
}

bool addNewbieGoldToInventory( Ousters* pOusters, bool sendPacket /*= false*/ ) 
{
	__BEGIN_TRY

	if( sendPacket )
	{
		filelog("NewbieItemError.log", "Someone request packet to addNewbieItemToInventory() function!");
		return false;
	}

	if( pOusters == NULL ) return false;
	if( pOusters->getGold() != 0 ) return false;

	pOusters->setGoldEx(500);

	return true;

	__END_CATCH
}

bool addNewbieItemToInventory( Ousters* pOusters, bool sendPacket /*= false */) 
{
	__BEGIN_TRY

	if( sendPacket )
	{
		filelog("NewbieItemError.log", "Someone request packet to addNewbieGoldToInventory() function!");
		return false;
	}

	if( pOusters == NULL ) return false;

	Zone* pZone = pOusters->getZone();
	if ( pZone == NULL ) return false;
	
	Inventory* pInventory = pOusters->getInventory();
	if ( pInventory == NULL ) return false;

	if ( pInventory->getItemNum() != 0 ) return false;

	Item* pPupa = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_PUPA, 0, list<OptionType_t>() );
	Item* pLarva = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_LARVA, 0, list<OptionType_t>() );

	Assert( pPupa != NULL );
	Assert( pLarva != NULL );

	pPupa->setNum(9);
	pLarva->setNum(9);
	pPupa->setCreateType( Item::CREATE_TYPE_GAME );
	pLarva->setCreateType( Item::CREATE_TYPE_GAME );

	pZone->registerObject( pPupa );
	pZone->registerObject( pLarva );
	
	_TPOINT tp;
	pInventory->addItem( pPupa, tp );
	pPupa->create( pOusters->getName(), STORAGE_INVENTORY, 0, tp.x, tp.y, pPupa->getItemID() );
	pInventory->addItem( pLarva, tp );
	pLarva->create( pOusters->getName(), STORAGE_INVENTORY, 0, tp.x, tp.y, pLarva->getItemID() );

	return true;

	__END_CATCH
}

bool addNewbieItemToGear( Ousters* pOusters, bool sendPacket /*= false */) 
{
	__BEGIN_TRY

	if( sendPacket )
	{
		filelog("NewbieItemError.log", "Someone request packet to addNewbieItemToInventory() function!");
		return false;
	}

	if( pOusters == NULL ) return false;
	Zone* pZone = pOusters->getZone();
	Assert( pZone != NULL );

	if ( pOusters->getWearItem(Ousters::WEAR_RIGHTHAND) != NULL ) return false;

	Item* pWeapon = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_OUSTERS_CHAKRAM, 0, list<OptionType_t>() );
	Assert( pWeapon != NULL );

	pWeapon->setCreateType( Item::CREATE_TYPE_GAME );
	pZone->registerObject( pWeapon );

	pOusters->wearItem(Ousters::WEAR_RIGHTHAND, pWeapon);
	pWeapon->create( pOusters->getName(), STORAGE_GEAR, 0, Ousters::WEAR_RIGHTHAND, 0, pWeapon->getItemID() );

	return true;

	__END_CATCH
}

Item::ItemClass getBestNewbieWeaponClass(Slayer* pSlayer)
	
{
	__BEGIN_TRY

	Assert(pSlayer!=NULL);

	Attr_t STR = pSlayer->getSTR();
	Attr_t DEX = pSlayer->getDEX();
	Attr_t INT = pSlayer->getINT();

	// STR
	if (STR>=DEX && STR>=INT)
	{
		return (rand()%2? Item::ITEM_CLASS_SWORD : Item::ITEM_CLASS_BLADE);
	}
	// DEX
	else if (DEX>=STR && DEX>=INT)
	{
		return Item::ITEM_CLASS_AR;
	}

	// INT
	return (rand()%2? Item::ITEM_CLASS_CROSS : Item::ITEM_CLASS_MACE);


	__END_CATCH
}

void makeOptionList(const string& options, list<OptionType_t>& optionList)
	
{
	size_t a = 0, b = 0;

	//////////////////////////////////////////////
	// DEX+1,INT+2
	// a     ba     b
	//////////////////////////////////////////////
	optionList.clear();
	if (options.size()<=1) return;

	do
	{
		b = options.find_first_of(',', a);

		string  optionName = trim( options.substr(a, b-a) );

		OptionType_t optionType;
		
		try {
			optionType = g_pOptionInfoManager->getOptionType(optionName);
		} catch (NoSuchElementException&) {
			throw Error("�׷� �ɼ��� ���ܴ�.");
		}

		optionList.push_back( optionType );

		a = b+1;

	} while (b!=string::npos && b < options.size() -1);
}

void
saveDissectionItem(Creature* pCreature, Item* pTreasure, int x, int y)
	
{
	__BEGIN_TRY

	Assert(pCreature!=NULL);
	Assert(pTreasure!=NULL);

	// relic�� �ƴ� ��츸.. DB�� �������� �����Ѵ�.
	// ���� ������ ��� �̹� DB�� �����Ƿ� DB�� ������Ʈ���ش�.
	switch (pTreasure->getItemClass())
	{	
		case Item::ITEM_CLASS_RELIC:
		{
			// Relic�� DB�� ������ �ʿ� ����.
		}
		break;

		case Item::ITEM_CLASS_BLOOD_BIBLE:
		case Item::ITEM_CLASS_CASTLE_SYMBOL:
		case Item::ITEM_CLASS_SWEEPER:
		{
			char query[128];

			sprintf( query, "ObjectID = %lu, Storage=%u, StorageID=%u, X=%u, Y=%u",
					pTreasure->getObjectID(), STORAGE_ZONE, pCreature->getZone()->getZoneID(), x, y);
			pTreasure->tinysave( query );
		}
		break;

		default:
		{
			ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( pTreasure->getItemClass(), pTreasure->getItemType() );
			Assert(pItemInfo!=NULL);

			// ����ũ �������� ����
			// ������ ��ü�� ����ũ ������ ���ְ�
			// DB�� ����ũ �������� ������ ��������ش�.
			//
			// (*) ���Ͱ� �׾��� ��,
			//     ���� �ȿ� �ִ� �����ۿ��� ����ũ ������ ���ϰ�
			//     DB���� ���� ������ ���Ѵ�. �׷���, �����ٶ��� �����Ѵ�.
			//     ���� ����ũ �������� ���͸� ���ؼ��� ��Ÿ����
			//     CGDissectionCorpse�� ���ؼ� ����(!)�ǰ�
			//     EffectDecayItem�� ���ؼ��� ���ŵȴ�.

			if (pItemInfo->isUnique())
			{
				pTreasure->setUnique();
				UniqueItemManager::createItem(pTreasure->getItemClass(), pTreasure->getItemType());
				filelog("uniqueItem.txt", "[CGDissectionCorpse] %s %s", pCreature->getName().c_str(), pTreasure->toString().c_str());
			}

			// ������ ItemID�� �״�� �����Ѵ�.
			// ItemID�� 0�̸�.. create()�Ҷ� �ٽ� ItemID�� �޴´�.
			// by sigi. 2002.10.28
			pTreasure->create("", STORAGE_ZONE, pCreature->getZone()->getZoneID(), x, y, pTreasure->getItemID() );
		}
	}

	__END_CATCH
}

bool canDecreaseDurability( Item* pItem )
	
{
	__BEGIN_TRY

	if ( pItem == NULL ) return false;
	if ( pItem->isUnique() ) return false;
	if ( pItem->isTimeLimitItem() ) return false;
	if ( pItem->isQuestItem() ) return false;
	if ( pItem->isFlagItem() ) return false;

	switch ( pItem->getItemClass() )
	{
		case Item::ITEM_CLASS_VAMPIRE_AMULET:
		case Item::ITEM_CLASS_COUPLE_RING:
		case Item::ITEM_CLASS_VAMPIRE_COUPLE_RING:
		case Item::ITEM_CLASS_SWEEPER:
		case Item::ITEM_CLASS_CORE_ZAP:
		case Item::ITEM_CLASS_CARRYING_RECEIVER:
		case Item::ITEM_CLASS_DERMIS:
		case Item::ITEM_CLASS_FASCIA:
			return false;
		default:
			break;
	}
	return true;
		
	__END_CATCH
}

bool canSell( Item* pItem )
{



	if ( pItem==NULL ) return false;
	if ( pItem->isTimeLimitItem() ) return true;

	if ( pItem->isUnique() ) return false;
	if ( isCoupleRing( pItem ) ) return false;


	if ( pItem->isQuestItem() ) return false;
	if ( pItem->isFlagItem() ) return false;
	// ����Ʈ �������� 50���� �� �� �ִ�.
	//if ( pItem->isTimeLimitItem() ) return false;

	Item::ItemClass itemClass = pItem->getItemClass();

	if ( itemClass==Item::ITEM_CLASS_MOTORCYCLE
		|| itemClass==Item::ITEM_CLASS_KEY
		|| itemClass==Item::ITEM_CLASS_CORPSE
		|| itemClass==Item::ITEM_CLASS_MONEY
		|| itemClass==Item::ITEM_CLASS_PET_ITEM
		//          || itemClass==Item::ITEM_CLASS_EVENT_GIFT_BOX
		|| isRelicItem( itemClass )
	)
		return false;
	if ( itemClass == Item::ITEM_CLASS_SWEEPER ) return false;

	// edit by coffee 2007-7-7 �޸�������Ʒ ��������Ϊ�ɳ���
	if ( itemClass==Item::ITEM_CLASS_EVENT_ITEM && pItem->getItemType() == 31 ) return true;

	if ( itemClass==Item::ITEM_CLASS_EVENT_ITEM && pItem->getItemType() != 28 ) return false;

	return true;
}

bool canPutInStash( Item* pItem )
{
	if ( pItem==NULL ) return false;
	if ( pItem->isUnique() ) return false;
	if ( pItem->isTimeLimitItem() ) return false;
	if ( isRelicItem( pItem ) ) return false;
	if ( isCoupleRing( pItem ) ) return false;
	if ( pItem->isQuestItem() ) return false;
	if ( pItem->isFlagItem() ) return false;

	Item::ItemClass itemClass = pItem->getItemClass();

	if ( itemClass == Item::ITEM_CLASS_EVENT_ITEM ) return false;
	if ( itemClass == Item::ITEM_CLASS_SWEEPER ) return false;

	if ( itemClass == Item::ITEM_CLASS_LUCKY_BAG && pItem->getItemType() == 3 ) return false;
	if ( itemClass == Item::ITEM_CLASS_EVENT_ITEM && pItem->getItemType() == 28 ) return false;

	return true;
}

bool canTrade( Item* pItem )
{
	if ( pItem==NULL ) return false;
	if ( isRelicItem( pItem ) ) return false;
	if ( isCoupleRing( pItem ) ) return false;
	if ( pItem->isTimeLimitItem() ) return false;
	if ( pItem->isQuestItem() ) return false;
	if ( pItem->isFlagItem() ) return false;

	Item::ItemClass itemClass = pItem->getItemClass();
	ItemType_t itemType = pItem->getItemType();

	if ( itemClass == Item::ITEM_CLASS_EVENT_ITEM )
		return false;
	if ( itemClass == Item::ITEM_CLASS_SWEEPER ) return false;

	// �ݴ� ī��� Ʈ���̵� �� �� ����.
	if ( itemClass == Item::ITEM_CLASS_MOON_CARD && pItem->getItemType() == 0 )
		return false;

	// �����̾� ü��� ���� -_-
	if ( itemClass == Item::ITEM_CLASS_LUCKY_BAG && pItem->getItemType() == 3 ) return false;
	if ( itemClass == Item::ITEM_CLASS_EVENT_ITEM && pItem->getItemType() == 28 ) return false;
	if ( itemClass == Item::ITEM_CLASS_EFFECT_ITEM && pItem->getItemType() >= 4 && pItem->getItemType() <= 6 ) return false;

	// �̺�Ʈ ������ ��ȯ �Ұ�.
	if ( itemClass == Item::ITEM_CLASS_EVENT_STAR && ( itemType >= 17 && itemType <= 21 ) )
		return false;

	// ������ ������ ��ȯ �Ұ�
	if ( itemClass == Item::ITEM_CLASS_MIXING_ITEM && itemType == 18 )
		return false;

	return true;
}
bool isCoupleRing( Item* pItem )
{
	switch ( pItem->getItemClass() )
	{
		case Item::ITEM_CLASS_COUPLE_RING:
		case Item::ITEM_CLASS_VAMPIRE_COUPLE_RING:
			return true;
		default:
			return false;
	}
}

bool suitableItemClass( Item::ItemClass iClass, SkillDomainType_t domainType )
{
	switch ( domainType )
	{
		case SKILL_DOMAIN_BLADE:
			if ( iClass == Item::ITEM_CLASS_BLADE ) return true;
			return false;
			
		case SKILL_DOMAIN_SWORD:
			if ( iClass == Item::ITEM_CLASS_SWORD ) return true;
			return false;
			
		case SKILL_DOMAIN_GUN:
			if ( iClass == Item::ITEM_CLASS_AR ||
				 iClass == Item::ITEM_CLASS_SR ||
				 iClass == Item::ITEM_CLASS_SMG ||
				 iClass == Item::ITEM_CLASS_SG ) return true;
			return false;
			
		case SKILL_DOMAIN_HEAL:
			if ( iClass == Item::ITEM_CLASS_CROSS ) return true;
			return false;
			
		case SKILL_DOMAIN_ENCHANT:
			if ( iClass == Item::ITEM_CLASS_MACE ) return true;
			return false;
			
		case SKILL_DOMAIN_ETC:
			return false;
			
		case SKILL_DOMAIN_VAMPIRE:
			if ( iClass == Item::ITEM_CLASS_VAMPIRE_WEAPON ) return true;
			return false;
			
		default:
			return false;
	}

	Assert( false );
}

void setItemGender( Item* pItem, GenderRestriction gender )
{
	if ( gender == GENDER_BOTH || gender == GENDER_MAX ) return;

	ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( pItem->getItemClass(), pItem->getItemType() );
	if ( pItemInfo->getReqGender() == gender ) return;
	if ( pItemInfo->getReqGender() == GENDER_BOTH || pItemInfo->getReqGender() == GENDER_MAX ) return;

	int genderDiff = (int)gender - (int)pItemInfo->getReqGender();
	Assert( genderDiff == 1 || genderDiff == -1 );

	pItem->setItemType( pItem->getItemType() + genderDiff );
}

bool bTraceLog( Item* pItem )
{
	Item::ItemClass iClass = pItem->getItemClass();

	// PetItem �� ������ �����
	if ( iClass == Item::ITEM_CLASS_PET_ITEM || iClass == Item::ITEM_CLASS_CORE_ZAP )
		return true;

	// ������ �Ķ� �����̶� ��� ������ �����
	if ( iClass == Item::ITEM_CLASS_POTION &&
			( pItem->getItemType() == 10 || pItem->getItemType() == 11 ) )
		return true;

	// Serum �� ���� ������ �����
	if ( iClass == Item::ITEM_CLASS_SERUM && 
			( pItem->getItemType() == 4 || pItem->getItemType() == 5 ) )
		return true;

	switch ( iClass )
	{
		case Item::ITEM_CLASS_CARRYING_RECEIVER:
		case Item::ITEM_CLASS_SHOULDER_ARMOR:
		case Item::ITEM_CLASS_DERMIS:
		case Item::ITEM_CLASS_PERSONA:
		case Item::ITEM_CLASS_FASCIA:
		case Item::ITEM_CLASS_MITTEN:
			return true;
			break;
		default:
			break;
	}

	if ( iClass == Item::ITEM_CLASS_MOTORCYCLE ||
		 iClass == Item::ITEM_CLASS_POTION ||
		 iClass == Item::ITEM_CLASS_WATER ||
		 iClass == Item::ITEM_CLASS_HOLYWATER ||
		 iClass == Item::ITEM_CLASS_ETC ||
		 iClass == Item::ITEM_CLASS_KEY ||
		 iClass == Item::ITEM_CLASS_MAGAZINE ||
		 iClass == Item::ITEM_CLASS_BOMB_MATERIAL ||
		 iClass == Item::ITEM_CLASS_BOMB ||
		 iClass == Item::ITEM_CLASS_MINE ||
		 iClass == Item::ITEM_CLASS_LEARNINGITEM ||
		 iClass == Item::ITEM_CLASS_MONEY ||
		 iClass == Item::ITEM_CLASS_CORPSE ||
		 iClass == Item::ITEM_CLASS_SKULL ||
		 iClass == Item::ITEM_CLASS_SERUM ||
		 iClass == Item::ITEM_CLASS_VAMPIRE_ETC ||
		 iClass == Item::ITEM_CLASS_SLAYER_PORTAL_ITEM ||
		 iClass == Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM ||
		 iClass == Item::ITEM_CLASS_RELIC ||
		 iClass == Item::ITEM_CLASS_BLOOD_BIBLE ||
		 iClass == Item::ITEM_CLASS_CASTLE_SYMBOL ||
		 iClass == Item::ITEM_CLASS_DYE_POTION ||
		 iClass == Item::ITEM_CLASS_RESURRECT_ITEM ||
		 iClass == Item::ITEM_CLASS_SWEEPER ||
		 pItem->isTimeLimitItem() ) return false;

	const list<OptionType_t>& optionList = pItem->getOptionTypeList();
	list<OptionType_t>::const_iterator itr;

	// ���� �ɼ��� �ִ� �� ��� �����
	for (itr=optionList.begin(); itr!=optionList.end(); itr++)
	{
		OptionInfo* pOptionInfo = g_pOptionInfoManager->getOptionInfo( *itr );
		if (pOptionInfo==NULL) return false;

		OptionClass optionClass = pOptionInfo->getClass();

		if ( optionClass == OPTION_POISON ||
			 optionClass == OPTION_ACID ||
			 optionClass == OPTION_CURSE ||
			 optionClass == OPTION_BLOOD ) return true;
	}

	// ����� ���Ʈ�� ��� �����
	// Event Star �� ��� �����
	if ( iClass == Item::ITEM_CLASS_QUEST_ITEM ||
		 iClass == Item::ITEM_CLASS_EVENT_STAR ||
		 iClass == Item::ITEM_CLASS_MIXING_ITEM ) return true;

	// �� ���� �������� ��� 3�� ���ϴ� ��� ������ �ʴ´�
	if ( (int)(pItem->getItemType()) < 3 ) return false;

	return true;
}

void remainTraceLog ( Item* pItem, const string& preOwner, const string& owner, ItemTraceLogType logType, ItemTraceDetailType detailType )
	
{
	__BEGIN_TRY

	Assert( pItem != NULL);

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		string optionName = getOptionTypeToString(pItem->getOptionTypeList());

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery(
				"INSERT INTO ItemTraceLog (ItemID, ItemClass, ItemType, OptionType, PreOwnerID, OwnerID, LogType, DetailType, Time) VALUES ( %u,'%s',%u,'%s','%s','%s','%s','%s',now() )",
				pItem->getItemID(),
				ItemClass2ShortString[ (int)(pItem->getItemClass()) ].c_str(),
				pItem->getItemType(),
				optionName.c_str(),
				preOwner.c_str(),
				owner.c_str(),
				ItemTraceLogType2String[ (int)logType ].c_str(),
				ItemTraceLogDetailType2String[ (int)detailType ].c_str()
				);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

void remainTraceLogNew ( Item* pItem, const string& owner, ITLType logType, ITLDType detailType, ZoneID_t zid /*=0*/, int x /*=0*/, int y /*=0 */)
	
{
	__BEGIN_TRY

	Assert( pItem != NULL);

/*	Statement* pStmt = NULL;

	BEGIN_DB
	{
		string optionName = getOptionTypeToString(pItem->getOptionTypeList());

		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery(
				"INSERT INTO ItemTrace2Log (ItemID, ItemClass, ItemType, OptionType, OwnerID, ActionType, DetailType, Zone, X, Y ,Time) VALUES ( %u,'%s',%u,'%s','%s','%s','%s','%s','%d','%d','%d',now() )",
				pItem->getItemID(),
				ItemClass2ShortString[ (int)(pItem->getItemClass()) ].c_str(),
				pItem->getItemType(),
				optionName.c_str(),
				owner.c_str(),
				ITLType2String[ (int)logType ].c_str(),
				ITLDType2String[ (int)detailType ].c_str(),
				zid,
				x,
				y
				);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
*/
	__END_CATCH
}

void remainMoneyTraceLog ( const string& preOwner, const string& owner, ItemTraceLogType logType, ItemTraceDetailType detailType, int amount )
	
{
	__BEGIN_TRY

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery(
				"INSERT INTO MoneyTraceLog (PreOwnerID, OwnerID, LogType, DetailType, Amount, Time) VALUES ( '%s','%s','%s','%s', %d, now() )",
				preOwner.c_str(),
				owner.c_str(),
				ItemTraceLogType2String[ (int)logType ].c_str(),
				ItemTraceLogDetailType2String[ (int)detailType ].c_str(),
				amount
				);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	__END_CATCH
}

// Web ���� �� �������� ����� �Լ�
Item* createItemByGoodsID( DWORD goodsID )
{
	GoodsInfo* pGoodsInfo = g_pGoodsInfoManager->getGoodsInfo( goodsID );
	if ( pGoodsInfo == NULL )
	{
		filelog( "buyItemBug.txt", "buyID(%d) �� �ش��ϴ� ��ǰ�� �����ϴ�.", (int)goodsID );
		return NULL;
	}

	Item::ItemClass ItemClass = pGoodsInfo->getItemClass();
	ItemType_t ItemType = pGoodsInfo->getItemType();
	Grade_t Grade = pGoodsInfo->getGrade();
	list<OptionType_t> optionTypeList = pGoodsInfo->getOptionTypeList();
	int Num = pGoodsInfo->getNum();
	bool bTimeLimit = pGoodsInfo->isTimeLimit();
	int Hour = pGoodsInfo->getHour();

	if ( !g_pItemInfoManager->isPossibleItem( ItemClass, ItemType, optionTypeList ) )
	{
		filelog( "buyItemBug.txt", "buyID(%d) �� �ش��ϴ� �������� ���� �� �����ϴ�.", (int)goodsID );
		return NULL;
	}

	Item* pItem	= g_pItemFactoryManager->createItem( ItemClass, ItemType, optionTypeList );
	if ( pItem == NULL )
	{
		filelog( "buyItemBug.txt", "buyID(%d) �� �ش��ϴ� ������ ����⿡ �����߽��ϴ�.", (int)goodsID );
		return NULL;
	}

	pItem->setGrade(Grade);
	pItem->setNum(Num);
	pItem->setTimeLimitItem( bTimeLimit );
	pItem->setHour( Hour );
	pItem->setCreateType( Item::CREATE_TYPE_MALL );

	if ( ItemClass == Item::ITEM_CLASS_PET_ITEM )
	{
		PetItem* pPetItem = dynamic_cast<PetItem*>(pItem);
		Assert( pPetItem != NULL );

		PetType_t petType = ItemType;
		PetTypeInfo* pPetTypeInfo = PetTypeInfoManager::getInstance()->getPetTypeInfo(petType);
		PetExpInfo* pPetExpInfo = PetExpInfoManager::Instance().getPetExpInfo(48);//modify by viva for PetInfo
		if ( pPetTypeInfo == NULL || pPetExpInfo == NULL )
		{
			filelog( "buyItemBug.txt", "buyID(%d) �� �ش��ϴ� �� ������ ������ �̻��մϴ�.", (int)goodsID );
			SAFE_DELETE( pItem );
			return NULL;
		}

		PetInfo* pPetInfo = new PetInfo;

		pPetInfo->setPetType( petType );
		pPetInfo->setPetLevel(49);//modify by viva for PetInfo
		pPetInfo->setPetCreatureType(pPetTypeInfo->getPetCreatureType(49));//modify by viva for PetInfo
		pPetInfo->setPetAttr(23);//modify by viva for PetInfo
		pPetInfo->setPetExp( pPetExpInfo->getPetGoalExp() );
		//pPetInfo->setPetExp(1999998000);
		pPetInfo->setPetAttrLevel(11);//modify by viva for PetInfo
		pPetInfo->setFoodType(0);
		pPetInfo->setGamble(1);//modify by viva for PetInfo
		pPetInfo->setCutHead(0);//modify by viva for PetInfo
		pPetInfo->setAttack(1);//modify by viva for PetInfo
		pPetInfo->setPetHP(5760);
		pPetInfo->setFeedTime( VSDateTime::currentDateTime() );

		// ����� ��ũ
		pPetItem->setPetInfo( pPetInfo );
		pPetInfo->setPetItem( pPetItem );
	}

	return pItem;
}

bool bWinPrize( DWORD rewardID, DWORD questLevel )
{
	bool Lotto = false;
	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery(
				"UPDATE EventQuestRewardSchedule SET Count = Count - 1 WHERE Count > 0 AND RewardID = %d AND QuestLevel = %d AND Time < now() LIMIT 1", rewardID, questLevel );

		if ( pStmt->getAffectedRowCount() > 0 )
			Lotto = true;

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	return Lotto;
}

void deleteFlagEffect( Corpse* pFlagPole, Item* pFlag )
{
	if ( pFlag == NULL ) return;
	if ( !pFlag->isFlagItem() ) return;

	if ( !pFlagPole->isFlag( Effect::EFFECT_CLASS_FLAG_INSERT ) ) return;
	Effect* pEffect = pFlagPole->getEffectManager().findEffect(Effect::EFFECT_CLASS_FLAG_INSERT);
	if ( pEffect != NULL ) pEffect->setDeadline(0);
}

void countResurrectItem()
{
	__BEGIN_TRY
	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();

		pStmt->executeQuery(
				"UPDATE ResurrectItemCount SET Count=Count+1");

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	__END_CATCH
}

Item* fitToPC( Item* pItem, PlayerCreature* pPC )
{
	if ( pItem == NULL || pPC == NULL ) return pItem;

	if ( isSlayerWeapon( pItem->getItemClass() ) && pPC->isSlayer() )
	{
		Item::ItemClass targetClass = Item::ITEM_CLASS_MAX;
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		int add = 0;
		switch ( pSlayer->getHighestSkillDomain() )
		{
			case SKILL_DOMAIN_BLADE:
				{
					targetClass = Item::ITEM_CLASS_BLADE;
				}
				break;
			case SKILL_DOMAIN_SWORD:
				{
					targetClass = Item::ITEM_CLASS_SWORD;
				}
				break;
			case SKILL_DOMAIN_GUN:
				{
					targetClass = Item::ITEM_CLASS_AR;
				}
				break;
			case SKILL_DOMAIN_HEAL:
				{
					targetClass = Item::ITEM_CLASS_CROSS;
					add = -2;
				}
				break;
			case SKILL_DOMAIN_ENCHANT:
				{
					targetClass = Item::ITEM_CLASS_MACE;
					add = -2;
				}
				break;
			default:
				break;
		}

		if ( targetClass != Item::ITEM_CLASS_MAX && targetClass != pItem->getItemClass() )
		{
			Item* pNewItem = g_pItemFactoryManager->createItem( targetClass, pItem->getItemType() + add, pItem->getOptionTypeList() );
			if ( pNewItem != NULL )
			{
				SAFE_DELETE( pItem );
				pItem = pNewItem;
			}
		}
	}

	if ( isOustersWeapon( pItem->getItemClass() ) && pPC->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
		ElementalDomain maxDomain = ELEMENTAL_DOMAIN_FIRE;
		SkillBonus_t maxBonus = pOusters->getSkillPointCount( maxDomain );

		for ( ElementalDomain domain = ELEMENTAL_DOMAIN_WATER ; domain <= ELEMENTAL_DOMAIN_COMBAT ; ++(int&)domain )
		{
			if ( domain == ELEMENTAL_DOMAIN_WIND ) continue;
			SkillBonus_t bonus = pOusters->getSkillPointCount( domain );
			if ( domain == ELEMENTAL_DOMAIN_COMBAT ) bonus += pOusters->getSkillPointCount( ELEMENTAL_DOMAIN_ELEMENTAL_COMBAT );
			if ( bonus > maxBonus )
			{
				maxBonus = bonus;
				maxDomain = domain;
			}
		}

		Item::ItemClass targetClass = Item::ITEM_CLASS_OUSTERS_WRISTLET;
		int add = 0;

		switch ( maxDomain )
		{
			case ELEMENTAL_DOMAIN_FIRE:
				{
				}
				break;
			case ELEMENTAL_DOMAIN_WATER:
				{
					add = 10;
				}
				break;
			case ELEMENTAL_DOMAIN_EARTH:
				{
					add = 20;
				}
				break;
			case ELEMENTAL_DOMAIN_WIND:
				{
				}
				break;
			case ELEMENTAL_DOMAIN_COMBAT:
				{
					targetClass = Item::ITEM_CLASS_OUSTERS_CHAKRAM;
				}
				break;
			default:
				break;
		}

		if ( targetClass == pItem->getItemClass() )
		{
			pItem->setItemType( pItem->getItemType() + add );
		}
		else
		{
			Item* pNewItem = g_pItemFactoryManager->createItem( targetClass, pItem->getItemType() + add, pItem->getOptionTypeList() );
			if ( pNewItem != NULL )
			{
				SAFE_DELETE( pItem );
				pItem = pNewItem;
			}
		}
	}

	if ( pItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_STONE && pPC->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
		ElementalDomain maxDomain = ELEMENTAL_DOMAIN_FIRE;
		SkillBonus_t maxBonus = pOusters->getSkillPointCount( maxDomain );

		for ( ElementalDomain domain = ELEMENTAL_DOMAIN_WATER ; domain <= ELEMENTAL_DOMAIN_EARTH ; ++(int&)domain )
		{
			SkillBonus_t bonus = pOusters->getSkillPointCount( domain );
			if ( bonus > maxBonus )
			{
				maxBonus = bonus;
				maxDomain = domain;
			}
		}

		int add = 0;

		switch ( maxDomain )
		{
			case ELEMENTAL_DOMAIN_FIRE:
				{
				}
				break;
			case ELEMENTAL_DOMAIN_WATER:
				{
					add = 5;
				}
				break;
			case ELEMENTAL_DOMAIN_EARTH:
				{
					add = 10;
				}
				break;
			default:
				break;
		}

		pItem->setItemType( pItem->getItemType() + add );
	}

	setItemGender( pItem, (pPC->getSex()==MALE)?GENDER_MALE:GENDER_FEMALE );

	return pItem;
}

#if defined(__THAILAND_SERVER__) || defined(__CHINA_SERVER__)
	
ItemType_t getItemTypeByItemLimit( Item::ItemClass itemClass, ItemType_t itemType )
{
	static ItemType_t limitItemType = (ItemType_t)SystemAvailabilitiesManager::getInstance()->getItemLevelLimit();
	ItemType_t rItemType = itemType;

	//  cout << "Original itemType : " << itemType << " , SystemItemLimit : " << limitItemType << endl;

	ItemInfo* pItemInfo = g_pItemInfoManager->getItemInfo( itemClass, rItemType );

	// ���ܻ���. ������ ������ ���� �������� ��� �н�
	if ( pItemInfo->getItemLevel() == 99 || pItemInfo->getItemLevel() == 255 )
	{
		return true;
	}

	int counter = 0;    // ������ ������ ���� ī����. ���ѷ����� �η���~

	//cout << "i. ItemLevel : " << pItemInfo->getItemLevel() << endl;

	while ( limitItemType <= pItemInfo->getItemLevel() && counter++ < 10 )
	{
		rItemType = getDowngradeItemType( itemClass, rItemType );
		pItemInfo = g_pItemInfoManager->getItemInfo( itemClass, rItemType );
	}

	//  cout << "o. ItemLevel : " << pItemInfo->getItemLevel() << endl;
	//  cout << "Return itemType : " << rItemType << endl;
	return rItemType;
}

#endif // __THAILAND_SERVER__
