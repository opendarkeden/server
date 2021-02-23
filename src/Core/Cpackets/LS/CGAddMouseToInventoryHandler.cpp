//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddMouseToInventoryHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGAddMouseToInventory.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "ItemUtil.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "ItemFactoryManager.h"
	#include "TradeManager.h"
	#include "PacketUtil.h"
	#include "VariableManager.h"

	#include "Gpackets/GCCannotAdd.h"
	#include "Gpackets/GCTradeVerify.h"
	#include "Gpackets/GCCreateItem.h"
	#include "Gpackets/GCNoticeEvent.h"
	#include "Gpackets/GCDeleteInventoryItem.h"
	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddMouseToInventoryHandler::execute(CGAddMouseToInventory* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	//cout << "AddMouseToInventory execute start" << endl;

	try 
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		Assert(pGamePlayer != NULL);

		Creature* pCreature = pGamePlayer->getCreature();
		Assert(pCreature != NULL);
		Assert(pCreature->isPC());

		PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
		Assert(pPC != NULL);

		Zone* pZone = pPC->getZone();
		Assert(pZone != NULL);

		Inventory* pInventory = pPC->getInventory();
		Assert(pInventory != NULL);

		Item* pItem   = pPC->getExtraInventorySlot()->getItem();
		bool  Success = false;

		if (pItem == NULL)
		{
			//cout << "pItem NULL" << endl;
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		//Item::ItemClass itemClass = pItem->getItemClass();
		//ItemType_t	itemType	 = pItem->getItemType();
		ObjectID_t  itemObjectID = pItem->getObjectID();
		CoordInven_t InvenX      = pPacket->getInvenX();
		CoordInven_t InvenY      = pPacket->getInvenY();

		if (InvenX >= 10 || InvenY >= 6)
		{
			//cout << "inventory over" << endl;
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// 아이템의 ObjectID가 일치하는지 체크한다.
		if (itemObjectID != pPacket->getObjectID())
		{
			//cout << "wrong objectID" << endl;
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// 인벤토리에 넣을 수 있는지 체크한다.
		if (!pInventory->canAdding(InvenX, InvenY, pItem))
		{
			//cout << "cannot add" << endl;
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		TPOINT pt;
		pt.x = 99;
		pt.y = 99;

		//cout << "chk relic1" << endl;
		
		// 넣을려는 Inventory Slot의 Item을 받아온다.
		Item* pPrevItem = pInventory->searchItem(InvenX, InvenY , pItem, pt);

		// 그 장소에 아이템이 있다면
		if (pPrevItem != NULL) 
		{
			//cout << "prevItem!=0" << endl;
			bool bisSame = true;
			// 아이템 클래스가 같을때 숫자를 올려 주고 마우스에 있는 것은 없앤다.
			if (canStack(pItem, pPrevItem))
			{
				// add by sonic 2006.10.30  렝岺唐珂쇌掘齡膠틔렴瞳寧폅
				if(pItem->isTimeLimitItem() | pPrevItem->isTimeLimitItem())
				{
					//cout << "cannot add" << endl;
					GCCannotAdd _GCCannotAdd;
					_GCCannotAdd.setObjectID(pPacket->getObjectID());
					pPlayer->sendPacket(&_GCCannotAdd);
					return;
				}
				int MaxStack = ItemMaxStack[pItem->getItemClass()];

				VolumeWidth_t  ItemWidth  = pItem->getVolumeWidth();
				VolumeHeight_t ItemHeight = pItem->getVolumeHeight();
				VolumeWidth_t  InvenWidth = pInventory->getWidth();
				VolumeWidth_t  InvenHeight= pInventory->getHeight();


				if ((InvenX + ItemWidth <= InvenWidth) && (InvenY + ItemHeight <= InvenHeight)) 
				{
					for (int x = InvenX; x < (InvenX + ItemWidth); x++) 
					{
						for (int y = InvenY; y < (InvenY + ItemHeight); y++) 
						{
							if (pInventory->hasItem(x, y)) 
							{
								if( pInventory->getItem(x,y) != pPrevItem ) {
									bisSame = false;
									break;
								}
							} else {
								bisSame = false;
								break;
							}
						}
					}
				}

				// 들어갈 아이템과 들어있는 아이템의 좌표가 꼭 일치 한다면?
				if( bisSame ) {
					// 숫자가 9개를 넘으면 9개 될때까지만 Add 하고 나머지는 마우스에 달아둔다.
					if (pItem->getNum() + pPrevItem->getNum() > MaxStack) 
					{
						ItemNum_t CurrentNum = pPrevItem->getNum();
						ItemNum_t AddNum = pItem->getNum();
						ItemNum_t NewNum = AddNum + CurrentNum - MaxStack;

						pPrevItem->setNum(MaxStack);
						pItem->setNum(NewNum);
						pInventory->increaseNum(MaxStack - CurrentNum);
						pInventory->increaseWeight(pItem->getWeight()* (MaxStack - CurrentNum));
						//pPrevItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
						// item저장 최적화. by sigi. 2002.5.13
						char pField[80];
						sprintf(pField, "Num=%d, Storage=%d, X=%d, Y=%d", MaxStack, STORAGE_INVENTORY, InvenX, InvenY);
						pPrevItem->tinysave(pField);

						//pItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
						// item저장 최적화. by sigi. 2002.5.13
						sprintf(pField, "Num=%d, Storage=%d", NewNum, STORAGE_EXTRASLOT);
						pItem->tinysave(pField);

						Success = true;
					} 
					else 
					{
						pPC->deleteItemFromExtraInventorySlot();
						pPrevItem->setNum(pPrevItem->getNum() + pItem->getNum());
						pInventory->increaseNum(pItem->getNum());
						pInventory->increaseWeight(pItem->getWeight()* pItem->getNum());
						//pPrevItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
						// item저장 최적화. by sigi. 2002.5.13
						char pField[80];
						sprintf(pField, "Num=%d, Storage=%d, X=%d, Y=%d", pPrevItem->getNum(), STORAGE_INVENTORY, InvenX, InvenY);
						pPrevItem->tinysave(pField);

						pItem->destroy();
						SAFE_DELETE(pItem);
						Success = true;
					}

					if ( g_pVariableManager->getVariable(NETMARBLE_CARD_EVENT) != 0 && pPrevItem->getItemClass() == Item::ITEM_CLASS_MOON_CARD && pPrevItem->getItemType() == 2 && pPrevItem->getNum() == 99 )
					{
						GCNoticeEvent gcNE;
						gcNE.setCode( NOTICE_EVENT_NETMARBLE_CARD_FULL );
						pGamePlayer->sendPacket( &gcNE );
						cout << "gcNE sent" << endl;
					}

					if ( pPrevItem->getItemClass() == Item::ITEM_CLASS_LUCKY_BAG
							&& pPrevItem->getItemType() == 3
							&& pPrevItem->getNum() == 50 )
					{
						GCDeleteInventoryItem gcDI;
						gcDI.setObjectID( pPrevItem->getObjectID() );
						pGamePlayer->sendPacket( &gcDI );

						pInventory->deleteItem( pPrevItem->getObjectID() );
						pPrevItem->destroy();
						SAFE_DELETE( pPrevItem );
						
						Item* pNewItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_ITEM, 28, list<OptionType_t>() );
						pZone->registerObject( pNewItem );

						if ( !pInventory->addItem(pt.x, pt.y, pNewItem) )
						{
							cout << "-_-;" << endl;
							return;
						}

						pNewItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );

						if ( pNewItem != NULL )
						{
							GCCreateItem gcCI;
							makeGCCreateItem( &gcCI, pNewItem, pt.x, pt.y );
							pGamePlayer->sendPacket( &gcCI );
						}
					}

				} else {

					pInventory->deleteItem(pPrevItem->getObjectID());

					pPC->deleteItemFromExtraInventorySlot();

					pPC->addItemToExtraInventorySlot(pPrevItem);

					pInventory->addItem(InvenX , InvenY , pItem);

					//pPrevItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
					// item저장 최적화. by sigi. 2002.5.13
					char pField[80];
					sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
					pPrevItem->tinysave(pField);

					//pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
					// item저장 최적화. by sigi. 2002.5.13
					sprintf(pField, "Storage=%d, X=%d, Y=%d", STORAGE_INVENTORY, InvenX, InvenY);
					pItem->tinysave(pField);


					Success = true;
				}

			} 
			else // 아이템 클래스가 다르거나, 쌓이는 아이템이 아니라면.
			{
				pInventory->deleteItem(pPrevItem->getObjectID());

				pPC->deleteItemFromExtraInventorySlot();

				pPC->addItemToExtraInventorySlot(pPrevItem);

				pInventory->addItem(InvenX , InvenY , pItem);

				//pPrevItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
				// item저장 최적화. by sigi. 2002.5.13
				char pField[80];
				sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
				pPrevItem->tinysave(pField);

				//pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
				// item저장 최적화. by sigi. 2002.5.13
				sprintf(pField, "Storage=%d, X=%d, Y=%d", STORAGE_INVENTORY, InvenX, InvenY);
				pItem->tinysave(pField);


				Success = true;
			}
		} 
		else // 그 장소에 아이템이 없다면.
		{
			//cout << "prevItem is NULL" << endl;

			// Inventory에 특정 아이템을 넣는다.
			pInventory->addItem(InvenX , InvenY , pItem);

			// 넣기에 성공하면 마우스에 달려있는 아이템을 없앤다.
			pPC->deleteItemFromExtraInventorySlot();

			//pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
			// item저장 최적화. by sigi. 2002.5.13
			char pField[80];
			sprintf(pField, "Storage=%d, X=%d, Y=%d", STORAGE_INVENTORY, InvenX, InvenY);
			pItem->tinysave(pField);


			Success = true;
		}


		if (Success) 
		{
			//cout << "success" << endl;

			TradeManager* pTradeManager = pZone->getTradeManager();
			TradeInfo* pInfo = pTradeManager->getTradeInfo(pCreature->getName());
			if (pInfo != NULL && pInfo->getStatus() == TRADE_FINISH)
			{
				GCTradeVerify gcTradeVerify;
				gcTradeVerify.setCode(GC_TRADE_VERIFY_CODE_MOUSE_TO_INVENTORY_OK);
				pPlayer->sendPacket(&gcTradeVerify);
			}

			// 트리 조각일 경우
			if ( pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_EVENT_TREE)
			{
				ItemType_t itemtype = pItem->getItemType();

				// 크리스마스 트리 조각이면
				if ( itemtype <= 11 )
				{
					// 크리스마스 트리 조각이 맞춰지는지 본다.
					TPOINT pt = checkEventPuzzle( pPC, InvenX, InvenY, 0 );
					if ( pt.x != -1 && pt.y != -1 )
					{
						// 맞춰진 트리 조각을 지운다.
						deleteInventoryItem( pInventory, pt.x, pt.y, pt.x + 2, pt.y + 3 );

						// 트리를 생성한다.
						list<OptionType_t> optionType;
						Item* pTreeItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_TREE, 12, optionType );
						pZone->getObjectRegistry().registerObject( pTreeItem );
						pInventory->addItem( pt.x, pt.y, pTreeItem );
						pTreeItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );

						// 클라이언트에 트리가 만들어졌다는 걸 알린다.
						GCCreateItem gcCreateItem;
						makeGCCreateItem( &gcCreateItem, pTreeItem, pt.x, pt.y );
						pGamePlayer->sendPacket(&gcCreateItem);
					}
				}
				// 크리스마스 트리 조각이면
				else if ( itemtype > 12 && itemtype <= 24 )
				{
					// 크리스마스 트리 조각이 맞춰지는지 본다.
					TPOINT pt = checkEventPuzzle( pPC, InvenX, InvenY, 13 );
					if ( pt.x != -1 && pt.y != -1 )
					{
						// 맞춰진 트리 조각을 지운다.
						deleteInventoryItem( pInventory, pt.x, pt.y, pt.x + 2, pt.y + 3 );

						// 트리를 생성한다.
						list<OptionType_t> optionType;
						Item* pTreeItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_TREE, 25, optionType );
						pTreeItem->setQuestItem();
						pZone->getObjectRegistry().registerObject( pTreeItem );
						pInventory->addItem( pt.x, pt.y, pTreeItem );
						pTreeItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );

						// 클라이언트에 트리가 만들어졌다는 걸 알린다.
						GCCreateItem gcCreateItem;
						makeGCCreateItem( &gcCreateItem, pTreeItem, pt.x, pt.y );
						pGamePlayer->sendPacket(&gcCreateItem);
					}
				}
				// 크리스마스 트리 조각이면
				else if ( itemtype > 28 && itemtype <= 40 )
				{
					// 크리스마스 트리 조각이 맞춰지는지 본다.
					TPOINT pt = checkEventPuzzle( pPC, InvenX, InvenY, 29 );
					if ( pt.x != -1 && pt.y != -1 )
					{
						// 맞춰진 트리 조각을 지운다.
						deleteInventoryItem( pInventory, pt.x, pt.y, pt.x + 2, pt.y + 3 );

						// 트리를 생성한다.
						list<OptionType_t> optionType;
						Item* pTreeItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_TREE, 41, optionType );
						pTreeItem->setQuestItem();
						pZone->getObjectRegistry().registerObject( pTreeItem );
						pInventory->addItem( pt.x, pt.y, pTreeItem );
						pTreeItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );

						// 클라이언트에 트리가 만들어졌다는 걸 알린다.
						GCCreateItem gcCreateItem;
						makeGCCreateItem( &gcCreateItem, pTreeItem, pt.x, pt.y );
						pGamePlayer->sendPacket(&gcCreateItem);
					}
				}
			}
		}
		else
		{
			//cout << "cannot add" << endl;
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
		}
	} 
	catch (Throwable & t) 
	{
		//cout << t.toString();
	}

	//cout << "AddMouseToInventory execute OK" << endl;

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH

}

