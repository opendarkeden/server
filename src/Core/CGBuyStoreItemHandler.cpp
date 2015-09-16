//////////////////////////////////////////////////////////////////////////////
// Filename    : CGBuyStoreItemHandler.cpp
// Written By  : 김성민
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGBuyStoreItem.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Assert1.h"
	#include "Store.h"
	#include "Inventory.h"
	#include "ItemUtil.h"
	#include "Zone.h"
	#include "PlayerCreature.h"
	#include "PacketUtil.h"
	#include "DB.h"
	#include "VariableManager.h"
	#include "item/SubInventory.h"
	#include "GCMyStoreInfo.h"
	#include "GCRemoveStoreItem.h"
	#include "GCShopSellOK.h"
	#include "GCModifyInformation.h"
	#include "GCCreateItem.h"
	#include "GCSystemMessage.h"
	#include "GCNoticeEvent.h"
	#include <cstdio>
#endif

//////////////////////////////////////////////////////////////////////////////
// 플레이어가 원하는 물건을 파는 NPC와 그 아이템이 있는지
// 확인하고, 일반 아이템과 모터 사이클 처리부분으로 분기한다.
//////////////////////////////////////////////////////////////////////////////
void CGBuyStoreItemHandler::execute (CGBuyStoreItem* pPacket , Player* pPlayer)
	 throw(ProtocolException , Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__
	
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert(pPC != NULL);

	GCSystemMessage errorMsg;
	GCNoticeEvent errorNotice;

	if (pPacket->getIndex() > MAX_ITEM_NUM )
	{
		filelog("Store.log", "[%s:%s] (%u) 잘못된 인덱스입니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pPacket->getIndex());
		return;
	}

	PlayerCreature* pStorePC = dynamic_cast<PlayerCreature*>(pPC->getZone()->getCreature(pPacket->getOwnerObjectID()));
	if (pStorePC == NULL )
	{
		filelog("Store.log", "[%s:%s] (%u) 그런 유저가 없습니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pPacket->getOwnerObjectID());
//		errorMsg.setMessage("해당 판매자를 찾을 수 없습니다.");
		errorNotice.setCode(NOTICE_EVENT_CANNOT_FIND_STORE);
		pGamePlayer->sendPacket(&errorNotice);
		return;
	}

	if (pStorePC->getRace() != pPC->getRace() )
	{
		filelog("Store.log", "[%s:%s] (%s) 다른 종족의 상점을 열려고 시도했습니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pStorePC->getName().c_str());
		return;
	}

	Store* pStore = pStorePC->getStore();
	if (pStore == NULL || !pStore->isOpen() )
	{
		filelog("Store.log", "[%s:%s] (%s) 상점이 열려있지 않습니다..",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pStorePC->getName().c_str());
//		errorMsg.setMessage("상점이 이미 닫혔습니다.");
		errorNotice.setCode(NOTICE_EVENT_STORE_CLOSED);
		pGamePlayer->sendPacket(&errorNotice);
		return;
	}

	StoreItem& storeItem = pStore->getStoreItem(pPacket->getIndex());
	if (!storeItem.isExists() )
	{
		filelog("Store.log", "[%s:%s] (%s:%u) 해당 위치에 아이템이 없습니다..",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pStorePC->getName().c_str(), pPacket->getIndex());
//		errorMsg.setMessage("아이템이 이미 판매되었거나 판매자에 의해 철회되었습니다.");
		errorNotice.setCode(NOTICE_EVENT_ITEM_NOT_FOUND);
		pGamePlayer->sendPacket(&errorNotice);
		return;
	}

	Item* pItem = storeItem.getItem();
	Gold_t price = storeItem.getPrice();

	Assert(pItem != NULL);

	if (pItem->getItemClass() == Item::ITEM_CLASS_SUB_INVENTORY )
	{
		SubInventory* pSubInventoryItem = dynamic_cast<SubInventory*>(pItem);
		if (pSubInventoryItem->getInventory()->getItemNum() > 0 ||
			pPC->getInventory()->findItem(Item::ITEM_CLASS_SUB_INVENTORY ) != NULL )
		{
			errorNotice.setCode(NOTICE_EVENT_CANNOT_SELL);
			pGamePlayer->sendPacket(&errorNotice);
			return;
		}
	}

	if (pPC->getGold() < price )
	{
		filelog("Store.log", "[%s:%s] (%s:%u) (%u<%u) 돈이 모자랍니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pStorePC->getName().c_str(), pPacket->getIndex(), pPC->getGold(), price);
//		errorMsg.setMessage("돈이 모자랍니다.");
		errorNotice.setCode(NOTICE_EVENT_NOT_ENOUGH_MONEY);
		pGamePlayer->sendPacket(&errorNotice);
		return;
	}

	if (pStorePC->getGold() > MAX_MONEY - price )
	{
		filelog("Store.log", "[%s:%s] (%s:%u) (%u,%u) 돈이 넘칩니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pStorePC->getName().c_str(), pPacket->getIndex(), pStorePC->getGold(), price);
//		errorMsg.setMessage("판매자가 너무 많은 돈을 가지고 있어서 구입할 수 없습니다.");
		errorNotice.setCode(NOTICE_EVENT_TOO_MUCH_MONEY);
		pGamePlayer->sendPacket(&errorNotice);
		errorMsg.setMessage("너무 많은 돈을 가지고 있어서 물품을 판매할 수 없습니다.");
		pStorePC->getPlayer()->sendPacket(&errorMsg);
		pGamePlayer->sendPacket(&errorMsg);
		return;
	}

	if (pItem->isTimeLimitItem() || !canSell(pItem ) )
	{
		filelog("Store.log", "[%s:%s] (%s:%u) (%s) 팔 수 없는 아이템입니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pStorePC->getName().c_str(), pPacket->getIndex(), pItem->toString().c_str());
		return;
	}

	Inventory* pStoreInventory = pStorePC->getInventory();
	CoordInven_t storeX, storeY;

	Item* pStoreItem = pStoreInventory->findItemOID(pItem->getObjectID(), storeX, storeY);
	if (pStoreItem != pItem )
	{
		filelog("Store.log", "[%s:%s] (%s:%u) (%p!=%p) 판매자가 아이템을 안갖고 있거나 이상한 아이템입니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pStorePC->getName().c_str(), pPacket->getIndex(), pStoreItem, pItem);
		errorMsg.setMessage("인벤토리에 판매할 아이템이 없습니다.");
		pStorePC->getPlayer()->sendPacket(&errorMsg);
		return;
	}

	Inventory* pInventory = pPC->getInventory();
	_TPOINT emptyPos;

	if (!pInventory->getEmptySlot(pItem, emptyPos ) )
	{
		filelog("Store.log", "[%s:%s] (%s:%u) 살 사람 인벤토리에 자리가 없습니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pStorePC->getName().c_str(), pPacket->getIndex());
//		errorMsg.setMessage("인벤토리에 빈 곳이 없어서 구입할 수 없습니다.");
		errorNotice.setCode(NOTICE_EVENT_NO_INVENTORY_SPACE);
		pGamePlayer->sendPacket(&errorNotice);
		return;
	}

	Assert(pStore->removeStoreItem(pPacket->getIndex() ) == 0);

	pStoreInventory->deleteItem(storeX, storeY);
	pStorePC->increaseGoldEx(price);

	filelog("StoreBought.log", "[%s:%u/%u] 아이템이 제거되었습니다.", pStorePC->getName().c_str(), pItem->getItemClass(), pItem->getItemID());
	
	GCShopSellOK gcSellOK;
	gcSellOK.setObjectID(pPC->getObjectID());
	gcSellOK.setShopVersion(-1);
	gcSellOK.setItemObjectID(pItem->getObjectID());
	gcSellOK.setPrice(price);
	pStorePC->getPlayer()->sendPacket(&gcSellOK);

	Assert(pInventory->addItem(pItem, emptyPos ));
	pPC->decreaseGoldEx(price);

	char pField[80];
	sprintf(pField, "OwnerID='%s', Storage=%d, StorageID=0, X=%d, Y=%d", pPC->getName().c_str(), STORAGE_INVENTORY, emptyPos.x, emptyPos.y);
	pItem->tinysave(pField);

	filelog("StoreBought.log", "[%s:%u/%u] 아이템이 주어졌습니다.", pPC->getName().c_str(), pItem->getItemClass(), pItem->getItemID());

	if (pItem->isTraceItem() )
	{
		remainTraceLog(pItem, pStorePC->getName(), pPC->getName(), ITEM_LOG_TRADE, DETAIL_TRADE);
	}

	if (price > g_pVariableManager->getMoneyTraceLogLimit() )
	{
		remainMoneyTraceLog(pPC->getName(), pStorePC->getName(), ITEM_LOG_TRADE, DETAIL_TRADE, price);
	}

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("INSERT INTO `TradeLog` (`Timeline`, `Name1`, `IP1`, `Name2`, `IP2`, `Content`) VALUES ('%s', '%s', '%s', '%s', '%s', 'Store:[%s(%s)]\n%s\n----\nBuy:[%s(%s)]\nGOLD:%u\n')",
				VSDateTime::currentDateTime().toString().c_str(),
				pStorePC->getName().c_str(),
				pStorePC->getPlayer()->getSocket()->getHost().c_str(),
				pPC->getName().c_str(),
				pPC->getPlayer()->getSocket()->getHost().c_str(),
				pStorePC->getName().c_str(), pStorePC->getPlayer()->getID().c_str(),
				pItem->toString().c_str(),
				pPC->getName().c_str(), pPC->getPlayer()->getID().c_str(),
				price);

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt);

	GCCreateItem gcCreateItem;
	makeGCCreateItem(&gcCreateItem, pItem, emptyPos.x, emptyPos.y);
	pGamePlayer->sendPacket(&gcCreateItem);

	GCModifyInformation gcMI;
	gcMI.addLongData(MODIFY_GOLD, pPC->getGold());
	pGamePlayer->sendPacket(&gcMI);

	GCRemoveStoreItem gcRemoveStoreItem;
	gcRemoveStoreItem.setOwnerObjectID(pStorePC->getObjectID());
	gcRemoveStoreItem.setIndex(pPacket->getIndex());
	pStorePC->getZone()->broadcastPacket(pStorePC->getX(), pStorePC->getY(), &gcRemoveStoreItem, pStorePC);

	GCMyStoreInfo gcInfo;
	gcInfo.setStoreInfo(&(pStore->getStoreInfo()));
	pStorePC->getPlayer()->sendPacket(&gcInfo);

#endif

	__END_DEBUG_EX __END_CATCH
}


