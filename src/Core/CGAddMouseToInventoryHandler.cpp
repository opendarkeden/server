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

	#include "GCCannotAdd.h"
	#include "GCTradeVerify.h"
	#include "GCCreateItem.h"
	#include "GCNoticeEvent.h"
	#include "GCDeleteInventoryItem.h"
	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddMouseToInventoryHandler::execute(CGAddMouseToInventory* pPacket , Player* pPlayer)
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

		// �������� ObjectID�� ��ġ�ϴ��� üũ�Ѵ�.
		if (itemObjectID != pPacket->getObjectID())
		{
			//cout << "wrong objectID" << endl;
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// �κ��丮�� ���� �� �ִ��� üũ�Ѵ�.
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
		
		// �������� Inventory Slot�� Item�� �޾ƿ´�.
		Item* pPrevItem = pInventory->searchItem(InvenX, InvenY , pItem, pt);

		// �� ��ҿ� �������� �ִٸ�
		if (pPrevItem != NULL) 
		{
			//cout << "prevItem!=0" << endl;
			bool bisSame = true;
			// ������ Ŭ������ ������ ���ڸ� �÷� �ְ� ���콺�� �ִ� ���� ���ش�.
			if (canStack(pItem, pPrevItem))
			{
				// add by sonic 2006.10.30  ��ֹ��ʱ��������Ʒ����һ��
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

				// �� �����۰� ����ִ� �������� ��ǥ�� �� ��ġ �Ѵٸ�?
				if( bisSame ) {
					// ���ڰ� 9���� ������ 9�� �ɶ������� Add �ϰ� �������� ���콺�� �޾Ƶд�.
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
						// item���� ����ȭ. by sigi. 2002.5.13
						char pField[80];
						sprintf(pField, "Num=%d, Storage=%d, X=%d, Y=%d", MaxStack, STORAGE_INVENTORY, InvenX, InvenY);
						pPrevItem->tinysave(pField);

						//pItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
						// item���� ����ȭ. by sigi. 2002.5.13
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
						// item���� ����ȭ. by sigi. 2002.5.13
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
					// item���� ����ȭ. by sigi. 2002.5.13
					char pField[80];
					sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
					pPrevItem->tinysave(pField);

					//pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
					// item���� ����ȭ. by sigi. 2002.5.13
					sprintf(pField, "Storage=%d, X=%d, Y=%d", STORAGE_INVENTORY, InvenX, InvenY);
					pItem->tinysave(pField);


					Success = true;
				}

			} 
			else // ������ Ŭ������ �ٸ��ų�, ���̴� �������� �ƴ϶��.
			{
				pInventory->deleteItem(pPrevItem->getObjectID());

				pPC->deleteItemFromExtraInventorySlot();

				pPC->addItemToExtraInventorySlot(pPrevItem);

				pInventory->addItem(InvenX , InvenY , pItem);

				//pPrevItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
				// item���� ����ȭ. by sigi. 2002.5.13
				char pField[80];
				sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
				pPrevItem->tinysave(pField);

				//pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
				// item���� ����ȭ. by sigi. 2002.5.13
				sprintf(pField, "Storage=%d, X=%d, Y=%d", STORAGE_INVENTORY, InvenX, InvenY);
				pItem->tinysave(pField);


				Success = true;
			}
		} 
		else // �� ��ҿ� �������� ���ٸ�.
		{
			//cout << "prevItem is NULL" << endl;

			// Inventory�� Ư�� �������� �ִ´�.
			pInventory->addItem(InvenX , InvenY , pItem);

			// �ֱ⿡ �����ϸ� ���콺�� �޷��ִ� �������� ���ش�.
			pPC->deleteItemFromExtraInventorySlot();

			//pItem->save(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
			// item���� ����ȭ. by sigi. 2002.5.13
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

			// Ʈ�� ������ ���
			if ( pItem != NULL && pItem->getItemClass() == Item::ITEM_CLASS_EVENT_TREE)
			{
				ItemType_t itemtype = pItem->getItemType();

				// ũ�������� Ʈ�� �����̸�
				if ( itemtype <= 11 )
				{
					// ũ�������� Ʈ�� ������ ���������� ����.
					TPOINT pt = checkEventPuzzle( pPC, InvenX, InvenY, 0 );
					if ( pt.x != -1 && pt.y != -1 )
					{
						// ������ Ʈ�� ������ �����.
						deleteInventoryItem( pInventory, pt.x, pt.y, pt.x + 2, pt.y + 3 );

						// Ʈ���� �����Ѵ�.
						list<OptionType_t> optionType;
						Item* pTreeItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_TREE, 12, optionType );
						pZone->getObjectRegistry().registerObject( pTreeItem );
						pInventory->addItem( pt.x, pt.y, pTreeItem );
						pTreeItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );

						// Ŭ���̾�Ʈ�� Ʈ���� ��������ٴ� �� �˸���.
						GCCreateItem gcCreateItem;
						makeGCCreateItem( &gcCreateItem, pTreeItem, pt.x, pt.y );
						pGamePlayer->sendPacket(&gcCreateItem);
					}
				}
				// ũ�������� Ʈ�� �����̸�
				else if ( itemtype > 12 && itemtype <= 24 )
				{
					// ũ�������� Ʈ�� ������ ���������� ����.
					TPOINT pt = checkEventPuzzle( pPC, InvenX, InvenY, 13 );
					if ( pt.x != -1 && pt.y != -1 )
					{
						// ������ Ʈ�� ������ �����.
						deleteInventoryItem( pInventory, pt.x, pt.y, pt.x + 2, pt.y + 3 );

						// Ʈ���� �����Ѵ�.
						list<OptionType_t> optionType;
						Item* pTreeItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_TREE, 25, optionType );
						pTreeItem->setQuestItem();
						pZone->getObjectRegistry().registerObject( pTreeItem );
						pInventory->addItem( pt.x, pt.y, pTreeItem );
						pTreeItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );

						// Ŭ���̾�Ʈ�� Ʈ���� ��������ٴ� �� �˸���.
						GCCreateItem gcCreateItem;
						makeGCCreateItem( &gcCreateItem, pTreeItem, pt.x, pt.y );
						pGamePlayer->sendPacket(&gcCreateItem);
					}
				}
				// ũ�������� Ʈ�� �����̸�
				else if ( itemtype > 28 && itemtype <= 40 )
				{
					// ũ�������� Ʈ�� ������ ���������� ����.
					TPOINT pt = checkEventPuzzle( pPC, InvenX, InvenY, 29 );
					if ( pt.x != -1 && pt.y != -1 )
					{
						// ������ Ʈ�� ������ �����.
						deleteInventoryItem( pInventory, pt.x, pt.y, pt.x + 2, pt.y + 3 );

						// Ʈ���� �����Ѵ�.
						list<OptionType_t> optionType;
						Item* pTreeItem = g_pItemFactoryManager->createItem( Item::ITEM_CLASS_EVENT_TREE, 41, optionType );
						pTreeItem->setQuestItem();
						pZone->getObjectRegistry().registerObject( pTreeItem );
						pInventory->addItem( pt.x, pt.y, pTreeItem );
						pTreeItem->create( pPC->getName(), STORAGE_INVENTORY, 0, pt.x, pt.y );

						// Ŭ���̾�Ʈ�� Ʈ���� ��������ٴ� �� �˸���.
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

