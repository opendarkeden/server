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

	#include "GCTradeVerify.h"
	#include "GCCannotAdd.h"
	#include "GCCreateItem.h"
	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddInventoryToMouseHandler::execute(CGAddInventoryToMouse* pPacket , Player* pPlayer)
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

	// �κ��丮 ��ǥ�� �Ѿ�� ����ϴ�...
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

	// ���ϰ��� �ϴ� �������� ���ų�, �̹� ���콺�� ������ �پ��ִٸ�
	// �� �� ����.
	if (pItem == NULL || pExtraSlotItem != NULL)
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);
		return;
	}

	// �Ϲ����� ������ ���콺 ���ϱ� ��ƾ
	if (ItemOID != 0)
	{
		// OID�� ��ġ���� ������ ����ϴ�...
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
		// item���� ����ȭ. by sigi. 2002.5.13
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
	// ��ġ�� ������ �и��ϱ� ��ƾ
	else
	{
		// ��ġ�� �������� �ƴϰų�, ���� ���ڰ� 2 �̸��̶�� �и��� �� ����.
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

		// ������ �������� �������� ���� �������� �����Ѵ�. 
		Item::ItemClass IClass = pItem->getItemClass();
		ItemType_t      IType  = pItem->getItemType();
		const list<OptionType_t>& OType  = pItem->getOptionTypeList();

		Item* pNewItem = g_pItemFactoryManager->createItem(IClass, IType, OType);
		Assert(pNewItem != NULL);

		// ���콺���� ���� �������� ������ OID�� ��������,
		// �κ��丮�� ���� �������� ���ο� OID�� �޾ƾ� �Ѵ�.
		Zone* pZone = pPC->getZone();
		Assert(pZone != NULL);

		ObjectRegistry& OR = pZone->getObjectRegistry();
		OR.registerObject(pNewItem);

		// �κ��丮�� �����ִ� �������� ���ڴ� ���� ���ڿ��� 1�� �� ���ڰ� �ȴ�.
		// ������ �������� ���콺�� �Ű������Ƿ�, ���ڰ� 1�� �ȴ�.
		// �κ��丮���� ���콺�� �Ű��� �������� �����ϰ�, 
		// ���� ������ �������� ���Ѵ�.
		pInventory->deleteItem(pItem->getObjectID());
		pPC->addItemToExtraInventorySlot(pItem);

		int NewNum = pItem->getNum() - 1;
		pNewItem->setNum(NewNum); 
		pItem->setNum(1);

		pInventory->addItem(InvenX, InvenY, pNewItem);

		// �޶��� ��ġ ������ ���̺��Ѵ�...
		//pItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
		// item���� ����ȭ. by sigi. 2002.5.13
		char pField[80];
		sprintf(pField, "Num=%d, Storage=%d, StorageID=0", 1, STORAGE_EXTRASLOT);
		pItem->tinysave(pField);

		pNewItem->create(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
		//pNewItem->setNum(NewNum); // ������ �ߴµ� �� �ϳ�. -_-;
		//pNewItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
		// item���� ����ȭ. by sigi. 2002.5.13
		sprintf(pField, "Num=%d, Storage=%d, StorageID=0", NewNum, STORAGE_INVENTORY);
		pNewItem->tinysave(pField);


		// Ŭ���̾�Ʈ���Դ� GCCreateItem ��Ŷ�� �̿��� 
		// �κ��丮�� ������(?) ������ �����ۿ� ���� ������ �����ش�.
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

