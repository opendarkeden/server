////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveChildrenItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionGiveChildrenItem.h"
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
#include "Gpackets/GCSystemMessage.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionGiveChildrenItem::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY
    __END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
// 5월 5일 이벤트로
// 연변루돌프, 연변산타 몬스터를 죽였을대 나오는 아이템을 모아오면
// 그에 해당하는 아이템을 주도록 한다.
// 몬스터 아이템은 별로 정해질 예정이고..
// 나오는 아이템은 아직은 미정이다.
////////////////////////////////////////////////////////////////////////////////
void ActionGiveChildrenItem::execute (Creature * pCreature1 , Creature * pCreature2) 
	
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

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;
	int        count   = -1;

	Zone* pZone = pPC->getZone();
	ObjectRegistry& OR = pZone->getObjectRegistry();

	Inventory* pInventory = pPC->getInventory();
	TPOINT pt;
	GCCreateItem gcCreateItem;

	StringStream msg;
	msg << "PlayerID[" << pPlayer->getID() << "], " << "CreatureName[" << pPC->getName() << "]\n";

	if (pPC->isSlayer())
	{
		// 아이템을 생성한다.
		Item* pItem      = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_BRACELET, 3, 50);

		// OID를 등록받는다.
		OR.registerObject(pItem);

		if(pInventory->addItem(pItem, pt))
		{
			// 아이템을 인벤토리에 만든다.
			pItem->create(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);

			//아이템을 받았다는 것을 알려준다.
			gcCreateItem.setObjectID(pItem->getObjectID());
			gcCreateItem.setItemClass(pItem->getItemClass());
			gcCreateItem.setItemType(pItem->getItemType());
			gcCreateItem.setOptionType(pItem->getOptionType());
			gcCreateItem.setDurability(pItme->getDurability());
			gcCreateItem.setSilver(pItem->getSilver());
			gcCreateItem.setItemNum(pItem->getNum());
			gcCreateItem.setInvenX(pt.x);
			gcCreateItem.setInvenY(pt.y);

			pPlayer->sendPacket(&gcCreateItem);

			msg << "Inventory Adding Success : " << pItem->toString() << "\n";

			// ItemTraceLog 를 남긴다
			if ( pItem != NULL && pItem->isTraceItem() )
			{
				remainTraceLog( pItem, pCreature1->getName(), pCreature2->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
				remainTraceLogNew( pItem,  pCreature2->getName(), ITL_GET, ITLD_EVENTNPC, pCreature1->getZone()->getZoneID(), pCreature1->getX(), pCreature1->getY() );
			}
		}
		else
		{
			// 인벤토리에 자리가 없다면 메시지를 보내고 그만둔다.
			StringStream buf;
			buf << pPlayer->getID() << g_pStringPool->getString( STRID_NOT_ENOUGH_INVENTORY_SPACE );

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage(buf.toString());
			pPlayer->sendPacket(&gcSystemMessage);

			return;
		}
	
	}
	else
	{
		Item* pItem      = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_BRACELET, 3, 50);

		// OID를 등록받는다.
		OR.registerObject(pItem);

		if (pInventory->addItem(pItem, pt))
		{
			pItem->create(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);
			pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);

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

			msg << "Inventory Adding Succeeded : " << pItem->toString() << "\n";

			// ItemTraceLog 를 남긴다
			if ( pItem != NULL && pItem->isTraceItem() )
			{
				remainTraceLog( pItem, pCreature1->getName(), pCreature2->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
				remainTraceLogNew( pItem,  pCreature2->getName(), ITL_GET, ITLD_EVENTNPC, pCreature1->getZone()->getZoneID(), pCreature1->getX(), pCreature1->getY() );
			}
		}
		else
		{
			// 인벤토리에 자리가 없다면 메시지를 보내고 그만둔다.
			StringStream buf;
			buf << pPlayer->getID() << g_pStringPool->getString( STRID_NOT_ENOUGH_INVENTORY_SPACE );

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage(buf.toString());
			pPlayer->sendPacket(&gcSystemMessage);

			return;
		}
	}

	msg << "Finished\n";

	filelog("SpecialEvent.log", "%s", msg.toString().c_str());

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionGiveChildrenItem::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionGiveChildrenItem("
	    << ")";
	return msg.toString();

	__END_CATCH
}
