//////////////////////////////////////////////////////////////////////////////
// Filename    : CGTakeOutGoodHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGTakeOutGood.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Assert.h"
	#include "PlayerCreature.h"
	#include "GoodsInventory.h"
	#include "Inventory.h"
	#include "PacketUtil.h"
	#include "ItemUtil.h"
	#include "Gpackets/GCTakeOutFail.h"
	#include "Gpackets/GCTakeOutOK.h"
	#include "Gpackets/GCCreateItem.h"

	#include "SystemAvailabilitiesManager.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGTakeOutGoodHandler::execute (CGTakeOutGood* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert( pGamePlayer != NULL );

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pGamePlayer->getCreature());
	Assert( pPC != NULL );

	SYSTEM_ASSERT( SYSTEM_MARKET );

	GoodsInventory* pGoodsInventory = pPC->getGoodsInventory();
	Assert( pGoodsInventory != NULL );

	TPOINT tp;

	Item* pItem = pGoodsInventory->getItem( pPacket->getObjectID() );
	if ( pItem != NULL )
	{
		Inventory* pInventory = pPC->getInventory();
		if ( pInventory->addItem( pItem, tp ) )
		{
			pItem->create( pPC->getName(), STORAGE_INVENTORY, 0, tp.x, tp.y );
			pGoodsInventory->popItem( pPacket->getObjectID() );
			pItem->whenPCTake( pPC );

			GCCreateItem gcCreateItem;
			makeGCCreateItem( &gcCreateItem, pItem, tp.x ,tp.y );
			pPlayer->sendPacket( &gcCreateItem );

			if ( pItem->isTimeLimitItem() )
			{
				unsigned long timeLimit = pItem->getHour();
				timeLimit *= 3600;

				pPC->addTimeLimitItem( pItem, timeLimit );
				pPC->sendTimeLimitItemInfo();
			}

			remainTraceLog( pItem, "GoodsShop", pPC->getName(), ITEM_LOG_CREATE, DETAIL_MALLBUY );

			GCTakeOutOK gcTakeOutOK;
			gcTakeOutOK.setObjectID( pPacket->getObjectID() );
			pPlayer->sendPacket( &gcTakeOutOK );

			return;
		}
	}

	GCTakeOutFail gcTakeOutFail;
	gcTakeOutFail.setObjectID( pPacket->getObjectID() );

	pPlayer->sendPacket(&gcTakeOutFail);

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}
