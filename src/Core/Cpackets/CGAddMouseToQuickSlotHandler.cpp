//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddMouseToQuickSlotHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGAddMouseToQuickSlot.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Ousters.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "ItemUtil.h"
	#include "item/Belt.h"
	#include "item/OustersArmsband.h"

	#include "Gpackets/GCCannotAdd.h"
	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddMouseToQuickSlotHandler::execute (CGAddMouseToQuickSlot* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer*    pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*      pCreature   = pGamePlayer->getCreature();
	bool           Success     = false;

	if (pCreature->isSlayer())
	{
		Slayer*        pSlayer    = dynamic_cast<Slayer*>(pCreature);
		InventorySlot* pExtraSlot = pSlayer->getExtraInventorySlot();
		Item*          pItem      = pExtraSlot->getItem();

		if (pItem == NULL)
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		ObjectID_t      ItemObjectID = pItem->getObjectID();
		SlotID_t        SlotID       = pPacket->getSlotID();
		Item::ItemClass IClass       = pItem->getItemClass();

		// 아이템의 ObjectID가 일치하는지 체크한다.
		if (ItemObjectID != pPacket->getObjectID()) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// 벨트를 입고 있지 않다면 벨트에다 아이템을 더할 수가 없다.
		if (!pSlayer->isWear(Slayer::WEAR_BELT))
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// 포션도 아니고, 탄창도 아니라면 더할 수가 없지.
		if (IClass != Item::ITEM_CLASS_POTION && IClass != Item::ITEM_CLASS_MAGAZINE && IClass != Item::ITEM_CLASS_EVENT_ETC && IClass != Item::ITEM_CLASS_KEY)
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}
		if ( IClass == Item::ITEM_CLASS_EVENT_ETC && pItem->getItemType() < 14 )
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		Item*      pBelt          = pSlayer->getWearItem(Slayer::WEAR_BELT);
		Inventory* pBeltInventory = ((Belt*)pBelt)->getInventory();

		if (pBeltInventory->canAdding(SlotID, 0,  pItem)) 
		{
			// 현재 벨트에 있는 Item을 받아온다.
			Item* pPrevItem = pBeltInventory->getItem(SlotID, 0);

			// 지정한 자리에 아이템이 있다면...
			if (pPrevItem != NULL)
			{
				// 아이템이 완전히 같은 아이템이라면...
				if (isStackable(pItem) && isSameItem(pItem, pPrevItem))
				{
					int MaxStack = ItemMaxStack[pItem->getItemClass()];

					if (pItem->getNum() + pPrevItem->getNum() > MaxStack) 
					{
						ItemNum_t CurrentNum = pPrevItem->getNum();
						ItemNum_t AddNum     = pItem->getNum();
						ItemNum_t NewNum	 = AddNum + CurrentNum - MaxStack;

						pPrevItem->setNum(MaxStack);
						pItem->setNum(NewNum);
						pBeltInventory->increaseNum(MaxStack - CurrentNum);
						pBeltInventory->increaseWeight(pItem->getWeight()* (MaxStack - CurrentNum));
						//pPrevItem->save(pSlayer->getName(), STORAGE_BELT, pBelt->getItemID(), SlotID, 0);
						// item저장 최적화. by sigi. 2002.5.13
						char pField[80];
						sprintf(pField, "Num=%d, Storage=%d, StorageID=%lu, X=%d", MaxStack, STORAGE_BELT, pBelt->getItemID(), SlotID);
						pPrevItem->tinysave(pField);

						//pItem->save(pSlayer->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
						// item저장 최적화. by sigi. 2002.5.13
						sprintf(pField, "Num=%d, Storage=%d", NewNum, STORAGE_EXTRASLOT);
						pItem->tinysave(pField);


						Success = true;
					} 
					else // 숫자가 9개를 넘지 않을 때.
					{
						pSlayer->deleteItemFromExtraInventorySlot();
						pPrevItem->setNum(pPrevItem->getNum() + pItem->getNum());
						pBeltInventory->increaseNum(pItem->getNum());
						pBeltInventory->increaseWeight(pItem->getWeight()* pItem->getNum());
						//pPrevItem->save(pSlayer->getName(), STORAGE_BELT , pBelt->getItemID(), SlotID, 0);
						// item저장 최적화. by sigi. 2002.5.13
						char pField[80];
						sprintf(pField, "Num=%d, Storage=%d, StorageID=%lu, X=%d", pPrevItem->getNum(), STORAGE_BELT, pBelt->getItemID(), SlotID);
						pPrevItem->tinysave(pField);

						pItem->destroy();
						SAFE_DELETE(pItem);
						Success = true;
					}
				} 
				else // 클래스랑 타입이 같지 않을때
				{
					// 마우스에 달려있는 아이템과 벨트에 있는 아이템을 제거한다.
					pSlayer->deleteItemFromExtraInventorySlot();
					pBeltInventory->deleteItem(pPrevItem->getObjectID());

					// 둘의 위치를 바꿔 준다.
					pSlayer->addItemToExtraInventorySlot(pPrevItem);
					pBeltInventory->addItem(SlotID , 0 , pItem);

					// DB에다가 저장을 한다.
					//pPrevItem->save(pSlayer->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
					// item저장 최적화. by sigi. 2002.5.13
					char pField[80];
					sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
					pPrevItem->tinysave(pField);

					//pItem->save(pSlayer->getName(), STORAGE_BELT , pBelt->getItemID(), SlotID, 0);
					// item저장 최적화. by sigi. 2002.5.13
					sprintf(pField, "Storage=%d, StorageID=%lu, X=%d", STORAGE_BELT, pBelt->getItemID(), SlotID);
					pItem->tinysave(pField);


					Success = true;
				}
			} 
			else // 슬랏에 아무런 기존의 아이템이 없을때.
			{
				// Inventory에 특정 아이템을 넣는다.
				pBeltInventory->addItem(SlotID, 0 , pItem);

				// 넣기에 성공하면 마우스에 달려있는 아이템을 없앤다.
				pSlayer->deleteItemFromExtraInventorySlot();
				//pItem->save(pSlayer->getName(), STORAGE_BELT, pBelt->getItemID(), SlotID, 0);
				// item저장 최적화. by sigi. 2002.5.13
				char pField[80];
				sprintf(pField, "Storage=%d, StorageID=%lu, X=%d", STORAGE_BELT, pBelt->getItemID(), SlotID);
				pItem->tinysave(pField);

				Success = true;
			}
		} // end of if (pBeltInventory->canAdding(SlotID, 0,  pItem)) 
	} // if (pCreature->isSlayer())
	else if (pCreature->isOusters())
	{
		Ousters*        pOusters  = dynamic_cast<Ousters*>(pCreature);
		InventorySlot* pExtraSlot = pOusters->getExtraInventorySlot();
		Item*          pItem      = pExtraSlot->getItem();

		if (pItem == NULL)
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		ObjectID_t      ItemObjectID = pItem->getObjectID();
		SlotID_t        SlotID       = pPacket->getSlotID();
		Item::ItemClass IClass       = pItem->getItemClass();

		// 아이템의 ObjectID가 일치하는지 체크한다.
		if (ItemObjectID != pPacket->getObjectID()) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		Ousters::WearPart part = ( SlotID > 2 ? Ousters::WEAR_ARMSBAND2 : Ousters::WEAR_ARMSBAND1 );
		if ( SlotID > 2 ) SlotID -= 3;

		// 해당 암스밴드가 없다
		if (!pOusters->isWear(part)) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// 푸파도 아니고, 콤포스메이도 아니라면 더할 수가 없지.
		if (IClass != Item::ITEM_CLASS_PUPA && IClass != Item::ITEM_CLASS_COMPOS_MEI && IClass != Item::ITEM_CLASS_EVENT_ETC )
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		if ( IClass == Item::ITEM_CLASS_EVENT_ETC && pItem->getItemType() < 14 )
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		Item*      pArmsband          = pOusters->getWearItem(part);
		Inventory* pArmsbandInventory = ((OustersArmsband*)pArmsband)->getInventory();

		if (pArmsbandInventory->canAdding(SlotID, 0,  pItem)) 
		{
			// 현재 벨트에 있는 Item을 받아온다.
			Item* pPrevItem = pArmsbandInventory->getItem(SlotID, 0);

			// 지정한 자리에 아이템이 있다면...
			if (pPrevItem != NULL)
			{
				// 아이템이 완전히 같은 아이템이라면...
				if (isSameItem(pItem, pPrevItem))
				{
					int MaxStack = ItemMaxStack[pItem->getItemClass()];

					if (pItem->getNum() + pPrevItem->getNum() > MaxStack) 
					{
						ItemNum_t CurrentNum = pPrevItem->getNum();
						ItemNum_t AddNum     = pItem->getNum();
						ItemNum_t NewNum	 = AddNum + CurrentNum - MaxStack;

						pPrevItem->setNum(MaxStack);
						pItem->setNum(NewNum);
						pArmsbandInventory->increaseNum(MaxStack - CurrentNum);
						pArmsbandInventory->increaseWeight(pItem->getWeight()* (MaxStack - CurrentNum));
						//pPrevItem->save(pOusters->getName(), STORAGE_BELT, pArmsband->getItemID(), SlotID, 0);
						// item저장 최적화. by sigi. 2002.5.13
						char pField[80];
						sprintf(pField, "Num=%d, Storage=%d, StorageID=%lu, X=%d", MaxStack, STORAGE_BELT, pArmsband->getItemID(), SlotID);
						pPrevItem->tinysave(pField);

						//pItem->save(pOusters->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
						// item저장 최적화. by sigi. 2002.5.13
						sprintf(pField, "Num=%d, Storage=%d", NewNum, STORAGE_EXTRASLOT);
						pItem->tinysave(pField);


						Success = true;
					} 
					else // 숫자가 9개를 넘지 않을 때.
					{
						pOusters->deleteItemFromExtraInventorySlot();
						pPrevItem->setNum(pPrevItem->getNum() + pItem->getNum());
						pArmsbandInventory->increaseNum(pItem->getNum());
						pArmsbandInventory->increaseWeight(pItem->getWeight()* pItem->getNum());
						//pPrevItem->save(pOusters->getName(), STORAGE_BELT , pArmsband->getItemID(), SlotID, 0);
						// item저장 최적화. by sigi. 2002.5.13
						char pField[80];
						sprintf(pField, "Num=%d, Storage=%d, StorageID=%lu, X=%d", pPrevItem->getNum(), STORAGE_BELT, pArmsband->getItemID(), SlotID);
						pPrevItem->tinysave(pField);

						pItem->destroy();
						SAFE_DELETE(pItem);
						Success = true;
					}
				} 
				else // 클래스랑 타입이 같지 않을때
				{
					// 마우스에 달려있는 아이템과 벨트에 있는 아이템을 제거한다.
					pOusters->deleteItemFromExtraInventorySlot();
					pArmsbandInventory->deleteItem(pPrevItem->getObjectID());

					// 둘의 위치를 바꿔 준다.
					pOusters->addItemToExtraInventorySlot(pPrevItem);
					pArmsbandInventory->addItem(SlotID , 0 , pItem);

					// DB에다가 저장을 한다.
					//pPrevItem->save(pOusters->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
					// item저장 최적화. by sigi. 2002.5.13
					char pField[80];
					sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
					pPrevItem->tinysave(pField);

					//pItem->save(pOusters->getName(), STORAGE_BELT , pArmsband->getItemID(), SlotID, 0);
					// item저장 최적화. by sigi. 2002.5.13
					sprintf(pField, "Storage=%d, StorageID=%lu, X=%d", STORAGE_BELT, pArmsband->getItemID(), SlotID);
					pItem->tinysave(pField);


					Success = true;
				}
			} 
			else // 슬랏에 아무런 기존의 아이템이 없을때.
			{
				// Inventory에 특정 아이템을 넣는다.
				pArmsbandInventory->addItem(SlotID, 0 , pItem);

				// 넣기에 성공하면 마우스에 달려있는 아이템을 없앤다.
				pOusters->deleteItemFromExtraInventorySlot();
				//pItem->save(pOusters->getName(), STORAGE_BELT, pArmsband->getItemID(), SlotID, 0);
				// item저장 최적화. by sigi. 2002.5.13
				char pField[80];
				sprintf(pField, "Storage=%d, StorageID=%lu, X=%d", STORAGE_BELT, pArmsband->getItemID(), SlotID);
				pItem->tinysave(pField);

				Success = true;
			}
		} // end of if (pArmsbandInventory->canAdding(SlotID, 0,  pItem)) 
	} // if (pCreature->isOusters())

	// QuickSlot에 넣는 것을 실패 하였을때 실패 패킷을 날린다.
	if (!Success) 
	{
		GCCannotAdd _GCCannotAdd;
		_GCCannotAdd.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotAdd);
	}

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH

}

