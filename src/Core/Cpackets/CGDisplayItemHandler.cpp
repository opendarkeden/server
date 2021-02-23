//////////////////////////////////////////////////////////////////////////////
// Filename    : CGDisplayItemHandler.cp	p
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGDisplayItem.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "PlayerCreature.h"
	#include "Store.h"
	#include "Inventory.h"
	#include "ItemUtil.h"
	#include "Zone.h"
	#include "TradeManager.h"
	#include "Gpackets/GCMyStoreInfo.h"
	#include "Gpackets/GCAddStoreItem.h"
	#include "Gpackets/GCSystemMessage.h"
	#include "Gpackets/GCNoticeEvent.h"
#endif	// __GAME_SERVER__

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGDisplayItemHandler::execute (CGDisplayItem* pPacket , Player* pPlayer)
	 throw (Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
		
#ifdef __GAME_SERVER__
	
//#ifndef __TEST_SERVER__
//	return;
//#endif

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	Inventory* pInventory = pPC->getInventory();
	Assert( pInventory != NULL );

	Store* pStore = pPC->getStore();
	Assert( pStore != NULL );

	GCSystemMessage errorMsg;
	GCNoticeEvent errorNotice;

	if ( pPacket->getIndex() > MAX_ITEM_NUM )
	{
		filelog("Store.log", "[%s:%s] (%u) 잘못된 인덱스입니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pPacket->getIndex());
		return;
	}

	if ( pPacket->getX() >= pInventory->getWidth() || pPacket->getY() >= pInventory->getHeight() )
	{
		filelog("Store.log", "[%s:%s] (%u,%u) 인벤토리 좌표를 잘못 보내줬습니다..",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pPacket->getX(), pPacket->getY() );
		return;
	}

	Item* pItem = pInventory->getItem( pPacket->getX(), pPacket->getY() );
	if ( pItem == NULL || pItem->getObjectID() != pPacket->getItemObjectID() )
	{
		filelog("Store.log", "[%s:%s] (%u, %u) : %u 아이템 좌표가 잘못되었거나 오브젝트 아이디가 잘못되었습니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pPacket->getX(), pPacket->getY(), pPacket->getItemObjectID() );
		return;
	}

	if ( pPC->getZone()->getTradeManager()->getTradeInfo( pPC->getName() ) != NULL )
	{
		filelog("Store.log", "[%s:%s] : 거래중에는 물건을 올려놓을 수 없습니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str());
		return;
	}

	if ( pStore->hasItem( pItem ) )
	{
		filelog("Store.log", "[%s:%s] (%u, %u) 이미 아이템이 상점에 있습니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pItem->getObjectID(), pPacket->getIndex() );
//		errorMsg.setMessage("이미 진열된 아이템입니다.");
		errorNotice.setCode(NOTICE_EVENT_ALREADY_DISPLAYED);
		pGamePlayer->sendPacket( &errorNotice );
		return;
	}

	if ( pItem->isTimeLimitItem() || !canSell( pItem ) || !canTrade( pItem ) )
	{
		filelog("Store.log", "[%s:%s] (%s) 팔 수 없는 아이템입니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), pItem->toString().c_str());
//		errorMsg.setMessage("판매할 수 없는 아이템입니다.");
		errorNotice.setCode(NOTICE_EVENT_CANNOT_SELL);
		pGamePlayer->sendPacket( &errorNotice );
		return;
	}

	BYTE result = pStore->setStoreItem( pPacket->getIndex(), pItem, pPacket->getPrice() );
	if (  result != 0 )
	{
		filelog("Store.log", "[%s:%s] (%u) 아이템을 놓을 수 없습니다.",
				pGamePlayer->getID().c_str(), pPC->getName().c_str(), result);
		return;
	}

	GCMyStoreInfo gcInfo;
	gcInfo.setStoreInfo( &(pStore->getStoreInfo()) );
	pGamePlayer->sendPacket( &gcInfo );

	if ( pStore->isOpen() )
	{
		GCAddStoreItem gcAdd;
		gcAdd.setOwnerObjectID( pPC->getObjectID() );
		gcAdd.setIndex( pPacket->getIndex() );
		pStore->getStoreItem( pPacket->getIndex() ).makeStoreItemInfo( gcAdd.getItem() );
		pPC->getZone()->broadcastPacket( pPC->getX(), pPC->getY(), &gcAdd, pPC );
	}

#endif	// __GAME_SERVER__
		
	__END_DEBUG_EX __END_CATCH
}

