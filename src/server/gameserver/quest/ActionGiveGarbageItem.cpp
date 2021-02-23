////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveGarbageEventItem.cpp
// Written By  : excel96
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionGiveGarbageEventItem.h"
#include "PlayerCreature.h"
#include "GamePlayer.h"
#include "Item.h"
#include "ItemUtil.h"
#include "Inventory.h"
#include "Zone.h"
#include "ItemFactoryManager.h"
#include "DB.h"
#include "Thread.h"
#include "StringPool.h"
#include <list>

#include "item/Key.h"

#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCNPCResponse.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void ActionGiveGarbageEventItem::read (PropertyBuffer & propertyBuffer)
    throw (Error)
{
    __BEGIN_TRY
    __END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionGiveGarbageEventItem::execute (Creature * pCreature1 , Creature * pCreature2) 
	throw (Error)
{
	__BEGIN_TRY

	Assert(pCreature1 != NULL);
	Assert(pCreature2 != NULL);
	Assert(pCreature1->isNPC());
	Assert(pCreature2->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature2);
	Assert(pPC != NULL);

	Player* pPlayer = pPC->getPlayer();
	Assert(pPlayer != NULL);

	// 먼저 클라이언트를 위해 GCNPCResponse를 보내준다.
	GCNPCResponse okpkt;
	pPlayer->sendPacket(&okpkt);

	// 가비지 리스트에 아이템이 존재한다면...
	if (pPC->getGarbageSize() > 0)
	{
		TPOINT pt;

		Item* pItem = pPC->popItemFromGarbage();
		Assert(pItem != NULL);

		// 인벤토리에 자리가 있다면 인벤토리에다가 더하고 플레이어에게 알려준다.
		if (pInventory->addItem(pItem, pt))
		{
			pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);

			GCCreateItem gcCreateItem;
			gcCreateItem.setObjectID(pItem->getObjectID());
			gcCreateItem.setItemClass(pItem->getItemClass());
			gcCreateItem.setItemType(pItem->getItemType());
			gcCreateItem.setOptionType(pItem->getOptionType());
			gcCreateItem.setDurability(pItem->getDurability());
			gcCreateItem.setSilver(pItem->getSilver());
			gcCreateItem.setItemNum(pItem->getNum());
			gcCreateItem.setInvenX(pt.x);
			gcCreateItem.setInvenY(pt.y);

			pPlayer->sendPacket(&gcCreateItem);

			// ItemTraceLog 를 남긴다
			if ( pItem != NULL && pItem->isTraceItem() )
			{
				remainTraceLog( pItem, pCreature1->getName(), pCreature2->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
				remainTraceLogNew( pItem, pCreature2->getName(), ITL_GET, ITLD_EVENTNPC, pCreature1->getZone()->getZoneID(), pCreature1->getX(), pCreature1->getY() );
			}
		}
		// 인벤토리에 자리가 없다면, 다시 가비지 리스트에다가 더하고
		// 플레이어에게 그 사실을 알려준다.
		else
		{
			pPC->addItemToGarbage(pItem);

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage( g_pStringPool->getString( STRID_NOT_ENOUGH_INVENTORY_SPACE ) );
			pPlayer->sendPacket(&gcSystemMessage);
		}
	}
	else
	{
		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage( g_pStringPool->getString( STRID_ITEM_NOT_EXIST ) );
		pPlayer->sendPacket(&gcSystemMessage);
	}

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionGiveGarbageEventItem::toString () const 
	throw ()
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionGiveGarbageEventItem("
	    << ")";
	return msg.toString();

	__END_CATCH
}
