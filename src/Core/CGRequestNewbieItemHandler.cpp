//////////////////////////////////////////////////////////////////////////////
// Filename    : CGRequestNewbieItem.cpp
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGRequestNewbieItem.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Slayer.h"
	#include "FlagSet.h"
	#include "Item.h"
	#include "Zone.h"
	#include "ItemFactoryManager.h"

	#include "item/Magazine.h"
	#include "GCCreateItem.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGRequestNewbieItemHandler::execute (CGRequestNewbieItem* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pPC         = pGamePlayer->getCreature();
	Zone*       pZone       = pPC->getZone();
	BYTE        IClass   = pPacket->getItemClass();

	////////////////////////////////////////////////////////////
	// Only Slayers can request this starter kit.
	////////////////////////////////////////////////////////////
	if (!pPC->isSlayer()) return;

	Slayer*    pSlayer     = dynamic_cast<Slayer*>(pPC);
	FlagSet*   pFlagSet    = pSlayer->getFlagSet();
	Inventory* pInventory  = pSlayer->getInventory();

	////////////////////////////////////////////////////////////
	// Check whether the starter items were already granted.
	// Flag 0 was historically used to track receipt; keep that behavior.
	////////////////////////////////////////////////////////////
	if (pFlagSet->isOn(0)) return;

	////////////////////////////////////////////////////////////
	// Build the starter item set based on the requested class.
	////////////////////////////////////////////////////////////
	Item* pItem[10] = { NULL, };
	int   i         = 0;

	for (i=0; i<10; i++) pItem[i] = NULL;

	list<OptionType_t> optionNULL;

	if (IClass == Item::ITEM_CLASS_SWORD)
	{
		// Starter weapon
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_SWORD, 0, optionNULL);
		// Healing items
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
	}
	else if (IClass == Item::ITEM_CLASS_BLADE)
	{
		// Starter weapon
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_BLADE, 0, optionNULL);
		// Healing items
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
	}
	else if (IClass == Item::ITEM_CLASS_CROSS)
	{
		// Starter weapon
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_CROSS, 0, optionNULL);
		// Healing items
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
	}
	else if (IClass == Item::ITEM_CLASS_MACE)
	{
		// Starter weapon
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_MACE, 0, optionNULL);
		// Healing items
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
	}
	else if (IClass == Item::ITEM_CLASS_AR)
	{
		// Starter weapon
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_AR, 0, optionNULL);
		// Healing items
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		// Ammo magazine
		pItem[5] = CREATE_ITEM(Item::ITEM_CLASS_MAGAZINE, 1, optionNULL);
		dynamic_cast<Magazine*>(pItem[5])->setNum(9);
	}
	else if (IClass == Item::ITEM_CLASS_SR)
	{
		// Starter weapon
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_SR, 0, optionNULL);
		// Healing items
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		// Ammo magazine
		pItem[5] = CREATE_ITEM(Item::ITEM_CLASS_MAGAZINE, 4, optionNULL);
		dynamic_cast<Magazine*>(pItem[5])->setNum(9);
	}
	else if (IClass == Item::ITEM_CLASS_SG)
	{
		// Starter weapon
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_SG, 0, optionNULL);
		// Healing items
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		// Ammo magazine
		pItem[5] = CREATE_ITEM(Item::ITEM_CLASS_MAGAZINE, 0, optionNULL);
		dynamic_cast<Magazine*>(pItem[5])->setNum(9);
	}
	else if (IClass == Item::ITEM_CLASS_SMG)
	{
		// Starter weapon
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_SMG, 0, optionNULL);
		// Healing items
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		// Ammo magazine
		pItem[5] = CREATE_ITEM(Item::ITEM_CLASS_MAGAZINE, 3, optionNULL);
		dynamic_cast<Magazine*>(pItem[5])->setNum(9);
	}
	else
	{
		return;
	}

	////////////////////////////////////////////////////////////
	// Create the items, persist them, and inform the client.
	////////////////////////////////////////////////////////////
	ObjectRegistry& OR = pZone->getObjectRegistry();
	TPOINT           pt;
	GCCreateItem     gcCreateItem;

	for (i=0; i<10; i++)
	{
		if (pItem[i] != NULL)
		{
			OR.registerObject(pItem[i]);

			if (pInventory->addItem(pItem[i], pt))
			{
				pItem[i]->create(pSlayer->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);

				gcCreateItem.setObjectID(pItem[i]->getObjectID());
				gcCreateItem.setItemClass(pItem[i]->getItemClass());
				gcCreateItem.setItemType(pItem[i]->getItemType());
				gcCreateItem.setOptionType(pItem[i]->getOptionTypeList());
				gcCreateItem.setDurability(pItem[i]->getDurability());
				gcCreateItem.setSilver(pItem[i]->getSilver());
				gcCreateItem.setItemNum(pItem[i]->getNum());
				gcCreateItem.setInvenX(pt.x);
				gcCreateItem.setInvenY(pt.y);

				pPlayer->sendPacket(&gcCreateItem);
			}
			else
			{
				SAFE_DELETE(pItem[i]);
			}
		}
	}

	////////////////////////////////////////////////////////////
	// Mark that the starter kit was delivered using the FlagSet.
	// Flag 0 tracks overall receipt for backward compatibility.
	////////////////////////////////////////////////////////////
	pFlagSet->turnOn(FLAGSET_RECEIVE_NEWBIE_ITEM);

	if (IClass == Item::ITEM_CLASS_SWORD || IClass == Item::ITEM_CLASS_BLADE)
	{
		// Fighter starter flag (type 1)
		pFlagSet->turnOn(FLAGSET_RECEIVE_NEWBIE_ITEM_FIGHTER);
	}
	else if (IClass == Item::ITEM_CLASS_CROSS || IClass == Item::ITEM_CLASS_MACE)
	{
		// Cleric starter flag (type 2)
		pFlagSet->turnOn(FLAGSET_RECEIVE_NEWBIE_ITEM_CLERIC);
	}
	else
	{
		// Gunner starter flag (type 3)
		pFlagSet->turnOn(FLAGSET_RECEIVE_NEWBIE_ITEM_GUNNER);
	}

	pFlagSet->save(pSlayer->getName());

#endif

	__END_DEBUG_EX __END_CATCH
}
