//////////////////////////////////////////////////////////////////////////////
// Filename    : CGReloadFromQuickSlotHandler.cc
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGReloadFromQuickSlot.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "Slayer.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "EffectManager.h"

	#include "item/Belt.h"
	#include "item/SG.h"
	#include "item/AR.h"
	#include "item/SMG.h"
	#include "item/SR.h"
	#include "item/Magazine.h"
	#include "ItemUtil.h"

	#include "skill/EffectReloadTimer.h"

	#include "Gpackets/GCCannotUse.h"
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGReloadFromQuickSlotHandler::execute (CGReloadFromQuickSlot* pPacket , Player* pPlayer)
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

		Assert(pCreature->isSlayer());

		Slayer*    pSlayer      = dynamic_cast<Slayer*>(pCreature);
		Item*      pArmsItem    = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		Item*      pBeltItem    = NULL;
		bool       Success      = false;
		ObjectID_t ItemObjectID = 0;
		SlotID_t   SlotID;
		
		if (pArmsItem != NULL) 
		{
			if (isArmsWeapon(pArmsItem)) 
			{
				Item* pBelt = pSlayer->getWearItem(Slayer::WEAR_BELT);
		
				if (pBelt == NULL)
				{
					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID(pPacket->getObjectID());
					pPlayer->sendPacket(&_GCCannotUse);
					return;
				}

				Inventory* pBeltInventory = ((Belt*)pBelt)->getInventory();
				SlotID = pPacket->getSlotID();

				if (SlotID >= pBeltInventory->getWidth())
				{
					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID(pPacket->getObjectID());
					pPlayer->sendPacket(&_GCCannotUse);
					return;
				}
		
				pBeltItem = pBeltInventory->getItem(SlotID, 0);
		
				if (pBeltItem == NULL)
				{
					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID(pPacket->getObjectID());
					pPlayer->sendPacket(&_GCCannotUse);
					return;
				}
		
				// 슬랏에 있는 아이템의 Object를 받는다.
				ItemObjectID = pBeltItem->getObjectID();

				// 아이템이 있는지 그 아이템의 ObjectID가 일치하는지 체크한다.
				if (ItemObjectID == pPacket->getObjectID() && 
					pBeltItem->getItemClass() == Item::ITEM_CLASS_MAGAZINE) 
				{
					SkillSlot*	pVivid = pSlayer->getSkill( SKILL_VIVID_MAGAZINE );
					bool		hasVivid = (pVivid != NULL) && pVivid->canUse();

					if (isSuitableMagazine(pArmsItem, pBeltItem, hasVivid))
					{
						Success = true;
					}
				}
			}
		} 

		// 검증 패킷을 날린다.
		EffectManager* pEffectManager = pSlayer->getEffectManager();
		if (Success && !pSlayer->isFlag(Effect::EFFECT_CLASS_RELOAD_TIMER))
		{
			EffectReloadTimer* pEffect = new EffectReloadTimer(pSlayer);
			pEffect->setFromInventory(false);
			pEffect->setObjectID(ItemObjectID);
			pEffect->setSlotID(SlotID);
			if (pSlayer->hasSkill(SKILL_FAST_RELOAD))
			{
				pEffect->setDeadline(7);    // 빠른 reload(0.7초)
			}
			else
			{
				pEffect->setDeadline(2*10);    // 보통 reload(2sec)
			}

			pSlayer->setFlag(Effect::EFFECT_CLASS_RELOAD_TIMER);
			pEffectManager->addEffect(pEffect);

		} 
		else 
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(ItemObjectID);

			pPlayer->sendPacket(&_GCCannotUse);
		}

	} 
	catch (Throwable & t) 
	{
		//cout << t.toString();
	}

#endif	// __GAME_SERVER__

    __END_DEBUG_EX __END_CATCH
}
