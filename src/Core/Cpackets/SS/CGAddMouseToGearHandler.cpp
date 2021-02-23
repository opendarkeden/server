//////////////////////////////////////////////////////////////////////////////
// Filename    : CGAddMouseToGearHandler.cc
// Written By  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "CGAddMouseToGear.h"

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
	#include "ItemUtil.h"

	#include "Gpackets/GCModifyInformation.h"
	#include "Gpackets/GCCannotAdd.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGAddMouseToGearHandler::execute (CGAddMouseToGear* pPacket , Player* pPlayer)
	throw (ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	try 
	{
		GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
		Assert(pGamePlayer != NULL);

		Creature*   pCreature   = pGamePlayer->getCreature();
		Assert(pCreature != NULL);

		bool        Success     = false;

		if (pCreature->isSlayer()) 
		{
			Slayer* pSlayer    = dynamic_cast<Slayer*>(pCreature);
			Assert(pSlayer != NULL);

			Item*   pItem = pSlayer->getExtraInventorySlotItem();

			if (pItem == NULL)
			{
				GCCannotAdd _GCCannotAdd;
				_GCCannotAdd.setObjectID(pPacket->getObjectID());
				pPlayer->sendPacket(&_GCCannotAdd);
				return;
			}

			ObjectID_t ItemObjectID = pItem->getObjectID();
			SlotID_t   SlotID       = pPacket->getSlotID();
		
			// 아이템의 ObjectID가 일치하는지 체크한다.
			if (ItemObjectID == pPacket->getObjectID()) 
			{
				Item::ItemClass IClass = pItem->getItemClass();
				
				switch (SlotID) // 슬랏을 보고 그 슬랏에 맞는 아이템 유형인지 비교한다.
				{
					case Slayer::WEAR_HEAD:
						if (IClass == Item::ITEM_CLASS_HELM) Success = true;
						break;
					case Slayer::WEAR_NECK:
						if (IClass == Item::ITEM_CLASS_NECKLACE) Success = true;
						break;
					case Slayer::WEAR_FINGER1:
						if (IClass == Item::ITEM_CLASS_RING || IClass == Item::ITEM_CLASS_COUPLE_RING) Success = true;
						break;
					case Slayer::WEAR_FINGER2:
						if (IClass == Item::ITEM_CLASS_RING || IClass == Item::ITEM_CLASS_COUPLE_RING) Success = true;
						break;
					case Slayer::WEAR_FINGER3:
						if (IClass == Item::ITEM_CLASS_RING || IClass == Item::ITEM_CLASS_COUPLE_RING) Success = true;
						break;
					case Slayer::WEAR_FINGER4:
						if (IClass == Item::ITEM_CLASS_RING || IClass == Item::ITEM_CLASS_COUPLE_RING) Success = true;
						break;
					case Slayer::WEAR_WRIST1:
						if (IClass == Item::ITEM_CLASS_BRACELET) Success = true;
						break;
					case Slayer::WEAR_WRIST2:
						if (IClass == Item::ITEM_CLASS_BRACELET) Success = true;
						break;
					case Slayer::WEAR_LEFTHAND:
						if (IClass == Item::ITEM_CLASS_SHIELD) Success = true;
						break;
					case Slayer::WEAR_HAND3:
						if (IClass == Item::ITEM_CLASS_GLOVE) Success = true;
						break;
					case Slayer::WEAR_BODY:
						if (IClass == Item::ITEM_CLASS_COAT) Success = true;
						break;
					case Slayer::WEAR_BELT:
						if (IClass == Item::ITEM_CLASS_BELT) Success = true;
						break;
					case Slayer::WEAR_LEG:
						if (IClass == Item::ITEM_CLASS_TROUSER) Success = true;
						break;
					case Slayer::WEAR_FOOT:
						if (IClass == Item::ITEM_CLASS_SHOES) Success = true;
						break;
					case Slayer::WEAR_RIGHTHAND:
						if (isSlayerWeapon(IClass)) Success = true;
						break;
					case Slayer::WEAR_ZAP1:
					case Slayer::WEAR_ZAP2:
					case Slayer::WEAR_ZAP3:
					case Slayer::WEAR_ZAP4:
						if (IClass == Item::ITEM_CLASS_CORE_ZAP) Success = true;
						break;
					case Slayer::WEAR_PDA:
						if (IClass == Item::ITEM_CLASS_CARRYING_RECEIVER) Success = true;
						break;
					case Slayer::WEAR_SHOULDER:
						if (IClass == Item::ITEM_CLASS_SHOULDER_ARMOR) Success = true;
						break;
					default :
						break;
				}
				
				// 그 슬랏에 맞는 아이템을 장착하려고 하는지 체크한다.
				if (Success) pSlayer->wearItem((Slayer::WearPart)SlotID);
			}
		} 
		else if (pCreature->isVampire())
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);
			Assert(pVampire != NULL);

			Item*    pItem    = pVampire->getExtraInventorySlotItem();

			if (pItem == NULL)
			{
				GCCannotAdd _GCCannotAdd;
				_GCCannotAdd.setObjectID(pPacket->getObjectID());
				pPlayer->sendPacket(&_GCCannotAdd);
				return;
			}

			ObjectID_t ItemObjectID = pItem->getObjectID();
			SlotID_t   SlotID       = pPacket->getSlotID();
		
			// 아이템의 ObjectID가 일치하는지 체크한다.
			if (ItemObjectID == pPacket->getObjectID()) 
			{
				Item::ItemClass IClass = pItem->getItemClass();
				
				switch (SlotID) // 슬랏을 보고 그 슬랏에 맞는 아이템 유형인지 비교한다.
				{
					case Vampire::WEAR_NECK:
						if (IClass == Item::ITEM_CLASS_VAMPIRE_NECKLACE) Success = true;
						break;
					case Vampire::WEAR_FINGER1:
						if (IClass == Item::ITEM_CLASS_VAMPIRE_RING || IClass == Item::ITEM_CLASS_VAMPIRE_COUPLE_RING) Success = true;
						break;
					case Vampire::WEAR_FINGER2:
						if (IClass == Item::ITEM_CLASS_VAMPIRE_RING || IClass == Item::ITEM_CLASS_VAMPIRE_COUPLE_RING) Success = true;
						break;
					case Vampire::WEAR_FINGER3:
						if (IClass == Item::ITEM_CLASS_VAMPIRE_RING || IClass == Item::ITEM_CLASS_VAMPIRE_COUPLE_RING) Success = true;
						break;
					case Vampire::WEAR_FINGER4:
						if (IClass == Item::ITEM_CLASS_VAMPIRE_RING || IClass == Item::ITEM_CLASS_VAMPIRE_COUPLE_RING) Success = true;
						break;
					case Vampire::WEAR_WRIST1:
						if (IClass == Item::ITEM_CLASS_VAMPIRE_BRACELET) Success = true;
						break;
					case Vampire::WEAR_WRIST2:
						if (IClass == Item::ITEM_CLASS_VAMPIRE_BRACELET) Success = true;
						break;
					case Vampire::WEAR_EARRING1:
						if (IClass == Item::ITEM_CLASS_VAMPIRE_EARRING) Success = true;
						break;
					case Vampire::WEAR_EARRING2:
						if (IClass == Item::ITEM_CLASS_VAMPIRE_EARRING) Success = true;
						break;
					case Vampire::WEAR_BODY:
						if (IClass == Item::ITEM_CLASS_VAMPIRE_COAT) Success = true;
						break;
					case Vampire::WEAR_LEFTHAND:
						if (IClass == Item::ITEM_CLASS_VAMPIRE_WEAPON) Success = true;
						break;
					case Vampire::WEAR_RIGHTHAND:
						if (IClass == Item::ITEM_CLASS_VAMPIRE_WEAPON) Success = true;
						break;
					case Vampire::WEAR_AMULET1:
						if (IClass == Item::ITEM_CLASS_VAMPIRE_AMULET) Success = true;
						break;
					case Vampire::WEAR_AMULET2:
						if (IClass == Item::ITEM_CLASS_VAMPIRE_AMULET) Success = true;
						break;
					case Vampire::WEAR_AMULET3:
						if (IClass == Item::ITEM_CLASS_VAMPIRE_AMULET) Success = true;
						break;
					case Vampire::WEAR_AMULET4:
						if (IClass == Item::ITEM_CLASS_VAMPIRE_AMULET) Success = true;
						break;
					case Vampire::WEAR_ZAP1:
					case Vampire::WEAR_ZAP2:
					case Vampire::WEAR_ZAP3:
					case Vampire::WEAR_ZAP4:
						if (IClass == Item::ITEM_CLASS_CORE_ZAP) Success = true;
						break;
					case Vampire::WEAR_DERMIS:
						if (IClass == Item::ITEM_CLASS_DERMIS) Success = true;
						break;
					case Vampire::WEAR_PERSONA:
						if (IClass == Item::ITEM_CLASS_PERSONA) Success = true;
						break;

					default :
						break;
				}
				
				// 그 슬랏에 맞는 아이템을 장착하려고 하는지 체크한다.
				if (Success) pVampire->wearItem((Vampire::WearPart)SlotID);
			}
		}
		else if (pCreature->isOusters())
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
			Assert(pOusters != NULL);

			Item*    pItem    = pOusters->getExtraInventorySlotItem();

			if (pItem == NULL)
			{
				GCCannotAdd _GCCannotAdd;
				_GCCannotAdd.setObjectID(pPacket->getObjectID());
				pPlayer->sendPacket(&_GCCannotAdd);
				return;
			}

			ObjectID_t ItemObjectID = pItem->getObjectID();
			SlotID_t   SlotID       = pPacket->getSlotID();
		
			// 아이템의 ObjectID가 일치하는지 체크한다.
			if (ItemObjectID == pPacket->getObjectID()) 
			{
				Item::ItemClass IClass = pItem->getItemClass();
				
				switch (SlotID) // 슬랏을 보고 그 슬랏에 맞는 아이템 유형인지 비교한다.
				{
					case Ousters::WEAR_CIRCLET:
						if (IClass == Item::ITEM_CLASS_OUSTERS_CIRCLET) Success = true;
						break;
					case Ousters::WEAR_COAT:
						if (IClass == Item::ITEM_CLASS_OUSTERS_COAT) Success = true;
						break;
					case Ousters::WEAR_LEFTHAND:
					case Ousters::WEAR_RIGHTHAND:
						if (IClass == Item::ITEM_CLASS_OUSTERS_WRISTLET || IClass == Item::ITEM_CLASS_OUSTERS_CHAKRAM ) Success = true;
						break;
					case Ousters::WEAR_BOOTS:
						if (IClass == Item::ITEM_CLASS_OUSTERS_BOOTS) Success = true;
						break;
					case Ousters::WEAR_ARMSBAND1:
					case Ousters::WEAR_ARMSBAND2:
						if (IClass == Item::ITEM_CLASS_OUSTERS_ARMSBAND) Success = true;
						break;
					case Ousters::WEAR_RING1:
					case Ousters::WEAR_RING2:
						if (IClass == Item::ITEM_CLASS_OUSTERS_RING) Success = true;
						break;
					case Ousters::WEAR_NECKLACE1:
					case Ousters::WEAR_NECKLACE2:
					case Ousters::WEAR_NECKLACE3:
						if (IClass == Item::ITEM_CLASS_OUSTERS_PENDENT) Success = true;
						break;
					case Ousters::WEAR_STONE1:
					case Ousters::WEAR_STONE2:
					case Ousters::WEAR_STONE3:
					case Ousters::WEAR_STONE4:
						if (IClass == Item::ITEM_CLASS_OUSTERS_STONE) Success = true;
						break;

					case Ousters::WEAR_ZAP1:
					case Ousters::WEAR_ZAP2:
					case Ousters::WEAR_ZAP3:
					case Ousters::WEAR_ZAP4:
						if (IClass == Item::ITEM_CLASS_CORE_ZAP) Success = true;
						break;
					case Ousters::WEAR_FASCIA:
						if (IClass == Item::ITEM_CLASS_FASCIA) Success = true;
						break;
					case Ousters::WEAR_MITTEN:
						if (IClass == Item::ITEM_CLASS_MITTEN) Success = true;
						break;

					default :
						break;
				}
				
				// 그 슬랏에 맞는 아이템을 장착하려고 하는지 체크한다.
				if (Success) pOusters->wearItem((Ousters::WearPart)SlotID);
			}
		}

		// Adding에 실패 하였을 경우
		if (!Success) 
		{
			GCCannotAdd _GCCannotAdd;
			_GCCannotAdd.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotAdd);
		}
	} 
	catch (Throwable & t) 
	{
		//cout << t.toString();
	}

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH

}
