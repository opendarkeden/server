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
	#include "Gpackets/GCCreateItem.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGRequestNewbieItemHandler::execute (CGRequestNewbieItem* pPacket , Player* pPlayer)
	 throw (ProtocolException , Error)
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
	// 초보자가 슬레이어가 아닌 경우는 없다.
	////////////////////////////////////////////////////////////
	if (!pPC->isSlayer()) return;

	Slayer*    pSlayer     = dynamic_cast<Slayer*>(pPC);
	FlagSet*   pFlagSet    = pSlayer->getFlagSet();
	Inventory* pInventory  = pSlayer->getInventory();

	////////////////////////////////////////////////////////////
	// 진짜 초보인지를 검사한다.
	// 0번을 초보 아이템 받았다 플래그로 정했다.
	// 이것은 어디까지나 땜빵 코드다.
	////////////////////////////////////////////////////////////
	if (pFlagSet->isOn(0)) return;

	////////////////////////////////////////////////////////////
	// 각 아이템 클래스에 따라 아이템을 생성한다.
	////////////////////////////////////////////////////////////
	Item* pItem[10] = { NULL, };
	int   i         = 0;

	for (i=0; i<10; i++) pItem[i] = NULL;

	list<OptionType_t> optionNULL;

	if (IClass == Item::ITEM_CLASS_SWORD)
	{
		// 무기
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_SWORD, 0, optionNULL);
		// 포션
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
	}
	else if (IClass == Item::ITEM_CLASS_BLADE)
	{
		// 무기
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_BLADE, 0, optionNULL);
		// 포션
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
	}
	else if (IClass == Item::ITEM_CLASS_CROSS)
	{
		// 무기
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_CROSS, 0, optionNULL);
		// 포션
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
	}
	else if (IClass == Item::ITEM_CLASS_MACE)
	{
		// 무기
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_MACE, 0, optionNULL);
		// 포션
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
	}
	else if (IClass == Item::ITEM_CLASS_AR)
	{
		// 무기
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_AR, 0, optionNULL);
		// 포션
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		// 탄창
		pItem[5] = CREATE_ITEM(Item::ITEM_CLASS_MAGAZINE, 1, optionNULL);
		dynamic_cast<Magazine*>(pItem[5])->setNum(9);
	}
	else if (IClass == Item::ITEM_CLASS_SR)
	{
		// 무기
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_SR, 0, optionNULL);
		// 포션
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		// 탄창
		pItem[5] = CREATE_ITEM(Item::ITEM_CLASS_MAGAZINE, 4, optionNULL);
		dynamic_cast<Magazine*>(pItem[5])->setNum(9);
	}
	else if (IClass == Item::ITEM_CLASS_SG)
	{
		// 무기
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_SG, 0, optionNULL);
		// 포션
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		// 탄창
		pItem[5] = CREATE_ITEM(Item::ITEM_CLASS_MAGAZINE, 0, optionNULL);
		dynamic_cast<Magazine*>(pItem[5])->setNum(9);
	}
	else if (IClass == Item::ITEM_CLASS_SMG)
	{
		// 무기
		pItem[0] = CREATE_ITEM(Item::ITEM_CLASS_SMG, 0, optionNULL);
		// 포션
		pItem[1] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[2] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 0, optionNULL);
		pItem[3] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		pItem[4] = CREATE_ITEM(Item::ITEM_CLASS_POTION, 4, optionNULL);
		// 탄창
		pItem[5] = CREATE_ITEM(Item::ITEM_CLASS_MAGAZINE, 3, optionNULL);
		dynamic_cast<Magazine*>(pItem[5])->setNum(9);
	}
	else
	{
		return;
	}

	////////////////////////////////////////////////////////////
	// 생성한 아이템을 등록하고, DB에 저장하고,
	// 클라이언트에게 정보를 날려준다.
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
	// 아이템을 받았으니, 현재 FlagSet을 저장한다.
	// 0번을 초보 아이템 받았다 플래그로 정했다.
	// 이것은 어디까지나 땜빵 코드다.
	////////////////////////////////////////////////////////////
	pFlagSet->turnOn(FLAGSET_RECEIVE_NEWBIE_ITEM);

	if (IClass == Item::ITEM_CLASS_SWORD || IClass == Item::ITEM_CLASS_BLADE)
	{
		// 무사일 경우 1
		pFlagSet->turnOn( FLAGSET_RECEIVE_NEWBIE_ITEM_FIGHTER );
	}
	else if (IClass == Item::ITEM_CLASS_CROSS || IClass == Item::ITEM_CLASS_MACE)
	{
		// 성직자일 경우 2
		pFlagSet->turnOn( FLAGSET_RECEIVE_NEWBIE_ITEM_CLERIC );
	}
	else
	{
		// 군인일 경우 3
		pFlagSet->turnOn( FLAGSET_RECEIVE_NEWBIE_ITEM_GUNNER );
	}

	pFlagSet->save(pSlayer->getName());

#endif

	__END_DEBUG_EX __END_CATCH
}
