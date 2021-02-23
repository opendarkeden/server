//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddGearToMouseHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGAddGearToMouse.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Ousters.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"

	#include "Gpackets/GCCannotAdd.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddGearToMouseHandler::execute (CGAddGearToMouse* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		Creature*   pCreature   = pGamePlayer->getCreature();
		bool        bSuccess    = false;
		SlotID_t    SlotID      = pPacket->getSlotID();

		Assert(pCreature != NULL);	

		if (pCreature->isSlayer()) 
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
			Assert(pSlayer != NULL);	

			// 마우스에 뭔가를 들고 있어선 안 되고,
			// 벗으려는 부분에 아이템을 입고 있지 않아서도 안 된다.
			if (pSlayer->getExtraInventorySlotItem() == NULL &&
				pSlayer->isWear((Slayer::WearPart)SlotID)) 
			{
				// 장착하고 있는 Item을 받아온다.
				Item* pItem = pSlayer->getWearItem((Slayer::WearPart)SlotID);

				// 아이템이 있는지 그 아이템의 ObjectID가 일치하는지 체크한다.
				if (pItem != NULL && pItem->getObjectID() == pPacket->getObjectID())
				{
					// 아이템을 장착창에서 지우고 Mouse로 이동시킨다.
					// 옷을 벗기면서 능력치를 다운시키고 벗은 아이템을 Mouse로 이동시킨다.
					pSlayer->takeOffItem((Slayer::WearPart)SlotID, true, true);
					bSuccess = true;
				}
			} 
		} 
		else if (pCreature->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

			Assert(pVampire != NULL);

			// 마우스에 뭔가를 들고 있어선 안 되고,
			// 벗으려는 부분에 아이템을 입고 있지 않아서도 안 된다.
			if (pVampire->getExtraInventorySlotItem() == NULL &&
				pVampire->isWear((Vampire::WearPart)SlotID))
			{
				// 장착하고 있는 Item을 받아온다.
				Item* pItem = pVampire->getWearItem((Vampire::WearPart)SlotID);

				// 아이템이 있는지 그 아이템의 ObjectID가 일치하는지 체크한다.
				if (pItem != NULL && pItem->getObjectID() == pPacket->getObjectID()) 
				{
					// 아이템을 장착창에서 지우고 Mouse로 이동시킨다.
					// 옷을 벗기면서 능력치를 다운시키고 벗은 아이템을 Mouse로 이동시킨다.
					pVampire->takeOffItem((Vampire::WearPart)SlotID, true, true);
					bSuccess = true;
				}
			} 
		}
		else if (pCreature->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);

			Assert(pOusters != NULL);

			// 마우스에 뭔가를 들고 있어선 안 되고,
			// 벗으려는 부분에 아이템을 입고 있지 않아서도 안 된다.
			if (pOusters->getExtraInventorySlotItem() == NULL &&
				pOusters->isWear((Ousters::WearPart)SlotID))
			{
				// 장착하고 있는 Item을 받아온다.
				Item* pItem = pOusters->getWearItem((Ousters::WearPart)SlotID);

				// 아이템이 있는지 그 아이템의 ObjectID가 일치하는지 체크한다.
				if (pItem != NULL && pItem->getObjectID() == pPacket->getObjectID()) 
				{
					// 아이템을 장착창에서 지우고 Mouse로 이동시킨다.
					// 옷을 벗기면서 능력치를 다운시키고 벗은 아이템을 Mouse로 이동시킨다.
					pOusters->takeOffItem((Ousters::WearPart)SlotID, true, true);
					bSuccess = true;
				}
			} 
		}

		if (!bSuccess) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
		}
	} 
	catch (Throwable & t) 
	{
		//cerr << t.toString();
	}

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}
