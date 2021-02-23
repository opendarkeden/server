//////////////////////////////////////////////////////////////////////////////
// Filename    : CGMouseToStashHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGMouseToStash.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "PlayerCreature.h"
	#include "Stash.h"
	#include "Item.h"
	#include "ItemUtil.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "LogClient.h"
	#include "RelicUtil.h"
	#include "CreatureUtil.h"

	#include "item/Potion.h"
	#include "item/Magazine.h"
	#include "item/PetItem.h"

	#include "Gpackets/GCCannotAdd.h"
	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGMouseToStashHandler::execute (CGMouseToStash* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX
	__BEGIN_DEBUG

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		GamePlayer*         pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
		Creature*           pCreature    = pGamePlayer->getCreature();
		PlayerCreature*     pPC          = dynamic_cast<PlayerCreature*>(pCreature);
		Stash*              pStash       = pPC->getStash();
		Item*               pMouseItem   = pPC->getExtraInventorySlotItem();
		bool                Success      = false;

		// 마우스에 아이템이 달려있나?
		// 유니크 아이템은 보관함에 못 넣는다.
		// canPutInStash로 extract 2003. 3. 3
		if (pMouseItem == NULL
			|| !canPutInStash( pMouseItem )
//			|| pMouseItem->isUnique())
		)
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		ObjectID_t MouseItemOID = pMouseItem->getObjectID();
		BYTE       rack         = pPacket->getRack();
		BYTE       index        = pPacket->getIndex();

		// 정상적인 좌표값인가? 오브젝트 아이디는 일치하나?
		// Relic은 보관함에 저장될 수 없다.
		if (rack >= STASH_RACK_MAX 
			|| index >= STASH_INDEX_MAX 
			|| rack >= pPC->getStashNum() 
			|| MouseItemOID != pPacket->getObjectID()
			)
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
			return;
		}

		// 넣을려는 Stash Slot의 Item을 받아온다.
		Item* pStashItem = pStash->get(rack, index);

		// 그 장소에 아이템이 있다면
		if (pStashItem != NULL) 
		{
			// 아이템 클래스가 같을때 숫자를 올려 주고 마우스에 있는 것은 없앤다.
			if (isSameItem(pMouseItem, pStashItem) && isStackable(pMouseItem))
			{
				int MaxStack = ItemMaxStack[pMouseItem->getItemClass()];

				if (pMouseItem->getNum() + pStashItem->getNum() > MaxStack) 
				{
					ItemNum_t CurrentNum = pStashItem->getNum();
					ItemNum_t AddNum     = pMouseItem->getNum();

					pStashItem->setNum(MaxStack);
					pMouseItem->setNum(AddNum + CurrentNum - MaxStack);

					// 바뀐 정보를 DB에 저장한다.
					//pStashItem->save(pPC->getName(), STORAGE_STASH, 0, rack, index);
					// item저장 최적화. by sigi. 2002.5.13
					char pField[80];
					sprintf(pField, "Num=%d, Storage=%d, X=%d, Y=%d", MaxStack, STORAGE_STASH, rack, index);
					pStashItem->tinysave(pField);

					//pMouseItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
					// item저장 최적화. by sigi. 2002.5.13
					sprintf(pField, "Num=%d, Storage=%d", pMouseItem->getNum(), STORAGE_EXTRASLOT);
					pMouseItem->tinysave(pField);


					log(LOG_STASH_ADD_ITEM, pPC->getName(), "", pMouseItem->toString());

					Success = true;
				} 
				else 
				{
					pPC->deleteItemFromExtraInventorySlot();
//					pMouseItem->whenPCLost(pPC);

					pStashItem->setNum(pStashItem->getNum() + pMouseItem->getNum());
					//pStashItem->save(pPC->getName(), STORAGE_STASH, 0, rack, index);
					// item저장 최적화. by sigi. 2002.5.13
					char pField[80];
					sprintf(pField, "Num=%d, Storage=%d, X=%d, Y=%d", pStashItem->getNum(), STORAGE_STASH, rack, index);
					pStashItem->tinysave(pField);


					log(LOG_STASH_ADD_ITEM, pPC->getName(), "", pMouseItem->toString());

					// 두개의 아이템이 하나로 되었으니까, 
					// 더하라고 온 아이템은 삭제해 준다.
					pMouseItem->destroy();
					SAFE_DELETE(pMouseItem);

					Success = true;
				}
			} 
			else // 아이템 클래스가 다르거나, 쌓이는 아이템이 아니라면.
			{
				// 보관함에 있던 것을 마우스에 달아준다.
				pPC->deleteItemFromExtraInventorySlot();
				pPC->addItemToExtraInventorySlot(pStashItem);

//				pStashItem->whenPCTake( pPC );

				// Stash에 마우스에 달려있던 아이템을 넣는다.
				pStash->remove(rack, index);
				pStash->insert(rack , index , pMouseItem);

//				pMouseItem->whenPCLost( pPC );

				//pStashItem->save(pPC->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
				// item저장 최적화. by sigi. 2002.5.13
				char pField[80];
				sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
				pStashItem->tinysave(pField);

				//pMouseItem->save(pPC->getName(), STORAGE_STASH, 0, rack, index);
				// item저장 최적화. by sigi. 2002.5.13
				sprintf(pField, "Storage=%d, X=%d, Y=%d", STORAGE_STASH, rack, index);
				pMouseItem->tinysave(pField);

				log(LOG_STASH_REMOVE_ITEM, pPC->getName(), "", pStashItem->toString());
				log(LOG_STASH_ADD_ITEM, pPC->getName(), "", pMouseItem->toString());

				Success = true;
			}
		} 
		else // 그 장소에 아이템이 없다면.
		{
			// Stash에 특정 아이템을 넣는다.
			pStash->insert(rack , index , pMouseItem);
			pPC->deleteItemFromExtraInventorySlot();
//			pMouseItem->whenPCLost(pPC);
			//pMouseItem->save(pPC->getName(), STORAGE_STASH, 0, rack, index);
			// item저장 최적화. by sigi. 2002.5.13
			char pField[80];
			sprintf(pField, "Storage=%d, X=%d, Y=%d", STORAGE_STASH, rack, index);
			pMouseItem->tinysave(pField);


			log(LOG_STASH_ADD_ITEM, pPC->getName(), "", pMouseItem->toString());

			Success = true;
		}

		if (!Success) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
		}
		else
		{
			if ( pMouseItem != NULL && pMouseItem->getItemClass() == Item::ITEM_CLASS_PET_ITEM )
			{
				PetItem* pPetItem = dynamic_cast<PetItem*>(pMouseItem);
				if ( pPetItem != NULL && pPetItem->getPetInfo() != NULL && pPetItem->getPetInfo() == pPC->getPetInfo() )
				{
					pPC->setPetInfo(NULL);
					pPC->initAllStatAndSend();
					sendPetInfo( pGamePlayer, true );
				}
			}
		}
	}
	catch (Throwable & t) 
	{ 
		//cout << t.toString(); 
	}

#endif	// __GAME_SERVER__

    __END_DEBUG
	__END_DEBUG_EX __END_CATCH
}
