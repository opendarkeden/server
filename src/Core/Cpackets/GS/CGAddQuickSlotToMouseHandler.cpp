//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddQuickSlotToMouseHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGAddQuickSlotToMouse.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Ousters.h"
	#include "Inventory.h"
	#include "Item.h"

	#include "item/Belt.h"
	#include "item/OustersArmsband.h"

	#include "Gpackets/GCCannotAdd.h"

	#include <stdio.h>
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddQuickSlotToMouseHandler::execute (CGAddQuickSlotToMouse* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*   pCreature   = pGamePlayer->getCreature();

	try 
	{
		if ( pCreature->isSlayer() )
		{
			Slayer*     pSlayer     = dynamic_cast<Slayer*>(pCreature);
			SlotID_t    SlotID      = pPacket->getSlotID();

			if (!pSlayer->isWear(Slayer::WEAR_BELT))
			{
				GCCannotAdd _GCCannotAdd;
				_GCCannotAdd.setObjectID(pPacket->getObjectID());
				pPlayer->sendPacket(&_GCCannotAdd);
				return;
			}

			Item*      pBeltItem      = pSlayer->getWearItem(Slayer::WEAR_BELT);
			Inventory* pBeltInventory = ((Belt*)pBeltItem)->getInventory();

			if (SlotID >= pBeltInventory->getWidth())
			{
				GCCannotAdd _GCCannotAdd;
				_GCCannotAdd.setObjectID(pPacket->getObjectID());
				pPlayer->sendPacket(&_GCCannotAdd);
				return;
			}

			Item* pSlotItem = pBeltInventory->getItem(SlotID, 0);

			// 벨트에 아이템이 없거나, 마우스에 뭔가를 들고 있다면 더할 수 없다.
			if (pSlotItem == NULL || pSlayer->getExtraInventorySlotItem() != NULL)
			{
				GCCannotAdd _GCCannotAdd;
				_GCCannotAdd.setObjectID(pPacket->getObjectID());
				pPlayer->sendPacket(&_GCCannotAdd);
				return;
			}
			
			// 아이템을 벨트 인벤토리에서 지우고 Mouse로 이동시킨다.
			pBeltInventory->deleteItem(SlotID, 0);
			pSlayer->addItemToExtraInventorySlot(pSlotItem);
			//pSlotItem->save(pSlayer->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
			// item저장 최적화. by sigi. 2002.5.13
			char pField[80];
			sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
			pSlotItem->tinysave(pField);
		}

		if ( pCreature->isOusters() )
		{
			Ousters*     pOusters     = dynamic_cast<Ousters*>(pCreature);
			SlotID_t    SlotID      = pPacket->getSlotID();

			Ousters::WearPart part = ( SlotID > 2 ? Ousters::WEAR_ARMSBAND2 : Ousters::WEAR_ARMSBAND1 );
			if ( SlotID > 2 ) SlotID -= 3;

			if (!pOusters->isWear(part))
			{
				GCCannotAdd _GCCannotAdd;
				_GCCannotAdd.setObjectID(pPacket->getObjectID());
				pPlayer->sendPacket(&_GCCannotAdd);
				return;
			}

			Item*      pOustersArmsbandItem      = pOusters->getWearItem(part);
			Inventory* pOustersArmsbandInventory = ((OustersArmsband*)pOustersArmsbandItem)->getInventory();

			if (SlotID >= pOustersArmsbandInventory->getWidth())
			{
				GCCannotAdd _GCCannotAdd;
				_GCCannotAdd.setObjectID(pPacket->getObjectID());
				pPlayer->sendPacket(&_GCCannotAdd);
				return;
			}

			Item* pSlotItem = pOustersArmsbandInventory->getItem(SlotID, 0);

			// 벨트에 아이템이 없거나, 마우스에 뭔가를 들고 있다면 더할 수 없다.
			if (pSlotItem == NULL || pOusters->getExtraInventorySlotItem() != NULL)
			{
				GCCannotAdd _GCCannotAdd;
				_GCCannotAdd.setObjectID(pPacket->getObjectID());
				pPlayer->sendPacket(&_GCCannotAdd);
				return;
			}
			
			// 아이템을 벨트 인벤토리에서 지우고 Mouse로 이동시킨다.
			pOustersArmsbandInventory->deleteItem(SlotID, 0);
			pOusters->addItemToExtraInventorySlot(pSlotItem);
			//pSlotItem->save(pOusters->getName(), STORAGE_EXTRASLOT, 0, 0, 0);
			// item저장 최적화. by sigi. 2002.5.13
			char pField[80];
			sprintf(pField, "Storage=%d", STORAGE_EXTRASLOT);
			pSlotItem->tinysave(pField);
		}
	} 
	catch (Throwable & t) 
	{
		//cout << t.toString();
	}

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}
