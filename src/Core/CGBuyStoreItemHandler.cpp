//////////////////////////////////////////////////////////////////////////////
// Filename    : CGBuyStoreItemHandler.cpp
// Written By  : �輺��
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGBuyStoreItem.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Assert.h"
	#include "Store.h"
	#include "Inventory.h"
	#include "ItemUtil.h"
	#include "Zone.h"
	#include "PlayerCreature.h"
	#include "PacketUtil.h"
	#include "DB.h"
	#include "VariableManager.h"
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
// �÷��̾ ���ϴ� ������ �Ĵ� NPC�� �� �������� �ִ���
// Ȯ���ϰ�, �Ϲ� �����۰� ���� ����Ŭ ó���κ����� �б��Ѵ�.
//////////////////////////////////////////////////////////////////////////////
void CGBuyStoreItemHandler::execute (CGBuyStoreItem* pPacket , Player* pPlayer)
	 
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__
	
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	GCSystemMessage errorMsg;
	GCNoticeEvent errorNotice;

	if ( pPacket->getIndex() > MAX_ITEM_NUM )
	{
		filelog("Store.log", "[%s:%s] (%u) �߸��� �ε����Դϴ�.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pPacket->getIndex());
		return;
	}

	PlayerCreature* pStorePC = dynamic_cast<PlayerCreature*>(pPC->getZone()->getCreature(pPacket->getOwnerObjectID()));
	if ( pStorePC == NULL )
	{
		filelog("Store.log", "[%s:%s] (%u) �׷� ������ �����ϴ�.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pPacket->getOwnerObjectID());
//		errorMsg.setMessage("�ش� �Ǹ��ڸ� ã�� �� �����ϴ�.");
		errorNotice.setCode(NOTICE_EVENT_CANNOT_FIND_STORE);
		pGamePlayer->sendPacket( &errorNotice );
		return;
	}

	if ( pStorePC->getRace() != pPC->getRace() )
	{
		filelog("Store.log", "[%s:%s] (%s) �ٸ� ������ ������ ������ �õ��߽��ϴ�.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pStorePC->getName().c_str());
		return;
	}

	Store* pStore = pStorePC->getStore();
	if ( pStore == NULL || !pStore->isOpen() )
	{
		filelog("Store.log", "[%s:%s] (%s) ������ �������� �ʽ��ϴ�..",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pStorePC->getName().c_str());
//		errorMsg.setMessage("������ �̹� �������ϴ�.");
		errorNotice.setCode(NOTICE_EVENT_STORE_CLOSED);
		pGamePlayer->sendPacket( &errorNotice );
		return;
	}

	StoreItem& storeItem = pStore->getStoreItem( pPacket->getIndex() );
	if ( !storeItem.isExists() )
	{
		filelog("Store.log", "[%s:%s] (%s:%u) �ش� ��ġ�� �������� �����ϴ�..",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pStorePC->getName().c_str(), pPacket->getIndex());
//		errorMsg.setMessage("�������� �̹� �ǸŵǾ��ų� �Ǹ��ڿ� ���� öȸ�Ǿ����ϴ�.");
		errorNotice.setCode(NOTICE_EVENT_ITEM_NOT_FOUND);
		pGamePlayer->sendPacket( &errorNotice );
		return;
	}

	Item* pItem = storeItem.getItem();
	Gold_t price = storeItem.getPrice();

	Assert( pItem != NULL );

	if ( pPC->getGold() < price )
	{
		filelog("Store.log", "[%s:%s] (%s:%u) (%u<%u) ���� ���ڶ��ϴ�.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pStorePC->getName().c_str(), pPacket->getIndex(), pPC->getGold(), price);
//		errorMsg.setMessage("���� ���ڶ��ϴ�.");
		errorNotice.setCode(NOTICE_EVENT_NOT_ENOUGH_MONEY);
		pGamePlayer->sendPacket( &errorNotice );
		return;
	}

	if ( pStorePC->getGold() > MAX_MONEY - price )
	{
		filelog("Store.log", "[%s:%s] (%s:%u) (%u,%u) ���� ��Ĩ�ϴ�.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pStorePC->getName().c_str(), pPacket->getIndex(), pStorePC->getGold(), price);
//		errorMsg.setMessage("�Ǹ��ڰ� �ʹ� ���� ���� ������ �־ ������ �� �����ϴ�.");
		errorNotice.setCode(NOTICE_EVENT_TOO_MUCH_MONEY);
		pGamePlayer->sendPacket( &errorNotice );
		errorMsg.setMessage("���Ͻ��̫��,�޷����н���.");
		pStorePC->getPlayer()->sendPacket(&errorMsg);
		pGamePlayer->sendPacket( &errorMsg );
		return;
	}

	if ( pItem->isTimeLimitItem() || !canSell( pItem ) )
	{
		filelog("Store.log", "[%s:%s] (%s:%u) (%s) �� �� ���� �������Դϴ�.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pStorePC->getName().c_str(), pPacket->getIndex(), pItem->toString().c_str());
		return;
	}

	Inventory* pStoreInventory = pStorePC->getInventory();
	CoordInven_t storeX, storeY;

	Item* pStoreItem = pStoreInventory->findItemOID( pItem->getObjectID(), storeX, storeY );
	if ( pStoreItem != pItem )
	{
		filelog("Store.log", "[%s:%s] (%s:%u) (%p!=%p) �Ǹ��ڰ� �������� �Ȱ��� �ְų� �̻��� �������Դϴ�.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pStorePC->getName().c_str(), pPacket->getIndex(), pStoreItem, pItem );
		errorMsg.setMessage("��������û�пɳ��۵ĵ���.");
		pStorePC->getPlayer()->sendPacket(&errorMsg);
		return;
	}

	Inventory* pInventory = pPC->getInventory();
	_TPOINT emptyPos;

	if ( !pInventory->getEmptySlot( pItem, emptyPos ) )
	{
		filelog("Store.log", "[%s:%s] (%s:%u) �� ��� �κ��丮�� �ڸ��� �����ϴ�.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pStorePC->getName().c_str(), pPacket->getIndex());
//		errorMsg.setMessage("�κ��丮�� �� ���� ��� ������ �� �����ϴ�.");
		errorNotice.setCode(NOTICE_EVENT_NO_INVENTORY_SPACE);
		pGamePlayer->sendPacket( &errorNotice );
		return;
	}

	Assert( pStore->removeStoreItem( pPacket->getIndex() ) == 0 );

	pStoreInventory->deleteItem( storeX, storeY );
	pStorePC->increaseGoldEx( price );

	filelog("StoreBought.log", "[%s:%u/%u] �������� ���ŵǾ����ϴ�.", pStorePC->getName().c_str(), pItem->getItemClass(), pItem->getItemID());
	
	GCShopSellOK gcSellOK;
	gcSellOK.setObjectID( pPC->getObjectID() );
	gcSellOK.setShopVersion( -1 );
	gcSellOK.setItemObjectID( pItem->getObjectID() );
	gcSellOK.setPrice( price );
	pStorePC->getPlayer()->sendPacket( &gcSellOK );

	Assert(pInventory->addItem( pItem, emptyPos ));
	pPC->decreaseGoldEx( price );

	char pField[80];
	sprintf(pField, "OwnerID='%s', Storage=%d, X=%d, Y=%d", pPC->getName().c_str(), STORAGE_INVENTORY, emptyPos.x, emptyPos.y);
	pItem->tinysave(pField);

	filelog("StoreBought.log", "[%s:%u/%u] �������� �־������ϴ�.", pPC->getName().c_str(), pItem->getItemClass(), pItem->getItemID());

	if ( pItem->isTraceItem() )
	{
		remainTraceLog( pItem, pStorePC->getName(), pPC->getName(), ITEM_LOG_TRADE, DETAIL_TRADE );
	}

	if ( price > g_pVariableManager->getMoneyTraceLogLimit() )
	{
		remainMoneyTraceLog( pPC->getName(), pStorePC->getName(), ITEM_LOG_TRADE, DETAIL_TRADE, price );
	}

	Statement* pStmt = NULL;

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pStmt->executeQuery("INSERT INTO TradeLog (Timeline, Name1, IP1, Name2, IP2, Content) VALUES ('%s', '%s', '%s', '%s', '%s', 'Store:[%s(%s)]\n%s\n----\nBuy:[%s(%s)]\nGOLD:%u\n')",
				VSDateTime::currentDateTime().toString().c_str(),
				pStorePC->getName().c_str(),
				pStorePC->getPlayer()->getSocket()->getHost().c_str(),
				pPC->getName().c_str(),
				pPC->getPlayer()->getSocket()->getHost().c_str(),
				pStorePC->getName().c_str(), pStorePC->getPlayer()->getID().c_str(),
				pItem->toString().c_str(),
				pPC->getName().c_str(), pPC->getPlayer()->getID().c_str(),
				price);

		SAFE_DELETE( pStmt );
	}
	END_DB(pStmt);

	GCCreateItem gcCreateItem;
	makeGCCreateItem( &gcCreateItem, pItem, emptyPos.x, emptyPos.y );
	pGamePlayer->sendPacket( &gcCreateItem );

	GCModifyInformation gcMI;
	gcMI.addLongData( MODIFY_GOLD, pPC->getGold() );
	pGamePlayer->sendPacket( &gcMI );

	GCRemoveStoreItem gcRemoveStoreItem;
	gcRemoveStoreItem.setOwnerObjectID( pStorePC->getObjectID() );
	gcRemoveStoreItem.setIndex( pPacket->getIndex() );
	pStorePC->getZone()->broadcastPacket( pStorePC->getX(), pStorePC->getY(), &gcRemoveStoreItem, pStorePC );

	GCMyStoreInfo gcInfo;
	gcInfo.setStoreInfo( &(pStore->getStoreInfo()) );
	pStorePC->getPlayer()->sendPacket( &gcInfo );

#endif

	__END_DEBUG_EX __END_CATCH
}


