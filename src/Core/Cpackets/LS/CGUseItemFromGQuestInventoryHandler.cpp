
//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseItemFromInventoryHandler.cpp
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGUseItemFromGQuestInventory.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "PlayerCreature.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Inventory.h"
	#include "GQuestInventory.h"
	#include "GQuestManager.h"
	#include "Item.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "ItemFactoryManager.h"
	#include "ItemMineInfo.h"
	#include "ItemUtil.h"
	#include "PacketUtil.h"
	#include "CreatureUtil.h"
	#include "Gpackets/GCCannotUse.h"
	#include "Gpackets/GCUseOK.h"
	#include "Gpackets/GCCreateItem.h"

	bool sendCannotUse( CGUseItemFromGQuestInventory* pPacket, Player* pPlayer )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getIndex());
		pPlayer->sendPacket(&_GCCannotUse);

		return true;
	}

#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromGQuestInventoryHandler::execute(CGUseItemFromGQuestInventory* pPacket, Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__
	
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC != NULL);

	Inventory* pInventory = pPC->getInventory();

	GQuestInventory& rInventory = pPC->getGQuestManager()->getGQuestInventory();
	list<ItemType_t>& rList = rInventory.getItems();

	list<ItemType_t>::iterator itr = rList.begin();

	for ( BYTE i=0; i<pPacket->getIndex(); ++i )
	{
		++itr;
		if ( itr == rList.end() )
		{
			sendCannotUse( pPacket, pPlayer );
			return;
		}
	}

	ItemType_t iType = *itr;

	if ( iType < 13 || iType > 20 )
	{
		sendCannotUse( pPacket, pPlayer );
		return;
	}

	if ( pPC->getLevel() < (iType-12)*5 )
	{
		sendCannotUse( pPacket, pPlayer );
		return;
	}

	static int baseID[3] = { 413, 421, 429 };

	int ID = baseID[(int)pPC->getRace()] + iType - 13;
	cout << "ID : " << ID << endl;

	Item* pItem = g_pItemMineInfoManager->getRandomItem(ID, ID);
	pItem = fitToPC( pItem, pPC );

	if ( pItem == NULL )
	{
		sendCannotUse( pPacket, pPlayer );
		return;
	}

	pItem->setCreateType( Item::CREATE_TYPE_TIME_EXTENSION );

	_TPOINT pt;
	if ( !pInventory->getEmptySlot( pItem, pt ) )
	{
		sendCannotUse( pPacket, pPlayer );
		SAFE_DELETE( pItem );
		return;
	}

	pPC->getZone()->registerObject( pItem );
	GCUseOK gcUseOK;
	pGamePlayer->sendPacket(&gcUseOK);

	rInventory.removeOne( pPC->getName(), iType );
	rList.erase(itr);
	pGamePlayer->sendPacket( rInventory.getInventoryPacket() );

	Assert( pInventory->addItem( pt.x, pt.y, pItem ) );

	pItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );
	GCCreateItem gcCreateItem;
	makeGCCreateItem( &gcCreateItem, pItem, pt.x, pt.y );
	pGamePlayer->sendPacket( &gcCreateItem );

	pPC->addTimeLimitItem( pItem, 604800 );
	pPC->updateEventItemTime( 604800 );
	pPC->sendTimeLimitItemInfo();

	giveLotto( pPC, 4, 3 );
	filelog( "ChoboEvent.log", "%s open %d box", pPC->getName().c_str(), iType );

	// ItemTraceLog 를 남긴다
	if ( pItem != NULL && pItem->isTraceItem() )
	{
		remainTraceLog( pItem, "GQuestBox", pPC->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
	}

#endif

    __END_DEBUG_EX __END_CATCH
}

