//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddInventoryToMouseHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGAddInventoryToMouse.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "PlayerCreature.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "ItemFactoryManager.h"
	#include "ItemUtil.h"
	#include "TradeManager.h"
	#include "ObjectRegistry.h"
	#include "Store.h"

	#include "Gpackets/GCTradeVerify.h"
	#include "Gpackets/GCCannotAdd.h"
	#include "Gpackets/GCCreateItem.h"
	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddInventoryToMouseHandler::execute(CGAddInventoryToMouse* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC != NULL);

	Zone* pZone = pPC->getZone();
	Assert(pZone != NULL);

	if ( pPC->getStore()->isOpen() )
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);
		return;
	}

	CoordInven_t InvenX = pPacket->getX();
	CoordInven_t InvenY = pPacket->getY();
	ObjectID_t   ItemOID = pPacket->getObjectID();

	Inventory* pInventory = pPC->getInventory();
	Assert(pInventory != NULL);

	// 인벤토리 좌표를 넘어가면 곤란하다...
	if (InvenX >= pInventory->getWidth() || InvenY >= pInventory->getHeight())
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);
		return;
	}

	Item* pItem          = pInventory->getItem(InvenX, InvenY);
	Item* pExtraSlotItem = pPC->getExtraInventorySlotItem();

	if ( pPC->getStore()->hasItem( pItem ) )
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);
		return;
	}

	// 더하고자 하는 아이템이 없거나, 이미 마우스에 뭔가가 붙어있다면
	// 들 수 없다.
	if (pItem == NULL || pExtraSlotItem != NULL)
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);
		return;
	}

	// 일반적인 아이템 마우스 더하기 루틴
	if (ItemOID != 0)
	{
		// OID가 일치하지 않으면 곤란하다...
		if (pItem->getObjectID() != ItemOID)
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		pInventory->deleteItem(pItem->getObjectID());
		pPC->addItemToExtraInventorySlot(pItem);
		//pItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
		// item저장 최적화. by sigi. 2002.5.13
		char pField[80];
		sprintf(pField, "Storage=%d, StorageID=0", STORAGE_EXTRASLOT);
		pItem->tinysave(pField);

		TradeManager* pTradeManager = pZone->getTradeManager();
		TradeInfo* pInfo = pTradeManager->getTradeInfo(pCreature->getName());
		if (pInfo != NULL && pInfo->getStatus() == TRADE_FINISH)
		{
			GCTradeVerify gcTradeVerify;
			gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_INVENTORY_TO_MOUSE_OK);
			pPlayer->sendPacket(&gcTradeVerify);
		}
	}
	// 겹치는 아이템 분리하기 루틴
	else
	{
		// 겹치는 아이템이 아니거나, 현재 숫자가 2 미만이라면 분리할 수 없다.
		if (!isStackable(pItem) || pItem->getNum() < 2
			|| (pItem->getItemClass() == Item::ITEM_CLASS_MOON_CARD && pItem->getItemType() == 2 && pItem->getNum() == 99) 
			|| pPC->getStore()->hasItem(pItem)
		)
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// 기존의 아이템을 바탕으로 같은 아이템을 생성한다. 
		Item::ItemClass IClass = pItem->getItemClass();
		ItemType_t      IType  = pItem->getItemType();
		const list<OptionType_t>& OType  = pItem->getOptionTypeList();

		Item* pNewItem = g_pItemFactoryManager->createItem(IClass, IType, OType);
		Assert(pNewItem != NULL);

		// 마우스에다 더할 아이템은 기존의 OID를 가져가고,
		// 인벤토리에 남을 아이템은 새로운 OID를 받아야 한다.
		Zone* pZone = pPC->getZone();
		Assert(pZone != NULL);

		ObjectRegistry& OR = pZone->getObjectRegistry();
		OR.registerObject(pNewItem);

		// 인벤토리에 남아있는 아이템의 숫자는 원래 숫자에서 1을 뺀 숫자가 된다.
		// 기존의 아이템은 마우스로 옮겨졌으므로, 숫자가 1이 된다.
		// 인벤토리에서 마우스로 옮겨진 아이템을 삭제하고, 
		// 새로 생성된 아이템을 더한다.
		pInventory->deleteItem(pItem->getObjectID());
		pPC->addItemToExtraInventorySlot(pItem);

		int NewNum = pItem->getNum() - 1;
		pNewItem->setNum(NewNum); 
		pItem->setNum(1);

		pInventory->addItem(InvenX, InvenY, pNewItem);

		// 달라진 위치 정보를 세이브한다...
		//pItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
		// item저장 최적화. by sigi. 2002.5.13
		char pField[80];
		sprintf(pField, "Num=%d, Storage=%d, StorageID=0", 1, STORAGE_EXTRASLOT);
		pItem->tinysave(pField);

		pNewItem->create(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
		//pNewItem->setNum(NewNum); // 위에서 했는데 또 하네. -_-;
		//pNewItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
		// item저장 최적화. by sigi. 2002.5.13
		sprintf(pField, "Num=%d, Storage=%d, StorageID=0", NewNum, STORAGE_INVENTORY);
		pNewItem->tinysave(pField);


		// 클라이언트에게는 GCCreateItem 패킷을 이용해 
		// 인벤토리에 새로이(?) 생성된 아이템에 대한 정보를 보내준다.
		GCCreateItem gcCreateItem;
		gcCreateItem.setObjectID(pNewItem->getObjectID());
		gcCreateItem.setItemClass((BYTE)pNewItem->getItemClass());
		gcCreateItem.setItemType(pNewItem->getItemType());
		gcCreateItem.setOptionType(pNewItem->getOptionTypeList());
		gcCreateItem.setDurability(pNewItem->getDurability());
		gcCreateItem.setSilver(pNewItem->getSilver());
		gcCreateItem.setEnchantLevel(pNewItem->getEnchantLevel());
		gcCreateItem.setItemNum(pNewItem->getNum());
		gcCreateItem.setInvenX(InvenX);
		gcCreateItem.setInvenY(InvenY);
		pPlayer->sendPacket(&gcCreateItem);
	}
	
#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH

}

