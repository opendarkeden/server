////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveSpecialEventItem.cpp
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#include "ActionGiveSpecialEventItem.h"
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

#include <stdio.h>

#include "item/Key.h"

#include "Gpackets/GCCreateItem.h"
#include "Gpackets/GCNPCResponse.h"
#include "Gpackets/GCSystemMessage.h"

////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void ActionGiveSpecialEventItem::read (PropertyBuffer & propertyBuffer)
    
{
    __BEGIN_TRY
    __END_CATCH
}

////////////////////////////////////////////////////////////////////////////////
// 액션을 실행한다.
////////////////////////////////////////////////////////////////////////////////
void ActionGiveSpecialEventItem::execute (Creature * pCreature1 , Creature * pCreature2) 
	
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

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection( (int)Thread::self() )->createStatement();
		pResult = pStmt->executeQuery("SELECT Count FROM SpecialEvent WHERE Name='%s'", pPlayer->getID().c_str());

		// 해당 로우가 없다는 말은 이 사람이 이벤트 아이템을 받을 자격이 없다는 것을 말한다.
		if (pResult->getRowCount() == 0)
		{
//			StringStream buf;
//			buf << pPlayer->getID() << " 님은 피의 전쟁 이벤트에 참가하지 않으셨습니다.";

			char buf[100];
			sprintf( buf, g_pStringPool->c_str( STRID_DO_NOT_JOIN_BLOOD_WAR_EVENT ),
							pPlayer->getID().c_str() );

			GCSystemMessage gcSystemMessage;
			gcSystemMessage.setMessage(buf);
			pPlayer->sendPacket(&gcSystemMessage);

			SAFE_DELETE(pStmt);
			return;
		}

		pResult->next();
		count = pResult->getInt(1);
		
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)

	// 카운트가 0이하라는 말은 이 사람이 이미 아이템을 받았다는 것을 의미한다.
	if (count <= 0)
	{
//		StringStream buf;
//		buf << pPlayer->getID() << " 님은 이미 피의 전쟁 이벤트 관련 아이템을 받으셨습니다.";

		char buf[100];
		sprintf( buf, g_pStringPool->c_str( STRID_ALREADY_TAKE_BLOOD_WAR_EVET_ITEM ),
						pPlayer->getID().c_str() );

		GCSystemMessage gcSystemMessage;
		gcSystemMessage.setMessage(buf);
		pPlayer->sendPacket(&gcSystemMessage);
		return;
	}

	Zone* pZone = pPC->getZone();
	ObjectRegistry& OR = pZone->getObjectRegistry();

	Inventory* pInventory = pPC->getInventory();
	TPOINT pt;
	GCCreateItem gcCreateItem;

	StringStream msg;
	msg << "PlayerID[" << pPlayer->getID() << "], " << "CreatureName[" << pPC->getName() << "]\n";

	if (pPC->isSlayer())
	{
		list<OptionType_t> option50;	option50.push_back( 50 );
		list<OptionType_t> optionNULL;

		Item* pItem1      = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_BRACELET, 3, option50);
		Item* pItem2      = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_BRACELET, 3, option50);
		Item* pMotorcycle = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_MOTORCYCLE, 0, optionNULL);
		Item* pKeyItem    = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_KEY, 2, optionNULL);

		Key* pKey = dynamic_cast<Key*>(pKeyItem);

		// OID를 등록받는다.
		OR.registerObject(pItem1);
		OR.registerObject(pItem2);
		OR.registerObject(pMotorcycle);
		OR.registerObject(pKey);

		pMotorcycle->create(pPC->getName(), STORAGE_ZONE, 11, 50, 50);
		pKey->setTarget(pMotorcycle->getItemID());

		list<Item*> ItemList;
		ItemList.push_back(pItem1);
		ItemList.push_back(pItem2);
		ItemList.push_back(pKey);

		list<Item*>::iterator itr = ItemList.begin();
		for (; itr != ItemList.end(); itr++)
		{
			Item* pItem = *itr;

			if (pInventory->addItem(pItem, pt))
			{
				pItem->create(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);
				pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);

				gcCreateItem.setObjectID(pItem->getObjectID());
				gcCreateItem.setItemClass(pItem->getItemClass());
				gcCreateItem.setItemType(pItem->getItemType());
				gcCreateItem.setOptionType(pItem->getOptionTypeList());
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
				}
			}
			else
			{
				// 자리가 없다면 존에다 떨어뜨린다.
				pt = pZone->addItem(pItem, pPC->getX(), pPC->getY());
				if (pt.x != -1)
				{
					pItem->create("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);
					pItem->save("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);

					// ItemTraceLog 를 남긴다
					if ( pItem != NULL && pItem->isTraceItem() )
					{
						char zoneName[15];
						sprintf( zoneName, "%4d%3d%3d", pZone->getZoneID(), pt.x, pt.y);
						remainTraceLog( pItem, pCreature1->getName(), zoneName, ITEM_LOG_CREATE, DETAIL_EVENTNPC);
					}
				}
				else
				{
					SAFE_DELETE(pItem);
				}

				msg << "Inventory Adding Failed : " << pItem->toString() << "\n";
			}
		}
	}
	else
	{
		list<OptionType_t> option50;	option50.push_back( 50 );
		list<OptionType_t> optionNULL;

		Item* pItem1 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_RING, 3, option50);
		Item* pItem2 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_RING, 3, option50);
		Item* pItem3 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_RING, 3, option50);
		Item* pItem4 = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_VAMPIRE_RING, 3, option50);

		// OID를 등록받는다.
		OR.registerObject(pItem1);
		OR.registerObject(pItem2);
		OR.registerObject(pItem3);
		OR.registerObject(pItem4);

		list<Item*> ItemList;
		ItemList.push_back(pItem1);
		ItemList.push_back(pItem2);
		ItemList.push_back(pItem3);
		ItemList.push_back(pItem4);

		list<Item*>::iterator itr = ItemList.begin();
		for (; itr != ItemList.end(); itr++)
		{
			Item* pItem = *itr;

			if (pInventory->addItem(pItem, pt))
			{
				pItem->create(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);
				pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y);

				gcCreateItem.setObjectID(pItem->getObjectID());
				gcCreateItem.setItemClass(pItem->getItemClass());
				gcCreateItem.setItemType(pItem->getItemType());
				gcCreateItem.setOptionType(pItem->getOptionTypeList());
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
				}
			}
			else
			{
				// 자리가 없다면 존에다 떨어뜨린다.
				pt = pZone->addItem(pItem, pPC->getX(), pPC->getY());
				if (pt.x != -1)
				{
					pItem->create("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);
					pItem->save("", STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y);

					// ItemTraceLog 를 남긴다
					if ( pItem != NULL && pItem->isTraceItem() )
					{
						char zoneName[15];
						sprintf( zoneName, "%4d%3d%3d", pZone->getZoneID(), pt.x, pt.y);
						remainTraceLog( pItem, pCreature1->getName(), zoneName, ITEM_LOG_CREATE, DETAIL_EVENTNPC);
					}

				}
				else
				{
					SAFE_DELETE(pItem);
				}

				msg << "Inventory Adding Failed : " << pItem->toString() << "\n";
			}
		}
	}

	msg << "Deleting SpecialEvent Count, ";
	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection( (int)Thread::self() )->createStatement();
		pStmt->executeQuery("UPDATE SpecialEvent SET Count = 0 WHERE Name='%s'", pPlayer->getID().c_str());
		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt)
	msg << "Finished\n";

	filelog("SpecialEvent.log", "%s", msg.toString().c_str());

	__END_CATCH
}


////////////////////////////////////////////////////////////////////////////////
// get debug string
////////////////////////////////////////////////////////////////////////////////
string ActionGiveSpecialEventItem::toString () const 
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "ActionGiveSpecialEventItem("
	    << ")";
	return msg.toString();

	__END_CATCH
}






