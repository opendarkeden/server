//////////////////////////////////////////////////////////////////////////////
// Filename    : CGUseItemFromInventoryHandler.cpp
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CGUseItemFromInventory.h"

#ifdef __GAME_SERVER__
	#include "GamePlayer.h"
	#include "Zone.h"
	#include "PlayerCreature.h"
	#include "Slayer.h"
	#include "Vampire.h"
	#include "Monster.h"
	#include "Inventory.h"
	#include "Item.h"
	#include "ItemInfo.h"
	#include "ItemInfoManager.h"
	#include "ItemFactoryManager.h"
	#include "ItemUtil.h"
	#include "ItemMineInfo.h"
	#include "skill/Skill.h"
	#include "SkillInfo.h"
	#include "skill/SkillUtil.h"
	#include "CreatureUtil.h"
    #include "EffectHPRecovery.h"
    #include "EffectMPRecovery.h"
	#include "Effect.h"
	#include "EffectReloadTimer.h"
	#include "EffectManager.h"
	#include "EffectAftermath.h"
	#include "EffectTranslation.h"
	#include "SimpleCreatureEffect.h"
	#include "EffectHasPet.h"
	#include "EffectBehemothForceScroll.h"
	#include "EffectSafeForceScroll.h"
	#include "EffectCarnelianForceScroll.h"
	#include "TradeManager.h"
	#include "skill/EffectSummonSylph.h"
	#include "ZoneUtil.h"
	#include <math.h>
	#include <stdio.h>

	#include "ctf/FlagManager.h"

	#include "ParkingCenter.h"
	#include "VariableManager.h"
	#include "DB.h"
	#include "GQuestManager.h"

	#include "item/Potion.h"
	#include "item/DyePotion.h"
	#include "item/Serum.h"
	#include "item/SlayerPortalItem.h"
	#include "item/Key.h"
	#include "item/ResurrectItem.h"
	#include "item/OustersSummonItem.h"
	#include "item/EffectItem.h"
	#include "item/PetItem.h"
	#include "item/PetFood.h"
	#include "item/SlayerPortalItem.h"
	#include "item/VampirePortalItem.h"
	#include "item/OustersSummonItem.h"
	#include "item/SMSItem.h"
	#include "item/TrapItem.h"
	#include "item/EventETC.h"
	#include "item/SubInventory.h"

	#include "GCCannotUse.h"
	#include "GCUseOK.h"
	#include "GCHPRecoveryStartToSelf.h"
	#include "GCHPRecoveryStartToOthers.h"
	#include "GCMPRecoveryStart.h"
	#include "GCAddHelicopter.h"
	#include "GCAddEffectToTile.h"
	#include "GCAddEffect.h"

	#include "GCDeleteObject.h"
	#include "GCAddSlayer.h"
	#include "GCAddVampire.h"
	#include "GCAddOusters.h"
	#include "GCCreateItem.h"

	#include "GCRemoveEffect.h"
	#include "GCStatusCurrentHP.h"
	#include "GCModifyInformation.h"
	#include "GCAddressListVerify.h"
	#include "GCSubInventoryInfo.h"

	#include "PacketUtil.h"
	#include "PetTypeInfo.h"
	#include "GDRLairManager.h"

	#include "EffectAutoTurret.h"
	#include "EffectTurretLaser.h"
	#include "EffectKillTimer.h"
	#include "SiegeManager.h"
	#include "Store.h"
	#include "DynamicZone.h"

	bool changeHairColorEx(PlayerCreature* pPC, Color_t color);
	bool changeBatColorEx(PlayerCreature* pPC, Color_t color);
	bool changeMasterEffectColorEx(PlayerCreature* pPC, BYTE color);
	bool changeAdvancementEffectColorEx(PlayerCreature* pPC, BYTE color);
	bool changeSkinColorEx(PlayerCreature* pPC, Color_t color);
	inline bool sendCannotUse(CGUseItemFromInventory* pPacket, Player* pPlayer);
#endif

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromInventoryHandler::execute(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

//	cout << "CGUseItemFromInventoryHandler " << endl;
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	GamePlayer* pGamePlayer = dynamic_cast<GamePlayer*>(pPlayer);
	Assert(pGamePlayer != NULL);

	Creature* pCreature = pGamePlayer->getCreature();
	Assert(pCreature != NULL);
	Assert(pCreature->isPC());

	PlayerCreature* pPC = dynamic_cast<PlayerCreature*>(pCreature);
	Assert(pPC != NULL);

	Inventory* pInventory = pPC->getInventory();
	Zone*      pZone      = pPC->getZone();

	Assert(pInventory != NULL);
	Assert(pZone != NULL);

	SubInventory* pInventoryItem = NULL;
	int invenID = 0;

	if (pPacket->getInventoryItemObjectID() != 0 )
	{
	//	cout << "서브 인벤토리에서 사용 : " << pPacket->getInventoryItemObjectID() << endl;
		CoordInven_t X, Y;
		pInventoryItem = dynamic_cast<SubInventory*>(pInventory->findItemOID(pPacket->getInventoryItemObjectID(), X, Y ));

		TradeManager* pTradeManager = pZone->getTradeManager();
		Assert(pTradeManager != NULL);

		if (pInventoryItem == NULL || pTradeManager->hasTradeInfo(pPC->getName()) )
		{
	//		cout << "근데 서브 인벤토리가 없다." <<endl;
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotUse);
			return;
		}

		pInventory = pInventoryItem->getInventory();
		invenID = pInventoryItem->getItemID();
	}

	CoordInven_t InvenX = pPacket->getX();
	CoordInven_t InvenY = pPacket->getY();

	//cout << "패킷날라옴 : " << pPacket->toString() << endl;

	// 인벤토리 좌표를 넘어가는 영역이라면 안 된다.
	if (InvenX >= pInventory->getWidth() || InvenY >= pInventory->getHeight())
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// 인벤토리에 그 아이템이 없다면 에러다.
	Item* pItem = pInventory->getItem(InvenX, InvenY);
	if (pItem == NULL)
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// 인벤토리에 있는 아이템의 Object를 받는다.
	ObjectID_t ItemObjectID = pItem->getObjectID();

	// OID가 일치하지 않거나, 사용할 수 없는 아이템이라면 에러다.
	if (ItemObjectID != pPacket->getObjectID() || !isUsableItem(pItem, pCreature))
	{
		//cout << "아템 사용 불가. 옵젝트 아디가 안 맞던가..." << endl;
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	if (invenID != 0 )
	{
		switch(pItem->getItemClass() )
		{
			case Item::ITEM_CLASS_PET_ITEM:
			case Item::ITEM_CLASS_PET_FOOD:
			case Item::ITEM_CLASS_SLAYER_PORTAL_ITEM:
			case Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM:
			case Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM:
			case Item::ITEM_CLASS_KEY:
				break;
			default:
				{
					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID(pPacket->getObjectID());
					pGamePlayer->sendPacket(&_GCCannotUse);
					return;
				}
		}
	}

	if (pPC->getStore()->getItemIndex(pItem) != 0xff )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// 아이템의 종류에 따라, 처리 함수를 분기시켜 준다.
	//cout << pItem->getItemClass() << endl;

	switch (pItem->getItemClass())
	{
		case Item::ITEM_CLASS_POTION:
			Assert(false);
			break;
		case Item::ITEM_CLASS_MAGAZINE:
			Assert(false);
			break;
		case Item::ITEM_CLASS_ETC:
			Assert(pItem->getItemType() != 0);
			executeTranslator(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_SERUM:
			Assert(false);
			break;
		case Item::ITEM_CLASS_VAMPIRE_ETC:
			Assert(pItem->getItemType() > 1);
			executeTranslator(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_SLAYER_PORTAL_ITEM:
			executeSlayerPortalItem(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM:
			executeOustersSummonItem(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_KEY:
			executeKeyItem(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_EVENT_ETC:
			executeFirecraker(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_DYE_POTION:
			executeDyePotion(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_RESURRECT_ITEM:
			executeResurrectItem(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_EFFECT_ITEM:
			if (pItem->getItemType() == 7
				|| pItem->getItemType() == 8
				|| pItem->getItemType() == 9
			   )
			{
				// 포스 스크롤일 경우
				executeForceScroll(pPacket, pPlayer);
			}
			else
			{
				executeEffectItem(pPacket, pPlayer);
			}
			break;
		case Item::ITEM_CLASS_PET_ITEM:
			executePetItem(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_PET_FOOD:
			executePetFood(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_EVENT_GIFT_BOX:
			executeEventGiftBox(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_SMS_ITEM:
			{
				SMSItemInfo* pItemInfo = dynamic_cast<SMSItemInfo*>(g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType() ));
				Assert(pItemInfo != NULL);

				uint charge = pItemInfo->getCharge();
				pPC->setSMSCharge(pPC->getSMSCharge() + charge);

				GCUseOK _GCUseOK;
				pGamePlayer->sendPacket(&_GCUseOK);

				GCAddressListVerify gcVerify;
				gcVerify.setCode(GCAddressListVerify::SMS_CHARGE_OK);
				gcVerify.setParameter(pPC->getSMSCharge());
				pGamePlayer->sendPacket(&gcVerify);

				char buffer[100];
				sprintf(buffer, "SMSCharge=%u", pPC->getSMSCharge());
				pPC->tinysave(buffer);

				// 쌓이지 않는 아이템은 바로바로 삭제해준다.
				pInventory->deleteItem(InvenX, InvenY);
				pItem->destroy();
				SAFE_DELETE(pItem);
			}
			break;

		case Item::ITEM_CLASS_TRAP_ITEM:
			executeTrapItem(pPacket, pPlayer);
			break;
		case Item::ITEM_CLASS_SUB_INVENTORY:
			{
				SubInventory* pSubInventoryItem = dynamic_cast<SubInventory*>(pItem);
				Inventory* pSubInventory = pSubInventoryItem->getInventory();
				InventoryInfo* pSubInventoryInfo = pSubInventory->getInventoryInfo();
				GCSubInventoryInfo gcInfo;
				gcInfo.setObjectID(pSubInventoryItem->getObjectID());
				gcInfo.setInventoryInfo(pSubInventoryInfo);
				pGamePlayer->sendPacket(&gcInfo);
			}
			break;
		default:
			Assert(false);
			break;
	}

#endif

    __END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromInventoryHandler::executePotion(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	//ObjectID_t      ItemObjectID = pItem->getObjectID();

	Assert(pCreature->isSlayer());

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);

	// 코마 상태라면 사용할 수 없다.
	if (pSlayer->isFlag(Effect::EFFECT_CLASS_COMA)
		// 송편인 경우는 유료 사용자가 아니면 사용할 수 없다.
		|| pItem->getItemType()==11 && !pGamePlayer->isPayPlaying() && !pGamePlayer->isPremiumPlay())
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	HP_t	MaxHP     = pSlayer->getHP(ATTR_MAX);
	HP_t	CurrentHP = pSlayer->getHP(ATTR_CURRENT);
	MP_t	MaxMP     = pSlayer->getMP(ATTR_MAX);
	MP_t	CurrentMP = pSlayer->getMP(ATTR_CURRENT);
	Potion* pPotion   = dynamic_cast<Potion*>(pItem);

	int HPQuantity = pPotion->getHPQuantity();
	int MPQuantity = pPotion->getMPQuantity();

	int HPDelayProvider = pPotion->getHPDelay();
	int MPDelayProvider = pPotion->getMPDelay();

	// Activation Effect가 걸려있다면 회복속도가 2배가 된다.
	if (pSlayer->isFlag(Effect::EFFECT_CLASS_ACTIVATION))
	{
		if (pPotion->getItemType() >= 14 && pPotion->getItemType() <= 17 )
		{
			// 쓸 수는 있다.
		}
		else
		{
			HPDelayProvider = (HPDelayProvider>>1);
			MPDelayProvider = (MPDelayProvider>>1);

			HPDelayProvider = max(HPDelayProvider, 1);
			MPDelayProvider = max(MPDelayProvider, 1);
		}
	}

	Attr_t INT = pSlayer->getINT();

	int PotionHPAmount=0, PotionMPAmount=0;

	// 만약 다른 종적의 Relic을 소유했다면, 혈청/포션의 효과가 50%로 떨어진다.
	PotionHPAmount = pPotion->getHPAmount();
	PotionMPAmount = pPotion->getMPAmount();
	
	int HPAmount = min(MaxHP - CurrentHP , PotionHPAmount);
	int MPAmount = min(MaxMP - CurrentMP , (int)(PotionMPAmount* (double)(1 + (double)((double)INT / 300.0))));

	bool notRecoverHP = false;
	bool notRecoverMP = false;

	// HP 회복양이 존재한다면...
	if (HPAmount != 0 && HPQuantity != 0)
	{
		if (CurrentHP < MaxHP) 
		{
			EffectManager* pEffectManager = pSlayer->getEffectManager();

			double temp     = (double)((double)HPAmount/(double)HPQuantity);
			int    Period   = (uint)ceil(temp);
			Turn_t Deadline = Period* HPDelayProvider;

			if (pSlayer->isFlag(Effect::EFFECT_CLASS_HP_RECOVERY)) 
			{
				Effect* pEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_HP_RECOVERY);
				EffectHPRecovery* pEffectHPRecoveryEffect = dynamic_cast<EffectHPRecovery*>(pEffect);

				// 기존의 단위양과 횟수로 채우는 HP양을 계산한다.
				// 그것을 현재 회복양에 더한다.
				int PrevHPAmount = pEffectHPRecoveryEffect->getHPQuantity()* pEffectHPRecoveryEffect->getPeriod();
				HPAmount = min((int)(HPAmount + PrevHPAmount), MaxHP - CurrentHP);

				// 둘 중에 큰 단위회복양과 작은 딜레이를 얻어낸다.
				HPQuantity      = max(HPQuantity,      (int)(pEffectHPRecoveryEffect->getHPQuantity()));
				HPDelayProvider = min(HPDelayProvider, (int)(pEffectHPRecoveryEffect->getDelay()));

				// 현재 회복양을 가지고, 얼마씩 몇번에 회복할 것인가를 결정한다.
				temp     = (double)((double)HPAmount/(double)HPQuantity);
				Period   = (uint)ceil(temp);
				Deadline = Period* HPDelayProvider;

				// HP Recovery effect를 갱신한다.
				pEffectHPRecoveryEffect->setDeadline(Deadline);
				pEffectHPRecoveryEffect->setDelay(HPDelayProvider);
				pEffectHPRecoveryEffect->setHPQuantity(HPQuantity);
				pEffectHPRecoveryEffect->setPeriod(Period);

				// 회복 시작하라는 패킷을 자신에게 보낸다.
				GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
				gcHPRecoveryStartToSelf.setPeriod(pEffectHPRecoveryEffect->getPeriod());
				gcHPRecoveryStartToSelf.setDelay(pEffectHPRecoveryEffect->getDelay());
				gcHPRecoveryStartToSelf.setQuantity(pEffectHPRecoveryEffect->getHPQuantity());

				pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

				// 회복 시작하라는 패킷을 다른이들에게 보낸다.
				// 회복 갱신 패킷, 시작과 똑 같은 패킷을 보낸다.
				GCHPRecoveryStartToOthers gcHPRecoveryStartToOthers;
				gcHPRecoveryStartToOthers.setObjectID(pSlayer->getObjectID());
				gcHPRecoveryStartToOthers.setPeriod(pEffectHPRecoveryEffect->getPeriod());
				gcHPRecoveryStartToOthers.setDelay(pEffectHPRecoveryEffect->getDelay());
				gcHPRecoveryStartToOthers.setQuantity(pEffectHPRecoveryEffect->getHPQuantity());

				pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcHPRecoveryStartToOthers, pSlayer);
				GCUseOK _GCUseOK;
				pGamePlayer->sendPacket(&_GCUseOK);
			} 
			else 
			{
				EffectHPRecovery* pEffectHPRecovery = new EffectHPRecovery();

				pEffectHPRecovery->setTarget(pSlayer);
				pEffectHPRecovery->setDeadline(Deadline);
				pEffectHPRecovery->setDelay(HPDelayProvider);
				pEffectHPRecovery->setNextTime(0);
				pEffectHPRecovery->setHPQuantity(HPQuantity);
				pEffectHPRecovery->setPeriod(Period);

				pEffectManager->addEffect(pEffectHPRecovery);

				// 회복 시작하라는 패킷을 자신에게 보낸다.
				GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
				gcHPRecoveryStartToSelf.setPeriod(Period);
				gcHPRecoveryStartToSelf.setDelay(HPDelayProvider);
				gcHPRecoveryStartToSelf.setQuantity(HPQuantity);

				pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

				// 회복 시작하라는 패킷을 보는이들에게 보낸다.
				GCHPRecoveryStartToOthers gcHPRecoveryStartToOthers;
				gcHPRecoveryStartToOthers.setObjectID(pSlayer->getObjectID());
				gcHPRecoveryStartToOthers.setPeriod(Period);
				gcHPRecoveryStartToOthers.setDelay(HPDelayProvider);
				gcHPRecoveryStartToOthers.setQuantity(HPQuantity);

				pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcHPRecoveryStartToOthers, pSlayer);
				GCUseOK _GCUseOK;
				pGamePlayer->sendPacket(&_GCUseOK);
			}

			decreaseItemNum(pItem, pInventory, pSlayer->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
		} 
		else 
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pGamePlayer->sendPacket(&_GCCannotUse);
			return;
		}
	} 
	else 
	{
		notRecoverHP = true;
	}

	// MP 회복양이 존재한다면...
	if (MPAmount != 0 && MPQuantity != 0)
	{
		if (CurrentMP < MaxMP) 
		{
			EffectManager* pEffectManager = pSlayer->getEffectManager();

			double temp     = (double)((double)MPAmount/(double)MPQuantity);
			uint   Period   = (uint)ceil(temp);
			Turn_t Deadline = Period* MPDelayProvider;

			if (pSlayer->isFlag(Effect::EFFECT_CLASS_MP_RECOVERY)) 
			{
				Effect* pEffect = pEffectManager->findEffect(Effect::EFFECT_CLASS_MP_RECOVERY);
				EffectMPRecovery* pEffectMPRecoveryEffect = dynamic_cast<EffectMPRecovery*>(pEffect);

				// 기존의 단위양과 횟수로 채우는 MP양을 계산한다.
				// 그것을 현재 회복양에 더한다.
				int PrevMPAmount = pEffectMPRecoveryEffect->getMPQuantity()* pEffectMPRecoveryEffect->getPeriod();
				MPAmount = min((int)(MPAmount + PrevMPAmount), MaxMP - CurrentMP);

				// 둘 중에 큰 단위회복양과 작은 딜레이를 얻어낸다.
				MPQuantity      = max(MPQuantity,      (int)(pEffectMPRecoveryEffect->getMPQuantity()));
				MPDelayProvider = min(MPDelayProvider, (int)(pEffectMPRecoveryEffect->getDelay()));

				// 현재 회복양을 가지고, 얼마씩 몇번에 회복할 것인가를 결정한다.
				temp     = (double)((double)MPAmount/(double)MPQuantity);
				Period   = (uint)ceil(temp);
				Deadline = Period* MPDelayProvider;

				// MP Recovery effect를 갱신한다.
				pEffectMPRecoveryEffect->setDeadline(Deadline);
				pEffectMPRecoveryEffect->setDelay(MPDelayProvider);
				pEffectMPRecoveryEffect->setMPQuantity(MPQuantity);
				pEffectMPRecoveryEffect->setPeriod(Period);

				// 회복 시작하라는 패킷을 자신에게 보낸다.
				GCMPRecoveryStart gcMPRecoveryStart;
				gcMPRecoveryStart.setPeriod(pEffectMPRecoveryEffect->getPeriod());
				gcMPRecoveryStart.setDelay(pEffectMPRecoveryEffect->getDelay());
				gcMPRecoveryStart.setQuantity(pEffectMPRecoveryEffect->getMPQuantity());

				pGamePlayer->sendPacket(&gcMPRecoveryStart);

				GCUseOK _GCUseOK;
				pGamePlayer->sendPacket(&_GCUseOK);
			} 
			else 
			{
				EffectMPRecovery* pEffectMPRecovery = new EffectMPRecovery();

				pEffectMPRecovery->setTarget(pSlayer);
				pEffectMPRecovery->setDeadline(Deadline);
				pEffectMPRecovery->setDelay(MPDelayProvider);
				pEffectMPRecovery->setNextTime(0);
				pEffectMPRecovery->setMPQuantity(MPQuantity);
				pEffectMPRecovery->setPeriod(Period);

				pEffectManager->addEffect(pEffectMPRecovery);

				// 회복 시작하라는 패킷을 자신에게 보낸다.
				GCMPRecoveryStart gcMPRecoveryStart;
				gcMPRecoveryStart.setPeriod(Period);
				gcMPRecoveryStart.setDelay(MPDelayProvider);
				gcMPRecoveryStart.setQuantity(MPQuantity);

				pGamePlayer->sendPacket(&gcMPRecoveryStart);

				GCUseOK _GCUseOK;
				pGamePlayer->sendPacket(&_GCUseOK);

			}

			decreaseItemNum(pItem, pInventory, pSlayer->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
		} 
		else 
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pGamePlayer->sendPacket(&_GCCannotUse);
			return;
		}
	} 
	else 
	{
		notRecoverMP = true;
	}

	if (notRecoverHP && notRecoverMP)
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

#endif

    __END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromInventoryHandler::executeMagazine(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	//Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	ObjectID_t      ItemObjectID = pItem->getObjectID();

	Assert(pCreature->isSlayer());

	Slayer*      pSlayer     = dynamic_cast<Slayer*>(pCreature);
	Item*        pArmsItem   = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
	bool         bSuccess    = false;

	if (pArmsItem != NULL) 
	{
		if (isArmsWeapon(pArmsItem))
		{
			SkillSlot*	pVivid = pSlayer->getSkill(SKILL_VIVID_MAGAZINE);
			bool		hasVivid = (pVivid != NULL) && pVivid->canUse();

			if (isSuitableMagazine(pArmsItem, pItem, hasVivid)) bSuccess = true;
		}
	} 

	// reload delay가 있으므로 effect에 등록 시킨다.
	EffectManager* pEffectManager = pSlayer->getEffectManager();
	if (pEffectManager == NULL) return;

	if (bSuccess && !pSlayer->isFlag(Effect::EFFECT_CLASS_RELOAD_TIMER)) 
	{
		EffectReloadTimer* pEffect = new EffectReloadTimer(pSlayer);
		
		pEffect->setFromInventory(true);
		pEffect->setObjectID(ItemObjectID);
		pEffect->setInventoryXY(InvenX, InvenY);
		
		// by sigi. 2002.12.3.  1초 --> 0.7초
		if (pSlayer->hasSkill(SKILL_FAST_RELOAD)) pEffect->setDeadline(7); // 빠른 reload(0.7초)
		else                                      pEffect->setDeadline(2*10); // 보통 reload(2sec)

		pSlayer->setFlag(Effect::EFFECT_CLASS_RELOAD_TIMER);
		pEffectManager->addEffect(pEffect);
	} 
	else 
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pPlayer->sendPacket(&_GCCannotUse);
	}

#endif

    __END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromInventoryHandler::executeETC(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	//Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	//ObjectID_t      ItemObjectID = pItem->getObjectID();

	// 아이템이 쌓이는 종류의 아이템이라면, 
	// 사용을 했으니 그만큼 삭제를 해 준다.
	if (isStackable(pItem))
	{
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
	}
	else 
	{
		// 쌓이지 않는 아이템은 바로바로 삭제해준다.
		pInventory->deleteItem(InvenX, InvenY);
		pItem->destroy();
		SAFE_DELETE(pItem);
	}

#endif

    __END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromInventoryHandler::executeSerum(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__


	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	//ObjectID_t      ItemObjectID = pItem->getObjectID();

	Assert(pCreature->isVampire());

	Vampire* pVampire = dynamic_cast<Vampire*>(pCreature);

	// 코마 상태라면 사용할 수 없다.
	if (pVampire->isFlag(Effect::EFFECT_CLASS_COMA)
		// 송편인 경우는 유료 사용자가 아니면 사용할 수 없다.
		|| pItem->getItemType()==5 && !pGamePlayer->isPayPlaying() && !pGamePlayer->isPremiumPlay())
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	HP_t   MaxHP       = pVampire->getHP(ATTR_MAX);
	HP_t   CurrentHP   = pVampire->getHP(ATTR_CURRENT);
	Serum* pSerum      = dynamic_cast<Serum*>(pItem);
	int    RegenHP     = 0;

	RegenHP = pSerum->getHPAmount();

	int    RegenPeriod = pSerum->getPeriod()*10; // 단위 시간의 주기
	int    RegenCount  = pSerum->getCount();     // 몇번 단위 시간을 반복할 것인가?

	int    RegenHPUnit = (int)((float)MaxHP* (float)RegenHP* 0.01); // 한번에 회복하는 HP의 양
	int    HPAmount    = min(MaxHP - CurrentHP , RegenHPUnit* RegenCount);

	// HP 회복양이 존재한다면...
	if (HPAmount != 0)
	{
		// 얼마씩 몇번 몇초마다.
		if (CurrentHP < MaxHP) 
		{
			EffectManager* pEffectManager = pVampire->getEffectManager(); 
			Turn_t 	       Period         = RegenCount; // 몇번 회복시키나?
			Turn_t	       Deadline       = RegenPeriod* Period;   // 언제 끝나나?

			if (pVampire->isFlag(Effect::EFFECT_CLASS_HP_RECOVERY)) 
			{
				Effect*     pEffect           = pEffectManager->findEffect(Effect::EFFECT_CLASS_HP_RECOVERY);
				EffectHPRecovery* pEffectHPRecoveryEffect = dynamic_cast<EffectHPRecovery*>(pEffect);

				// 몇번 더 해야 한다는 것을 갱신해 준다.
				Turn_t OldCount  = pEffectHPRecoveryEffect->getPeriod();
				Turn_t NewPeriod = OldCount + Period;
				pEffectHPRecoveryEffect->setPeriod(NewPeriod);
				pEffectHPRecoveryEffect->setDeadline(NewPeriod* RegenPeriod);

				// 회복 시작하라는 패킷을 자신에게 보낸다.
				GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
				gcHPRecoveryStartToSelf.setPeriod(NewPeriod); // 몇번 회복하나?
				gcHPRecoveryStartToSelf.setDelay(RegenPeriod); // 몇 초 단위로 하나?
				gcHPRecoveryStartToSelf.setQuantity(RegenHPUnit); // 한번에 얼마나 회복하나?

				pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

				// 회복 시작하라는 패킷을 다른이들에게 보낸다.
				// 회복 갱신 패킷, 시작과 똑 같은 패킷을 보낸다.
				GCHPRecoveryStartToOthers gcHPRecoveryStartToOthers;
				gcHPRecoveryStartToOthers.setObjectID(pVampire->getObjectID());
				gcHPRecoveryStartToOthers.setPeriod(NewPeriod);
				gcHPRecoveryStartToOthers.setDelay(RegenPeriod);
				gcHPRecoveryStartToOthers.setQuantity(RegenHPUnit);

				pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcHPRecoveryStartToOthers, pVampire);
				GCUseOK _GCUseOK;
				pGamePlayer->sendPacket(&_GCUseOK);
			} 
			else 
			{
				EffectHPRecovery* pEffectHPRecovery = new EffectHPRecovery();

				pEffectHPRecovery->setTarget(pVampire);
				pEffectHPRecovery->setDeadline(Deadline);
				pEffectHPRecovery->setDelay(RegenPeriod);
				pEffectHPRecovery->setNextTime(0);
				pEffectHPRecovery->setHPQuantity(RegenHPUnit);
				pEffectHPRecovery->setPeriod(Period);

				pEffectManager->addEffect(pEffectHPRecovery);

				// 회복 시작하라는 패킷을 자신에게 보낸다.
				GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
				gcHPRecoveryStartToSelf.setPeriod(Period);
				gcHPRecoveryStartToSelf.setDelay(RegenPeriod);
				gcHPRecoveryStartToSelf.setQuantity(RegenHPUnit);

				pGamePlayer->sendPacket(&gcHPRecoveryStartToSelf);

				// 회복 시작하라는 패킷을 보는이들에게 보낸다.
				GCHPRecoveryStartToOthers gcHPRecoveryStartToOthers;
				gcHPRecoveryStartToOthers.setObjectID(pVampire->getObjectID());
				gcHPRecoveryStartToOthers.setPeriod(Period);
				gcHPRecoveryStartToOthers.setDelay(RegenPeriod);
				gcHPRecoveryStartToOthers.setQuantity(RegenHPUnit);

				pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcHPRecoveryStartToOthers, pVampire);

				GCUseOK _GCUseOK;
				pGamePlayer->sendPacket(&_GCUseOK);
			}
		} 
		else 
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pGamePlayer->sendPacket(&_GCCannotUse);
			return;
		}
	}
	else
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	decreaseItemNum(pItem, pInventory, pVampire->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);

#endif

    __END_DEBUG_EX __END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromInventoryHandler::executeVampireETC(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	/*
	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	ObjectID_t      ItemObjectID = pItem->getObjectID();

	// 아이템이 쌓이는 종류의 아이템이라면, 
	// 사용을 했으니 그만큼 삭제를 해 준다.
	if (isStackable(pItem))
	{
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
	}
	else 
	{
		// 쌓이지 않는 아이템은 바로바로 삭제해준다.
		pInventory->deleteItem(InvenX, InvenY);
		pItem->destroy();
		SAFE_DELETE(pItem);
	}
	*/

#endif

    __END_DEBUG_EX __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromInventoryHandler::executeSlayerPortalItem(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();

	SubInventory* pInventoryItem = NULL;
	int invenID = 0;

	if (pPacket->getInventoryItemObjectID() != 0 )
	{
	//	cout << "서브 인벤토리에 넣기 : " << pPacket->getInventoryItemObjectID() << endl;
		CoordInven_t X, Y;
		pInventoryItem = dynamic_cast<SubInventory*>(pInventory->findItemOID(pPacket->getInventoryItemObjectID(), X, Y ));

		TradeManager* pTradeManager = pZone->getTradeManager();
		Assert(pTradeManager != NULL);

		if (pInventoryItem == NULL || pTradeManager->hasTradeInfo(pPC->getName()) )
		{
	//		cout << "근데 서브 인벤토리가 없다." <<endl;
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotUse);
			return;
		}

		pInventory = pInventoryItem->getInventory();
		invenID = pInventoryItem->getItemID();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	//ObjectID_t      ItemObjectID = pItem->getObjectID();

	Assert(pCreature->isSlayer());

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
	SlayerPortalItem* pPortalItem = dynamic_cast<SlayerPortalItem*>(pItem);

	Assert(pSlayer != NULL);
	Assert(pPortalItem != NULL);

	Store* pStore = pSlayer->getStore();
	if (pStore->isOpen() )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// 만약 Relic을 소유하고 있다면,헬기를 부를 수 없다.
	bool bHasRelic        = false;
	if (pSlayer->hasRelicItem() || pSlayer->isFlag(Effect::EFFECT_CLASS_HAS_FLAG ) || pSlayer->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER) )
	{
		bHasRelic         = true;
	}

	// 석화되어 있다면 헬기를 부를 수 없다.
	bool bParalyze = pSlayer->isFlag(Effect::EFFECT_CLASS_PARALYZE ) ? true : false;

	bool bZoneTypeCheck   = (pZone->getZoneType() == ZONE_NORMAL_FIELD) ? true : false;
	bool bCanUseCheck     = pSlayer->isRealWearing(pPortalItem);
	bool bChargeCheck     = (pPortalItem->getCharge() > 0) ? true : false;
	//bool bMotorcycleCheck = pSlayer->hasRideMotorcycle();
	bool bZoneCheck		= pZone->isNoPortalZone();

	//if (bZoneTypeCheck && bCanUseCheck && bChargeCheck && !bMotorcycleCheck)
	if (bZoneTypeCheck && bCanUseCheck && bChargeCheck && !bHasRelic && !bParalyze && !bZoneCheck)
	{
		// 아이템에 차지를 줄이고, 슬레이어에게 이펙트를 걸어준다.
		pPortalItem->setCharge(pPortalItem->getCharge()-1);
		//pPortalItem->save(pSlayer->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY); // 아이템 정보를 저장한다.
        // 아이템 저장 최적화. by sigi. 2002.5.13
        char pField[80];
	    sprintf(pField, "Charge=%d", pPortalItem->getCharge());
		pPortalItem->tinysave(pField);

		pSlayer->setFlag(Effect::EFFECT_CLASS_SLAYER_PORTAL);

		// 주변에다가 헬기 더하라는 패킷을 뿌린다.
		GCAddHelicopter gcAddHelicopter;
		gcAddHelicopter.setObjectID(pSlayer->getObjectID());
		gcAddHelicopter.setCode(0);
		pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcAddHelicopter);

		// 인증 패킷을 보내준다.
		GCUseOK gcUseOK;
		pPlayer->sendPacket(&gcUseOK);
	}
	else
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
	}

#endif

    __END_DEBUG_EX __END_CATCH
}

void CGUseItemFromInventoryHandler::executeOustersSummonItem(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_DEBUG_EX __BEGIN_TRY

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();

	SubInventory* pInventoryItem = NULL;
	int invenID = 0;

	if (pPacket->getInventoryItemObjectID() != 0 )
	{
	//	cout << "서브 인벤토리에 넣기 : " << pPacket->getInventoryItemObjectID() << endl;
		CoordInven_t X, Y;
		pInventoryItem = dynamic_cast<SubInventory*>(pInventory->findItemOID(pPacket->getInventoryItemObjectID(), X, Y ));

		TradeManager* pTradeManager = pZone->getTradeManager();
		Assert(pTradeManager != NULL);

		if (pInventoryItem == NULL || pTradeManager->hasTradeInfo(pPC->getName()) )
		{
	//		cout << "근데 서브 인벤토리가 없다." <<endl;
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotUse);
			return;
		}

		pInventory = pInventoryItem->getInventory();
		invenID = pInventoryItem->getItemID();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	//ObjectID_t      ItemObjectID = pItem->getObjectID();

	if (SiegeManager::Instance().isSiegeZone(pPC->getZoneID()) || pZone->isNoPortalZone() )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	Assert(pCreature->isOusters());

	Ousters* pOusters = dynamic_cast<Ousters*>(pCreature);
	OustersSummonItem* pSummonItem = dynamic_cast<OustersSummonItem*>(pItem);

	Assert(pOusters != NULL);
	Assert(pSummonItem != NULL);

	// 만약 Relic을 소유하고 있다면,헬기를 부를 수 없다.
	bool bHasRelic        = false;
	if (pOusters->hasRelicItem()||pOusters->isFlag(Effect::EFFECT_CLASS_REFINIUM_TICKET)
		||pOusters->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH )
		|| GDRLairManager::Instance().isGDRLairZone(pZone->getZoneID() )
		|| (pZone->isDynamicZone() && pZone->getDynamicZone()->getTemplateZoneID() == 4002)
	)
	{
		bHasRelic         = true;
	}

	// 석화되어 있다면 헬기를 부를 수 없다.
	bool bParalyze = pOusters->isFlag(Effect::EFFECT_CLASS_PARALYZE ) ? true : false;

	bool bCanUseCheck     = pOusters->isRealWearing(pSummonItem);
	bool bChargeCheck     = (pSummonItem->getCharge() > 0) ? true : false;
	//bool bMotorcycleCheck = pOusters->hasRideMotorcycle();

	SkillType_t       SkillType  = SKILL_SUMMON_SYLPH;
	SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
	OustersSummonItemInfo*	pItemInfo	 = dynamic_cast<OustersSummonItemInfo*>(g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType() ));
	Assert(pItemInfo != NULL);

	int RequireMP	= (int)pSkillInfo->getConsumeMP();
	bool bManaCheck	= hasEnoughMana(pOusters, RequireMP);
	bool bTileCheck = checkZoneLevelToUseSkill(pOusters);
	bool bEffect	= pOusters->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH);
	bool bSatisfyRequire = pOusters->satisfySkillRequire(pSkillInfo);
	bool bRangeCheck = checkZoneLevelToUseSkill(pOusters);

	if (bCanUseCheck && bChargeCheck && !bHasRelic && !bParalyze && bTileCheck
		&& bManaCheck && !bEffect && bSatisfyRequire && bRangeCheck)
	{
		GCModifyInformation gcMI;

		decreaseMana(pOusters, RequireMP, gcMI);
		// 아이템에 차지를 줄이고, 슬레이어에게 이펙트를 걸어준다.
		pSummonItem->setCharge(pSummonItem->getCharge()-1);
		//pSummonItem->save(pOusters->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY); // 아이템 정보를 저장한다.
        // 아이템 저장 최적화. by sigi. 2002.5.13
        char pField[80];
	    sprintf(pField, "Charge=%d", pSummonItem->getCharge());
		pSummonItem->tinysave(pField);

		// 이팩트 클래스를 만들어 붙인다.
		EffectSummonSylph* pEffect = new EffectSummonSylph(pOusters);
		pEffect->setEClass((Effect::EffectClass)pItemInfo->getEffectID());
		pOusters->addEffect(pEffect);
		pOusters->setFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH);

		OUSTERS_RECORD prev;
		pOusters->getOustersRecord(prev);
		pOusters->initAllStat();
		pOusters->addModifyInfo(prev, gcMI);

		// 인증 패킷을 보내준다.
		GCUseOK gcUseOK;
		pPlayer->sendPacket(&gcUseOK);
		pPlayer->sendPacket(&gcMI);

		GCAddEffect gcAddEffect;
		gcAddEffect.setObjectID(pOusters->getObjectID());
		gcAddEffect.setEffectID(pEffect->getSendEffectClass());
		gcAddEffect.setDuration(pEffect->getRemainDuration());

		pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &gcAddEffect, pOusters);
		pPlayer->sendPacket(&gcAddEffect);

		if (pOusters->getPetInfo() != NULL )
		{
			pOusters->setPetInfo(NULL);
			sendPetInfo(pGamePlayer, true);
		}

		pOusters->getGQuestManager()->rideMotorcycle();
	}
	else
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
	}

	

#endif

	__END_DEBUG_EX __END_CATCH
}


void CGUseItemFromInventoryHandler::executeKeyItem(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	//cout << pPacket->toString().c_str() << endl;

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();

	SubInventory* pInventoryItem = NULL;
	int invenID = 0;

	if (pPacket->getInventoryItemObjectID() != 0 )
	{
//		cout << "서브 인벤토리에 넣기 : " << pPacket->getInventoryItemObjectID() << endl;
		CoordInven_t X, Y;
		pInventoryItem = dynamic_cast<SubInventory*>(pInventory->findItemOID(pPacket->getInventoryItemObjectID(), X, Y ));

		TradeManager* pTradeManager = pZone->getTradeManager();
		Assert(pTradeManager != NULL);

		if (pInventoryItem == NULL || pTradeManager->hasTradeInfo(pPC->getName()) )
		{
	//		cout << "근데 서브 인벤토리가 없다." <<endl;
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotUse);
			return;
		}

		pInventory = pInventoryItem->getInventory();
		invenID = pInventoryItem->getItemID();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	//ObjectID_t      ItemObjectID = pItem->getObjectID();
	//
	if (SiegeManager::Instance().isSiegeZone(pPC->getZoneID()) )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// SLAYER가 아니라면 오토바이를 호출할 수 없다.
	Assert(pCreature->isSlayer());

	Slayer* pSlayer = dynamic_cast<Slayer*>(pCreature);
	
	// 소환 가능 상태 설정이 되어있어야 한다.
	// 코마 상태라면 사용할 수 없다.
	// 아이템이 열쇠 아이템이 아니라면, 오토바이를 호출할 수 없다.
	// 마스터 레어나 포탈 사용 불가 지역엔 오토바이 소환 불가
	// premium 사용자만 호출가능하다.
	if (!g_pVariableManager->isSummonMotorcycle()
		|| pSlayer->hasRideMotorcycle()
		|| pItem->getItemClass() != Item::ITEM_CLASS_KEY
		|| pSlayer->isFlag(Effect::EFFECT_CLASS_COMA)
		|| (pZone->getZoneLevel(pCreature->getX(), pCreature->getY()) & SAFE_ZONE)
		|| pZone->isMasterLair() || pZone->isNoPortalZone()
		|| (!pGamePlayer->isPremiumPlay() && !pGamePlayer->isPayPlaying())
		|| g_pFlagManager->isInPoleField(ZONE_COORD(pZone->getZoneID(), pCreature->getX(), pCreature->getY() ) )
		|| GDRLairManager::Instance().isGDRLairZone(pZone->getZoneID() )
	)
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	// 기존에 아이템이 생성되어 있는지를 확인한다.
	ItemID_t targetID = dynamic_cast<Key*>(pItem)->getTarget();

	Statement* pStmt   = NULL;
	Result*    pResult = NULL;

	// targetID가 0인 경우는.. targetID(motorcycleObject의 ItemID)가 설정이 안된 경우다.
	// 이 때는 임시로 targetID를 key의 ItemID와 같게 하면 된다...고 본다.
	// targetID가 motorcycle의 itemID로 들어가기 때문에..
	// broadcasting 등에서.. Assert()에 의해서 다운되었다...고 보여진다.  - -;
	// by sigi. 2002.12.25 x-mas T_T;
	if (targetID==0)
	{
		Key* pKey = dynamic_cast<Key*>(pItem);
		Assert(pKey != NULL);

		targetID = pKey->setNewMotorcycle(pSlayer);
/*		// (!) MotorcycleObject를 생성하고 MotorcycleItemID==Target를 받아야 한다.
		// 이 코드 제발 함수로 빼기를.. -_-; by sigi
		Key* pKey = dynamic_cast<Key*>(pItem);

		KeyInfo* pKeyInfo = dynamic_cast<KeyInfo*>(g_pItemInfoManager->getItemInfo(pKey->getItemClass(), pKey->getItemType() ));
		Assert(pKeyInfo != NULL);

		list<OptionType_t> option;
		ItemType_t motorcycleType = pKeyInfo->getTargetType();

		if (pKeyInfo->getOptionType() != 0 ) option.push_back(pKeyInfo->getOptionType());

		Item* pMotorcycle = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_MOTORCYCLE, motorcycleType, option);
		Assert(pMotorcycle != NULL);
		(pZone->getObjectRegistry()).registerObject(pMotorcycle);

		pMotorcycle->create(pSlayer->getName(), STORAGE_ZONE, pZone->getZoneID(), pSlayer->getX(), pSlayer->getY());
		pKey->setTarget(pMotorcycle->getItemID());

		targetID = pMotorcycle->getItemID();

		// targetID를 DB에도 update시켜야 한다.
		BEGIN_DB
		{
			pStmt   = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pResult = pStmt->executeQuery(
						"UPDATE KeyObject SET Target=%lu WHERE ItemID=%lu", 
									targetID, pKey->getItemID());

			SAFE_DELETE(pStmt);
		}
		END_DB(pStmt)

		// log
		filelog("motorcycle.txt", "[SetTargetID] Owner = %s, KeyID = %lu, Key's targetID = %lu, MotorcycleID = %lu", pSlayer->getName().c_str(), pKey->getItemID(), pKey->getTarget(), pMotorcycle->getItemID());

		// 밑에서 pMotorcycle을 사용해도 되겠지만, 기존 코드 안 건드릴려고 여기서 지운다. 
		SAFE_DELETE(pMotorcycle);*/
	}
	else
	{
		// 한번 모터사이클이랑 키랑 연결됐는데 모터사이클을 누가 자꾸 지우나보다.
		// 키에 연결된 모터사이클이 실제로 디비에 있는지 체크하고 없으면 새로 만들어서 넣어준다.
		BEGIN_DB
		{
			pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
			pResult = pStmt->executeQuery("SELECT ItemID FROM MotorcycleObject WHERE ItemID=%lu", targetID);
			
			if (!pResult->next() )
			{
				Key* pKey = dynamic_cast<Key*>(pItem);
				Assert(pKey != NULL);

				targetID = pKey->setNewMotorcycle(pSlayer);
			}

			SAFE_DELETE(pStmt);
		}
		END_DB(pStmt);
	}

	
	// 필살 방어 코드 -_-;
	if (targetID==0)
	{
		filelog("errorLog.txt", "[ActionRedeemMotorcycle] itemID=%lu, motorItemID=%lu", (int)pItem->getItemID(), (int)targetID);
		return;
	}


	if (g_pParkingCenter->hasMotorcycleBox(targetID)) 
	{
		//cout << "기존에 불려진 오토바이가 있습니다" << endl;

		MotorcycleBox* pMotorcycleBox = g_pParkingCenter->getMotorcycleBox(targetID);

		if (pMotorcycleBox!=NULL
			&& !pMotorcycleBox->isTransport())
		{
			Zone* pMotorZone = pMotorcycleBox->getZone();
			ZoneCoord_t motorX = pMotorcycleBox->getX();
			ZoneCoord_t motorY = pMotorcycleBox->getY();
			Motorcycle* pMotorcycle = pMotorcycleBox->getMotorcycle();

			// 같은 존에 있는 경우
			// 거리가 너무 가까우면 부르지 말자~
			if (pMotorZone!=pZone
				|| pSlayer->getDistance(motorX, motorY) > 15)
			{
				// 다른 zone으로 이동중이라고 표시한다.
				pMotorcycleBox->setTransport();

				// motorcycle을 slayer의 zone으로 옮긴다.
				pMotorZone->transportItem(motorX, motorY, pMotorcycle, 
											pZone, pSlayer->getX(), pSlayer->getY());

				// Use OK 대용이다.
				// Use하면 아이템이 사라지던가 그렇지 싶다. - -;
				/*
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
				*/

				// 한동안 delay를 줘야하는데..
			}
		}

		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);

		return;
	}

	BEGIN_DB
	{
		pStmt = g_pDatabaseManager->getConnection("DARKEDEN")->createStatement();
		pResult = pStmt->executeQuery("SELECT ItemID, ItemType, OptionType, Durability FROM MotorcycleObject WHERE ItemID=%lu", targetID);

		ItemID_t     itemID;
		ItemType_t   itemType;
		list<OptionType_t> optionTypes;
		Durability_t durability;

		bool bFound = false;

		if (pResult->next())
		{
			bFound = true;

			itemID     = pResult->getInt(1);
			itemType   = pResult->getInt(2);

			string optionField = pResult->getString(3);
			setOptionTypeFromField(optionTypes, optionField);

			durability = pResult->getInt(4);
		}
		else
		{
			itemID     = targetID;
			itemType   = 0;
			durability = 300;
		}

		// 새로운 오토바이 객체를 생성한다.
		Motorcycle* pMotorcycle = new Motorcycle(itemType, optionTypes);

		Assert(pMotorcycle != NULL);

		pMotorcycle->setItemID(itemID);
		pMotorcycle->setDurability(durability);

		// Object ID 할당받기
		(pZone->getObjectRegistry()).registerObject(pMotorcycle);


		// 오토바이를 존에 추가한다.
		//cout << "오토바이를 존에 추가합니다" << pSlayer->getX() << " " << pSlayer->getY() << endl;
		TPOINT pt = pZone->addItem(pMotorcycle, pSlayer->getX(), pSlayer->getY(), false);

		if(pt.x == -1)
		{
			StringStream msg;
			msg << "오토바이를 존에 넣을 수 없습니다: "
				<< "ZoneID=" << (int)pZone->getZoneID()
				<< ", X=" << (int)pSlayer->getX()
				<< ", Y=" << (int)pSlayer->getY();

			filelog("motorError.txt", "%s", msg.toString().c_str());
			//throw Error("오토바이를 존에 넣을 수 없습니다");

			SAFE_DELETE(pMotorcycle);
		}
		else
		{
			if (!bFound)
			{
				// by sigi. 2002.10.14
				pStmt->executeQuery(
				"INSERT INTO MotorcycleObject (ItemID, ObjectID, ItemType, OwnerID, Storage, StorageID, X, Y, OptionType, Durability) Values (%d, %d, %d, '', %d, %d, %d, %d, '', %d)",
					itemID, pMotorcycle->getObjectID(), itemType, STORAGE_ZONE, pZone->getZoneID(), pt.x, pt.y, durability);
			}

			// 오토바이를 Parking Center에 등록한다.
			MotorcycleBox* pBox = new MotorcycleBox(pMotorcycle, pZone, pt.x, pt.y);
			Assert(pBox != NULL);
			g_pParkingCenter->addMotorcycleBox(pBox);
		}


		// 검증 패킷이다.
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		//}
			/*
		else
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pGamePlayer->sendPacket(&_GCCannotUse);

			SAFE_DELETE(pStmt);
			return;
		}
		*/

		SAFE_DELETE(pStmt);
	}
	END_DB(pStmt);
#endif
    __END_DEBUG_EX __END_CATCH
}

#ifdef __GAME_SERVER__

static const Effect::EffectClass FirecrackerEffects[] =
{
	Effect::EFFECT_CLASS_FIRE_CRACKER_1,				// 0
	Effect::EFFECT_CLASS_FIRE_CRACKER_2,				// 1
	Effect::EFFECT_CLASS_FIRE_CRACKER_3,				// 2
	Effect::EFFECT_CLASS_DRAGON_FIRE_CRACKER,			// 3
	Effect::EFFECT_CLASS_FIRE_CRACKER_4,				// 4
	Effect::EFFECT_CLASS_FIRE_CRACKER_VOLLEY_1,			// 5
	Effect::EFFECT_CLASS_FIRE_CRACKER_VOLLEY_2,			// 6
	Effect::EFFECT_CLASS_FIRE_CRACKER_VOLLEY_3,			// 7
	Effect::EFFECT_CLASS_FIRE_CRACKER_VOLLEY_4,			// 8
	Effect::EFFECT_CLASS_FIRE_CRACKER_WIDE_VOLLEY_1,	// 9
	Effect::EFFECT_CLASS_FIRE_CRACKER_WIDE_VOLLEY_2,	// 10
	Effect::EFFECT_CLASS_FIRE_CRACKER_WIDE_VOLLEY_3,	// 11
	Effect::EFFECT_CLASS_FIRE_CRACKER_WIDE_VOLLEY_4,	// 12
	Effect::EFFECT_CLASS_FIRE_CRACKER_STORM				// 13
};

#endif

void CGUseItemFromInventoryHandler::executeFirecraker(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	//cout << pPacket->toString().c_str() << endl;

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	ObjectID_t      ItemObjectID = pItem->getObjectID();

	if (pItem->getItemType() >= 14 )
	{
		EventETCInfo* pInfo = dynamic_cast<EventETCInfo*>(g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType() ));
		Assert(pInfo != NULL);

		int amount = pInfo->getFunction();

		GCModifyInformation gcMI;
		bool HPRegen=false, MPRegen=false;
		HP_t CurrentHP = 0, MaxHP = 0;
		if (pPC->isSlayer() )
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
			CurrentHP = pSlayer->getHP();
			MaxHP = pSlayer->getHP(ATTR_MAX);
		}
		else if (pPC->isVampire() )
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
			CurrentHP = pVampire->getHP();
			MaxHP = pVampire->getHP(ATTR_MAX);
		}
		else if (pPC->isOusters() )
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
			CurrentHP = pOusters->getHP();
			MaxHP = pOusters->getHP(ATTR_MAX);
		}

		if (CurrentHP < MaxHP )
		{
			CurrentHP += min(amount, MaxHP-CurrentHP);
			GCStatusCurrentHP gcHP;
			gcHP.setObjectID(pPC->getObjectID());
			gcHP.setCurrentHP(CurrentHP);
			pZone->broadcastPacket(pPC->getX(), pPC->getY(), &gcHP);

			gcMI.addLongData(MODIFY_CURRENT_HP, CurrentHP);
			HPRegen = true;

			if (pPC->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
				pSlayer->setHP(CurrentHP);
			}
			else if (pPC->isVampire() )
			{
				Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
				pVampire->setHP(CurrentHP);
			}
			else if (pPC->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
				pOusters->setHP(CurrentHP);
			}
		}

		MP_t CurrentMP = 0, MaxMP = 0;
		if (pPC->isSlayer() )
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
			CurrentMP = pSlayer->getMP();
			MaxMP = pSlayer->getMP(ATTR_MAX);
		}
		else if (pPC->isOusters() )
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
			CurrentMP = pOusters->getMP();
			MaxMP = pOusters->getMP(ATTR_MAX);
		}

		if (CurrentMP < MaxMP )
		{
			CurrentMP += min(amount, MaxMP-CurrentMP);
			gcMI.addLongData(MODIFY_CURRENT_MP, CurrentMP);
			MPRegen = true;

			if (pPC->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
				pSlayer->setMP(CurrentMP);
			}
			else if (pPC->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
				pOusters->setMP(CurrentMP);
			}
		}

		if (!HPRegen && !MPRegen )
		{
			sendCannotUse(pPacket, pPlayer);
			return;
		}
		else
		{
			pPlayer->sendPacket(&gcMI);
		}
	}
	else
	{
		// 타일에 스킬을 쓰는 것이라고 보고 쓸 수 있는지를 체크한다.
		// 안전지대에서는 사용할 수 없다.
		if (!isAbleToUseTileSkill(pCreature )
			|| (pZone->getZoneLevel(pCreature->getX(), pCreature->getY()) & COMPLETE_SAFE_ZONE)
			|| ItemObjectID != pPacket->getObjectID()
			)
		{
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pGamePlayer->sendPacket(&_GCCannotUse);
			return;
		}

		Effect::EffectClass effectClass = FirecrackerEffects[ pItem->getItemType() ];

	/*	switch (pItem->getItemType() )
		{
			case 0:
				effectClass = Effect::EFFECT_CLASS_FIRE_CRACKER_1;
				break;

			case 1:
				effectClass = Effect::EFFECT_CLASS_FIRE_CRACKER_2;
				break;

			case 2:
				effectClass = Effect::EFFECT_CLASS_FIRE_CRACKER_3;
				break;

			case 3:
				effectClass = Effect::EFFECT_CLASS_DRAGON_FIRE_CRACKER;
				break;

			case 4:
				effectClass = Effect::EFFECT_CLASS_FIRE_CRACKER_4;
				break;

			default:
				Assert(false);
				break;
		}*/
		// 에펙트를 만들어서 브로드캐스팅 한다.
		GCAddEffectToTile gcAddEffectToTile;
		gcAddEffectToTile.setObjectID(pCreature->getObjectID());
		gcAddEffectToTile.setEffectID(effectClass);
		gcAddEffectToTile.setXY(pCreature->getX(), pCreature->getY());
		gcAddEffectToTile.setDuration(10);  // 별 의미 없다 그냥 1초

		pZone->broadcastPacket(pCreature->getX(), pCreature->getY(), &gcAddEffectToTile);
	}

	if (isStackable(pItem))
	{
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
	}
	else 
	{
		// 쌓이지 않는 아이템은 바로바로 삭제해준다.
		pInventory->deleteItem(InvenX, InvenY);
		pItem->destroy();
		SAFE_DELETE(pItem);
	}

	// 아이템을 사용했다고 클라이언트에 알린다.
	GCUseOK gcUseOK;
	pGamePlayer->sendPacket(&gcUseOK);

#endif
    __END_DEBUG_EX __END_CATCH
}

void CGUseItemFromInventoryHandler::executeDyePotion(CGUseItemFromInventory* pPacket, Player* pPlayer) 
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	DyePotionInfo*	pItemInfo	 = dynamic_cast<DyePotionInfo*>(g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType() ));
	bool			bInitAllStat = false;
	bool			bRefresh = true;

	if (pItem->getObjectID() != pPacket->getObjectID() ||
		pItemInfo == NULL )
	{
		sendCannotUse(pPacket, pPlayer);
		return;
	}

	BYTE func = pItemInfo->getFunctionFlag();
	int funcv = pItemInfo->getFunctionValue();

	if (func == DyePotionInfo::FUNCTION_HAIR && pPC->isVampire() )
	{
		sendCannotUse(pPacket, pPlayer);
		return;
	}

	if (func == DyePotionInfo::FUNCTION_SKIN && pPC->isOusters() )
	{
		sendCannotUse(pPacket, pPlayer);
		return;
	}

	switch (func )
	{
		case DyePotionInfo::FUNCTION_HAIR:
			{
				if (!changeHairColorEx(pPC, funcv ) )
				{
					sendCannotUse(pPacket, pPlayer);
					return;
				}
			}
			break;
		case DyePotionInfo::FUNCTION_SKIN:
			{
				if (!changeSkinColorEx(pPC, funcv ) )
				{
					sendCannotUse(pPacket, pPlayer);
					return;
				}
			}
			break;
		case DyePotionInfo::FUNCTION_SEX:
			{
				int code = changeSexEx(pPC);
				if (code != 0 )
				{
					// -_-; 성전환 아이템만 오브젝트 아이디에다가 에러코드 넣어준다. ㅜ.ㅠ
					GCCannotUse _GCCannotUse;
					_GCCannotUse.setObjectID((ObjectID_t)code);
					pPlayer->sendPacket(&_GCCannotUse);

					return;
				}
				else bInitAllStat = true;
			}
			break;
		case DyePotionInfo::FUNCTION_BAT:
			{
				if (!changeBatColorEx(pPC, funcv ) )
				{
					sendCannotUse(pPacket, pPlayer);
					return;
				}
			}
			break;
		case DyePotionInfo::FUNCTION_MASTER_EFFECT:
			{
				if (!changeMasterEffectColorEx(pPC, (BYTE)funcv ) )
				{
					sendCannotUse(pPacket, pPlayer);
					return;
				}
			}
			break;
		case DyePotionInfo::FUNCTION_REGEN:
			{
				GCModifyInformation gcMI;
				bool HPRegen=false, MPRegen=false;
				HP_t CurrentHP = 0, MaxHP = 0;
				if (pPC->isSlayer() )
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
					CurrentHP = pSlayer->getHP();
					MaxHP = pSlayer->getHP(ATTR_MAX);
				}
				else if (pPC->isVampire() )
				{
					Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
					CurrentHP = pVampire->getHP();
					MaxHP = pVampire->getHP(ATTR_MAX);
				}
				else if (pPC->isOusters() )
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
					CurrentHP = pOusters->getHP();
					MaxHP = pOusters->getHP(ATTR_MAX);
				}

				if (CurrentHP < MaxHP )
				{
					CurrentHP += min(1000, MaxHP-CurrentHP);
					GCStatusCurrentHP gcHP;
					gcHP.setObjectID(pPC->getObjectID());
					gcHP.setCurrentHP(CurrentHP);
					pZone->broadcastPacket(pPC->getX(), pPC->getY(), &gcHP);

					gcMI.addLongData(MODIFY_CURRENT_HP, CurrentHP);
					HPRegen = true;

					if (pPC->isSlayer() )
					{
						Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
						pSlayer->setHP(CurrentHP);
					}
					else if (pPC->isVampire() )
					{
						Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
						pVampire->setHP(CurrentHP);
					}
					else if (pPC->isOusters() )
					{
						Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
						pOusters->setHP(CurrentHP);
					}
				}

				MP_t CurrentMP = 0, MaxMP = 0;
				if (pPC->isSlayer() )
				{
					Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
					CurrentMP = pSlayer->getMP();
					MaxMP = pSlayer->getMP(ATTR_MAX);
				}
				else if (pPC->isOusters() )
				{
					Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
					CurrentMP = pOusters->getMP();
					MaxMP = pOusters->getMP(ATTR_MAX);
				}

				if (CurrentMP < MaxMP )
				{
					CurrentMP += min(1000, MaxMP-CurrentMP);
					gcMI.addLongData(MODIFY_CURRENT_MP, CurrentMP);
					MPRegen = true;

					if (pPC->isSlayer() )
					{
						Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
						pSlayer->setMP(CurrentMP);
					}
					else if (pPC->isOusters() )
					{
						Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
						pOusters->setMP(CurrentMP);
					}
				}

				if (!HPRegen && !MPRegen )
				{
					sendCannotUse(pPacket, pPlayer);
					return;
				}
				else
				{
					pPlayer->sendPacket(&gcMI);
				}

				bRefresh = false;
			}
			break;
		case DyePotionInfo::FUNCTION_ADVANCEMENT_EFFECT:
			{
				if (!changeAdvancementEffectColorEx(pPC, (BYTE)funcv ) )
				{
					sendCannotUse(pPacket, pPlayer);
					return;
				}

				bRefresh = true;
			}
			break;
		default:
			{
				sendCannotUse(pPacket, pPlayer);
				return;
			}
	}

	GCUseOK gcUseOK;
	pPlayer->sendPacket(&gcUseOK);

	if (isStackable(pItem))
	{
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
	}
	else 
	{
		// 쌓이지 않는 아이템은 바로바로 삭제해준다.
		pInventory->deleteItem(InvenX, InvenY);
		pItem->destroy();
		SAFE_DELETE(pItem);
	}

	if (bInitAllStat )
	{
	//	initAllStatAndSendChange(pPC);
		pPC->setFlag(Effect::EFFECT_CLASS_INIT_ALL_STAT);
		transportCreature(pPC, pPC->getZoneID(), pPC->getX(), pPC->getY(), false);
	}
	else if (bRefresh )
	{
		GCDeleteObject gcDeleteObject;
		gcDeleteObject.setObjectID(pPC->getObjectID());
		pZone->broadcastPacket(pPC->getX(), pPC->getY(), &gcDeleteObject, pPC);

		if (pPC->isSlayer() )
		{
			Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
			Assert(pSlayer != NULL);

			GCAddSlayer gcAddSlayer;
			makeGCAddSlayer(&gcAddSlayer, pSlayer);
			pZone->broadcastPacket(pPC->getX(), pPC->getY(), &gcAddSlayer, pPC);
		}
		else if (pPC->isVampire() )
		{
			Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
			Assert(pVampire != NULL);

			GCAddVampire gcAddVampire;
			makeGCAddVampire(&gcAddVampire, pVampire);
			pZone->broadcastPacket(pPC->getX(), pPC->getY(), &gcAddVampire, pPC);
		}
		else if (pPC->isOusters() )
		{
			Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
			Assert(pOusters != NULL);

			GCAddOusters gcAddOusters;
			makeGCAddOusters(&gcAddOusters, pOusters);
			pZone->broadcastPacket(pPC->getX(), pPC->getY(), &gcAddOusters, pPC);
		}
		else
		{
			Assert(false);
		}
	}

	return;

#endif

    __END_DEBUG_EX __END_CATCH
}

#ifdef __GAME_SERVER__

bool changeHairColorEx(PlayerCreature* pPC, Color_t color )
{
	if (pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		Assert(pSlayer != NULL);

		if (pSlayer->getHairColor() == color ) return false;

		pSlayer->setHairColor(color);
		
		char query[25];
		sprintf(query, "HairColor=%u", color);

		pSlayer->tinysave(query);

		return true;
	}
	else if (pPC->isOusters() )
	{
		Ousters* pOusters = dynamic_cast<Ousters*>(pPC);
		Assert(pOusters != NULL);

		if (pOusters->getHairColor() == color ) return false;

		pOusters->setHairColor(color);
		
		char query[25];
		sprintf(query, "HairColor=%u", color);

		pOusters->tinysave(query);

		return true;
	}

	return false;
}

bool changeBatColorEx(PlayerCreature* pPC, Color_t color )
{
	if (pPC->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		Assert(pVampire != NULL);

		if (pVampire->getBatColor() == color ) return false;
		if (pVampire->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT) ) return false;

		pVampire->setBatColor(color);
		
		char query[25];
		sprintf(query, "BatColor=%u", color);

		pVampire->tinysave(query);

		return true;
	}

	return false;
}

bool changeMasterEffectColorEx(PlayerCreature* pPC, BYTE color )
{
	if (pPC->getLevel()>=100 || pPC->isAdvanced() )
	{
		if (!pPC->canChangeMasterEffectColor() )
			return false;

		if (pPC->getMasterEffectColor() == color ) return false;

		pPC->setMasterEffectColor(color);
		
		char query[25];
		sprintf(query, "MasterEffectColor=%u", color);

		pPC->tinysave(query);

		return true;
	}

	return false;
}

bool changeAdvancementEffectColorEx(PlayerCreature* pPC, BYTE color )
{
	if (pPC->isAdvanced() )
	{
		if (!pPC->canChangeMasterEffectColor() )
			return false;

		if (pPC->getMasterEffectColor() == color ) return false;

		pPC->setMasterEffectColor(color);
		
		char query[25];
		sprintf(query, "MasterEffectColor=%u", color);

		pPC->tinysave(query);

		return true;
	}

	return false;
}

bool changeSkinColorEx(PlayerCreature* pPC, Color_t color )
{
	if (pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		Assert(pSlayer != NULL);

		if (pSlayer->getSkinColor() == color ) return false;

		pSlayer->setSkinColor(color);

		char query[25];
		sprintf(query, "SkinColor=%u", color);

		pSlayer->tinysave(query);

		return true;
	}
	else if (pPC->isVampire() )
	{
		Vampire* pVampire = dynamic_cast<Vampire*>(pPC);
		Assert(pVampire != NULL);

		if (pVampire->getSkinColor() == color ) return false;

		pVampire->setSkinColor(color);

		char query[25];
		sprintf(query, "SkinColor=%u", color);

		pVampire->tinysave(query);

		return true;
	}

	return false;
}

bool sendCannotUse(CGUseItemFromInventory* pPacket, Player* pPlayer )
{
	GCCannotUse _GCCannotUse;
	_GCCannotUse.setObjectID(pPacket->getObjectID());
	pPlayer->sendPacket(&_GCCannotUse);

	return true;
}

#endif

void CGUseItemFromInventoryHandler::executeResurrectItem(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	ResurrectItemInfo*	pItemInfo	 = dynamic_cast<ResurrectItemInfo*>(g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType() ));

	//cout << "Resurrection 아이템을 사용함 : " << pPC->getName() << " : " << pItem->getItemType() << endl;

	if (pItem->getObjectID() != pPacket->getObjectID() ||
		pItemInfo == NULL )
	{
		//cout << "아템 오브젝트 아디가 틀림" << endl;
		sendCannotUse(pPacket, pPlayer);
		return;
	}

	if (!pPC->isFlag(Effect::EFFECT_CLASS_COMA) )
	{
		//cout << "죽은 상태가 아님" << endl;
		sendCannotUse(pPacket, pPlayer);
		return;
	}

	Slayer* pSlayer = NULL;
	Vampire* pVampire = NULL;
	Ousters* pOusters = NULL;

	if (pPC->isSlayer() ) pSlayer = dynamic_cast<Slayer*>(pPC);
	else if (pPC->isVampire() ) pVampire = dynamic_cast<Vampire*>(pPC);
	else if (pPC->isOusters() ) pOusters = dynamic_cast<Ousters*>(pPC);

	ResurrectItemInfo::ResurrectType type = pItemInfo->getResurrectType();
	HP_t hp = 0;
	GCModifyInformation gcMI;
	GCRemoveEffect gcRemoveEffect;
	gcRemoveEffect.setObjectID(pPC->getObjectID());

	switch (type )
	{
		case ResurrectItemInfo::HP_1:
			{
				if (pPC->isSlayer() )
				{
					Assert(pSlayer != NULL);
					pSlayer->setHP(1);
					hp = 1;
					gcMI.addShortData(MODIFY_CURRENT_HP,hp);
				}
				else if (pPC->isVampire() )
				{
					Assert(pVampire != NULL);
					pVampire->setHP(1);
					hp = 1;
					gcMI.addShortData(MODIFY_CURRENT_HP,hp);
				}
				else if (pPC->isOusters() )
				{
					Assert(pOusters != NULL);
					pOusters->setHP(1);
					hp = 1;
					gcMI.addShortData(MODIFY_CURRENT_HP,hp);
				}
				else
				{
					sendCannotUse(pPacket, pPlayer);
					return;
				}

				if (GDRLairManager::Instance().isGDRLairZone(pPC->getZoneID()) )
				{
					filelog("GDRLair.log", "%s가 %d존에서 부활 스크롤을 사용했습니다.",
							pPC->getName().c_str(),
							pPC->getZoneID());
				}
			}
			break;
		case ResurrectItemInfo::HP_FULL:
			{
				if (pPC->isSlayer() )
				{
					Assert(pSlayer != NULL);
					pSlayer->setHP(pSlayer->getHP(ATTR_MAX));
					hp = pSlayer->getHP();

					gcMI.addShortData(MODIFY_CURRENT_HP,hp);

					if (pSlayer->getMP() < pSlayer->getMP(ATTR_MAX) )
					{
						pSlayer->setMP(pSlayer->getMP(ATTR_MAX));
						gcMI.addShortData(MODIFY_CURRENT_MP,pSlayer->getMP());
					}

					Effect* pEffect = pSlayer->getEffectManager()->findEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);
					if (pEffect != NULL )
					{
						pEffect->destroy(pSlayer->getName());
						pSlayer->getEffectManager()->deleteEffect(pSlayer, Effect::EFFECT_CLASS_BLOOD_DRAIN);

						gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_BLOOD_DRAIN);

						// 흡혈 아르바이트를 방지하기 위한 후유증 이펙트를 붙여준다.
						if (pSlayer->isFlag(Effect::EFFECT_CLASS_AFTERMATH))
						{
							Effect* pEffect = pSlayer->getEffectManager()->findEffect(Effect::EFFECT_CLASS_AFTERMATH);
							EffectAftermath* pEffectAftermath = dynamic_cast<EffectAftermath*>(pEffect);
							pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
						}
						else
						{
							EffectAftermath* pEffectAftermath = new EffectAftermath(pSlayer);
							pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
							pSlayer->getEffectManager()->addEffect(pEffectAftermath);
							pSlayer->setFlag(Effect::EFFECT_CLASS_AFTERMATH);
							pEffectAftermath->create(pSlayer->getName());
						}

						// 흡혈을 치료하면 능력치가 변화하게 된다.
						SLAYER_RECORD prev;
						pSlayer->getSlayerRecord(prev);
						pSlayer->initAllStat();
						pSlayer->addModifyInfo(prev, gcMI);
						pSlayer->sendRealWearingInfo();
					}
				}
				else if (pPC->isVampire() )
				{
					Assert(pVampire != NULL);
					pVampire->setSilverDamage(0);
					pVampire->setHP(pVampire->getHP(ATTR_MAX));
					hp = pVampire->getHP();
					gcMI.addShortData(MODIFY_CURRENT_HP,hp);
					gcMI.addShortData(MODIFY_SILVER_DAMAGE,0);
				}
				else if (pPC->isOusters() )
				{
					Assert(pOusters != NULL);
					pOusters->setSilverDamage(0);
					pOusters->setHP(pOusters->getHP(ATTR_MAX));
					hp = pOusters->getHP();
					gcMI.addShortData(MODIFY_CURRENT_HP,hp);
				}
				else
				{
					sendCannotUse(pPacket, pPlayer);
					return;
				}

				if (GDRLairManager::Instance().isGDRLairZone(pPC->getZoneID()) )
				{
					filelog("GDRLair.log", "%s가 %d존에서 엘릭서 스크롤을 사용했습니다.",
							pPC->getName().c_str(),
							pPC->getZoneID());
				}
			}
			break;

		default:
			sendCannotUse(pPacket, pPlayer);
			return;
	}

	pPC->deleteEffect(Effect::EFFECT_CLASS_COMA);
	pPC->removeFlag(Effect::EFFECT_CLASS_COMA);
	
	gcRemoveEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_COMA);
	pZone->broadcastPacket(pPC->getX(), pPC->getY(), &gcRemoveEffect);

	pPC->getEffectManager()->sendEffectInfo(pPC, pZone, pPC->getX(), pPC->getY());

	GCStatusCurrentHP gcHP;
	gcHP.setObjectID(pPC->getObjectID());
	gcHP.setCurrentHP(hp);
	pZone->broadcastPacket(pPC->getX(), pPC->getY(), &gcHP, pPC);

	pPlayer->sendPacket(&gcMI);

	GCUseOK gcUseOK;
	pPlayer->sendPacket(&gcUseOK);

	if (isStackable(pItem))
	{
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
	}
	else 
	{
		// 쌓이지 않는 아이템은 바로바로 삭제해준다.
		pInventory->deleteItem(InvenX, InvenY);
		pItem->destroy();
		SAFE_DELETE(pItem);
	}

#endif

    __END_DEBUG_EX __END_CATCH
}


void CGUseItemFromInventoryHandler::executeTranslator(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	ItemInfo*		pItemInfo	 = g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType());
	
	if (pItem->getObjectID() != pPacket->getObjectID() ||
		pItemInfo == NULL ||
		pPC->isFlag(Effect::EFFECT_CLASS_TRANSLATION ) )
	{
		//cout << "아템 오브젝트 아디가 틀림" << endl;
		sendCannotUse(pPacket, pPlayer);
		return;
	}

	EffectTranslation* pEffect = new EffectTranslation(pPC);
	Assert(pEffect != NULL);

	pEffect->setDeadline(6000);	// 10분
	pPC->addEffect(pEffect);
	pPC->setFlag(Effect::EFFECT_CLASS_TRANSLATION);

	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID(pPC->getObjectID());
	gcAddEffect.setEffectID(pEffect->getSendEffectClass());
	gcAddEffect.setDuration(6000);
	pZone->broadcastPacket(pPC->getX(), pPC->getY(), &gcAddEffect);

	GCUseOK gcUseOK;
	pPlayer->sendPacket(&gcUseOK);

	if (isStackable(pItem))
	{
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
	}
	else 
	{
		// 쌓이지 않는 아이템은 바로바로 삭제해준다.
		pInventory->deleteItem(InvenX, InvenY);
		pItem->destroy();
		SAFE_DELETE(pItem);
	}

#endif

    __END_DEBUG_EX __END_CATCH
}

void CGUseItemFromInventoryHandler::executeEffectItem(CGUseItemFromInventory* pPacket, Player* pPlayer) throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	EffectItemInfo*	pItemInfo	 = dynamic_cast<EffectItemInfo*>(g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType() ));

	if (pItem->getObjectID() != pPacket->getObjectID() || pItemInfo == NULL ||
		pPC->isFlag(pItemInfo->getEffectClass() )
	)
	{
		sendCannotUse(pPacket, pPlayer);
		return;
	}

	SimpleCreatureEffect* pEffect = new SimpleCreatureEffect(pItemInfo->getEffectClass(), pPC);
	Assert(pEffect != NULL);

	pEffect->setDeadline((WORD)pItemInfo->getDuration()*10);
	pPC->addEffect(pEffect);
	pPC->setFlag(pEffect->getEffectClass());

	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID(pPC->getObjectID());
	gcAddEffect.setEffectID(pEffect->getSendEffectClass());
	gcAddEffect.setDuration((WORD)pItemInfo->getDuration()*10);
	pZone->broadcastPacket(pPC->getX(), pPC->getY(), &gcAddEffect);

	GCUseOK gcUseOK;
	pPlayer->sendPacket(&gcUseOK);

	if (isStackable(pItem))
	{
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
	}
	else 
	{
		// 쌓이지 않는 아이템은 바로바로 삭제해준다.
		pInventory->deleteItem(InvenX, InvenY);
		pItem->destroy();
		SAFE_DELETE(pItem);
	}
	
#endif

	__END_DEBUG_EX __END_CATCH
}

void CGUseItemFromInventoryHandler::executeForceScroll(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	EffectItemInfo*	pItemInfo	 = dynamic_cast<EffectItemInfo*>(g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType() ));

	if (pItem->getObjectID() != pPacket->getObjectID() || pItemInfo == NULL ||
		pPC->isFlag(pItemInfo->getEffectClass() )
	)
	{
		sendCannotUse(pPacket, pPlayer);
		return;
	}

	Effect* pEffect = NULL;

	switch (pItem->getItemType() )
	{
		case 7:
			pEffect = new EffectBehemothForceScroll(pPC);
			break;
		case 8:
			pEffect = new EffectSafeForceScroll(pPC);
			break;
		case 9:
			pEffect = new EffectCarnelianForceScroll(pPC);
			break;
		default:
			sendCannotUse(pPacket, pPlayer);
			return;
	}

	Assert(pEffect != NULL);

	pEffect->setDeadline((WORD)pItemInfo->getDuration()*10);
	pPC->addEffect(pEffect);
	pPC->setFlag(pEffect->getEffectClass());

	// 옵션 적용
	pEffect->affect();
	pEffect->create(pPC->getName());

	GCAddEffect gcAddEffect;
	gcAddEffect.setObjectID(pPC->getObjectID());
	gcAddEffect.setEffectID(pEffect->getSendEffectClass());
	gcAddEffect.setDuration((WORD)pItemInfo->getDuration()*10);
	pZone->broadcastPacket(pPC->getX(), pPC->getY(), &gcAddEffect);

	GCUseOK gcUseOK;
	pPlayer->sendPacket(&gcUseOK);

	if (isStackable(pItem))
	{
		decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);
	}
	else 
	{
		// 쌓이지 않는 아이템은 바로바로 삭제해준다.
		pInventory->deleteItem(InvenX, InvenY);
		pItem->destroy();
		SAFE_DELETE(pItem);
	}
	
#endif

	__END_DEBUG_EX __END_CATCH
}

void CGUseItemFromInventoryHandler::executePetItem(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Zone*			pZone		 = pPC->getZone();
	Inventory*      pInventory   = pPC->getInventory();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();

	SubInventory* pInventoryItem = NULL;
	int invenID = 0;

	if (pPacket->getInventoryItemObjectID() != 0 )
	{
	//	cout << "서브 인벤토리에 넣기 : " << pPacket->getInventoryItemObjectID() << endl;
		CoordInven_t X, Y;
		pInventoryItem = dynamic_cast<SubInventory*>(pInventory->findItemOID(pPacket->getInventoryItemObjectID(), X, Y ));

		TradeManager* pTradeManager = pZone->getTradeManager();
		Assert(pTradeManager != NULL);

		if (pInventoryItem == NULL || pTradeManager->hasTradeInfo(pPC->getName()) )
		{
	//		cout << "근데 서브 인벤토리가 없다." <<endl;
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotUse);
			return;
		}

		pInventory = pInventoryItem->getInventory();
		invenID = pInventoryItem->getItemID();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);

	if (pPC == NULL )
	{
		sendCannotUse(pPacket, pPlayer);
		return;
	}

	if (pPC != NULL && pPC->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pPC);
		if (pSlayer->hasRideMotorcycle() )
		{
			sendCannotUse(pPacket, pPlayer);
			return;
		}
	}

	if (pPC != NULL &&
		(pPC->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT ) || pPC->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF )
		 || pPC->isFlag(Effect::EFFECT_CLASS_SUMMON_SYLPH ))
	)
	{
		sendCannotUse(pPacket, pPlayer);
		return;
	}

	PetItem* pPetItem = dynamic_cast<PetItem*>(pItem);
	if (pPetItem != NULL )
	{
		PetInfo* pTargetPetInfo = pPetItem->getPetInfo();
		if (pTargetPetInfo->getPetHP() == 0 )
		{
//			cout << pPC->getName() << " 죽은 펫 부르지 마셈" << endl;
			sendCannotUse(pPacket, pPlayer);
			return;
		}

		if (pTargetPetInfo->getPetType() >= PET_CENTAURO && pPC->getQuestLevel() < 40 )
		{
			filelog("Pet.log", "레벨 안되는 넘이 2차펫 부를라고 그런다 : [%s:%s]", pGamePlayer->getID().c_str(), pPC->getName().c_str());
			sendCannotUse(pPacket, pPlayer);
			return;
		}

		PetInfo* pPetInfo = pPC->getPetInfo();
		if (pPetInfo == NULL || pPetInfo->getPetItem() != pPetItem )
		{
			pPC->setPetInfo(pTargetPetInfo);
			//cout << pPetItem->getObjectID() << " 아이템의 펫을 불렀습니다." << endl;
		}
		else
		{
			//cout << "펫을 지웠습니다." << endl;
			pPC->setPetInfo(NULL);
		}

		pPC->initAllStatAndSend();
		sendPetInfo(pGamePlayer, true, true);
		GCUseOK gcUseOK;
		pGamePlayer->sendPacket(&gcUseOK);
	}
#endif

	__END_CATCH
}
	
void CGUseItemFromInventoryHandler::executePetFood(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY

#ifdef __GAME_SERVER__
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Zone*			pZone		 = pPC->getZone();
	Inventory*      pInventory   = pPC->getInventory();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();

	SubInventory* pInventoryItem = NULL;
	int invenID = 0;

	if (pPacket->getInventoryItemObjectID() != 0 )
	{
	//	cout << "서브 인벤토리에 넣기 : " << pPacket->getInventoryItemObjectID() << endl;
		CoordInven_t X, Y;
		pInventoryItem = dynamic_cast<SubInventory*>(pInventory->findItemOID(pPacket->getInventoryItemObjectID(), X, Y ));

		TradeManager* pTradeManager = pZone->getTradeManager();
		Assert(pTradeManager != NULL);

		if (pInventoryItem == NULL || pTradeManager->hasTradeInfo(pPC->getName()) )
		{
	//		cout << "근데 서브 인벤토리가 없다." <<endl;
			GCCannotUse _GCCannotUse;
			_GCCannotUse.setObjectID(pPacket->getObjectID());
			pPlayer->sendPacket(&_GCCannotUse);
			return;
		}

		pInventory = pInventoryItem->getInventory();
		invenID = pInventoryItem->getItemID();
	}

	Item*           pItem        = pInventory->getItem(InvenX, InvenY);

	PetFood* pPetFood = dynamic_cast<PetFood*>(pItem);
	PetFoodInfo* pInfo = dynamic_cast<PetFoodInfo*>(g_pItemInfoManager->getItemInfo(pPetFood->getItemClass(), pPetFood->getItemType() ));

	if (pPetFood != NULL && pInfo != NULL )
	{
		PetInfo* pPetInfo = pPC->getPetInfo();
		if (pPetInfo == NULL || pPetInfo->getPetHP() == 0 )
		{
			sendCannotUse(pPacket, pPlayer);
			return;
		}

		PetTypeInfo* pPetTypeInfo = PetTypeInfoManager::getInstance()->getPetTypeInfo(pPetInfo->getPetType());

		if (pPetTypeInfo == NULL || pPetTypeInfo->getFoodType() != pInfo->getTarget() )
		{
			sendCannotUse(pPacket, pPlayer);
			return;
		}
		else
		{
			pPetInfo->setPetHP(pInfo->getPetHP());
			pPetInfo->setFoodType(pPetFood->getItemType());

			decreaseItemNum(pItem, pInventory, pCreature->getName(), STORAGE_INVENTORY, invenID, InvenX, InvenY);

//			pInventory->deleteItem(pPetFood->getObjectID());
//			pPetFood->destroy();
			
//			SAFE_DELETE(pPetFood);

//			GCModifyInformation gcMI;
//			gcMI.addShortData(MODIFY_PET_HP, pPetInfo->getPetHP());
//			pGamePlayer->sendPacket(&gcMI);

			sendPetInfo(pGamePlayer, true);

			GCUseOK gcUseOK;
			pGamePlayer->sendPacket(&gcUseOK);

			char query[100];
			sprintf(query, "PetHP=%u, FoodType=%u", pPetInfo->getPetHP(), pPetInfo->getFoodType());

			Item* pItem = pPetInfo->getPetItem();
			if (pItem != NULL ) pItem->tinysave(query);
		}
	}
#endif

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void CGUseItemFromInventoryHandler::executeEventGiftBox(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
	__BEGIN_TRY __BEGIN_DEBUG_EX

#ifdef __GAME_SERVER__

	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	Zone*           pZone        = pPC->getZone();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);
	//ObjectID_t      ItemObjectID = pItem->getObjectID();
	
	// 검은색 선물 상자가 아니라면 사용할 수 없다 
	if (pItem->getItemType() < 6 || (pItem->getItemType() >= 16 && pItem->getItemType() <= 18 ) )
	{
		filelog("GiftBoxErrorLog.txt", "[Name] : %s , [ItemType] : %d : 잘못된 아이템 타입\n", pCreature->getName().c_str(), pItem->getItemType());
		return;
	}

	// DEBUG
	//cout << "Name : " << pCreature->getName() << " , GiftBoxType : " << pItem->getItemType() << endl;

	if (pItem->getItemType() >= 22 && pItem->getItemType() <= 26 )
	{
		sendCannotUse(pPacket, pPlayer);
		return;

/*		if (pCreature->isFlag(Effect::EFFECT_CLASS_CAN_MODIFY_NICKNAME_0 ) )
		{
			sendCannotUse(pPacket, pPlayer);
			return;
		}
		else
		{
			pCreature->setFlag(Effect::EFFECT_CLASS_CAN_MODIFY_NICKNAME_0);

			GCUseOK gcUseOK;
			pGamePlayer->sendPacket(&gcUseOK);

			pInventory->deleteItem(InvenX, InvenY);
			pItem->destroy();
			SAFE_DELETE(pItem);
			return;
		}*/
	}

/*	if (pItem->getItemType() == 23 )
	{
		if (pCreature->isFlag(Effect::EFFECT_CLASS_CAN_MODIFY_PET_NICKNAME ) )
		{
			sendCannotUse(pPacket, pPlayer);
			return;
		}
		else
		{
			pCreature->setFlag(Effect::EFFECT_CLASS_CAN_MODIFY_PET_NICKNAME);

			GCUseOK gcUseOK;
			pGamePlayer->sendPacket(&gcUseOK);

			pInventory->deleteItem(InvenX, InvenY);
			pItem->destroy();
			SAFE_DELETE(pItem);
			return;
		}
	}
*/
	// 검은상자가 변하는 아이템이 2*2 에 다 들어가는 크기이므로 Inventory 검사는 생략
	// (만약 검은 상자 지우고 나서 안 들어가는 상황 발생하면 곤란하므로)
	Item*	pResultItem	= NULL;
	bool	bFullStack = true;

	if (pItem->getItemType() == 6 )
	{
		if (pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(113, 122);
		}
		else if (pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(123, 132);
		}
		else if (pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(133, 142);
		}
	}
	else if (pItem->getItemType() == 7 )
	{
		if (pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(143, 152);
		}
		else if (pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(153, 162);
		}
		else if (pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(163, 172);
		}
	}
	else if (pItem->getItemType() == 8 )
	{
		if (pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(173, 182);
		}
		else if (pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(183, 192);
		}
		else if (pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(193, 202);
		}
	}
	else if (pItem->getItemType() == 9 )
	{
		if (pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(203, 212);
		}
		else if (pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(213, 222);
		}
		else if (pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(223, 232);
		}
	}
	else if (pItem->getItemType() == 10 )
	{
		if (pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(233, 242);
		}
		else if (pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(243, 252);
		}
		else if (pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(253, 262);
		}
	}
	else if (pItem->getItemType() == 11 )
	{
		if (pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(263, 272);
		}
		else if (pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(273, 282);
		}
		else if (pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(283, 292);
		}
	}
	else if (pItem->getItemType() == 12 )
	{
		if (pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(293, 302);
		}
		else if (pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(303, 312);
		}
		else if (pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(313, 322);
		}
	}
	else if (pItem->getItemType() == 13 )
	{
		if (pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(323, 332);
		}
		else if (pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(333, 342);
		}
		else if (pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(343, 352);
		}
	}
	else if (pItem->getItemType() == 14 )
	{
		if (pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(353, 362);
		}
		else if (pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(363, 372);
		}
		else if (pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(373, 382);
		}
	}
	else if (pItem->getItemType() == 15 )
	{
		if (pCreature->isSlayer() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(383, 392);
		}
		else if (pCreature->isVampire() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(393, 402);
		}
		else if (pCreature->isOusters() )
		{
			pResultItem = g_pItemMineInfoManager->getRandomItem(403, 412);
		}
	}
	else if (pItem->getItemType() == 19 )
	{
		int value = rand()%100;
		bFullStack = false;

		if (value < 70 )
		{
			// 엘릭서 스크롤
			pResultItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_RESURRECT_ITEM, 1, list<OptionType_t>());
		}
		else if (value < 95 )
		{
			// 빨간 떡국
			pResultItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_STAR, 8, list<OptionType_t>());
		}
		else if (value < 99 )
		{
			// 엘릭서 스크롤 묶음
			pResultItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_RESURRECT_ITEM, 1, list<OptionType_t>());
			pResultItem->setNum(9);
		}
		else
		{
			// 악세사리 믹싱포지 A형
			pResultItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_MIXING_ITEM, 6, list<OptionType_t>());
		}
	}
	else if (pItem->getItemType() == 20 )
	{
		int value = rand()%100;
		bFullStack = false;

		if (value < 70 )
		{
			// 부활 스크롤
			pResultItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_RESURRECT_ITEM, 0, list<OptionType_t>());
		}
		else if (value < 95 )
		{
			// 파란 떡국
			pResultItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_STAR, 10, list<OptionType_t>());
		}
		else if (value < 99 )
		{
			// 블루버드 50개
			pResultItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_STAR, 12, list<OptionType_t>());
			pResultItem->setNum(50);
		}
		else
		{
			// 아머 믹싱포지 A형
			pResultItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_MIXING_ITEM, 3, list<OptionType_t>());
		}
	}

	else if (pItem->getItemType() == 21 )
	{
		int value = rand()%100;
		bFullStack = false;

		if (value < 70 )
		{
			// 부활 스크롤
			pResultItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_RESURRECT_ITEM, 0, list<OptionType_t>());
		}
		else if (value < 95 )
		{
			// 녹색 떡국
			pResultItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_STAR, 9, list<OptionType_t>());
		}
		else if (value < 99 )
		{
			// 알림판 3
			pResultItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_EVENT_TREE, 28, list<OptionType_t>());
		}
		else
		{
			// 푸더 4개
			pResultItem = g_pItemFactoryManager->createItem(Item::ITEM_CLASS_PET_FOOD, 4, list<OptionType_t>());
			pResultItem->setNum(4);
		}
	}

	if (pResultItem == NULL )
	{
		filelog("GiftBoxErrorLog.txt", "[Name] : %s : 줄 수 있는 아이템이 없다\n", pCreature->getName().c_str());
		return;
	}

	// 쌓일 수 있는 아이템이면 꽉 채워준다
	if (pResultItem->isStackable() && bFullStack )
	{
		int MaxStack = ItemMaxStack[pResultItem->getItemClass()];
		pResultItem->setNum(MaxStack);
	}

	bool isChargingItem = false;
	int chargeNum = 0;
	// Charging 아이템도 꽉 채워준다
	if (pResultItem->getItemClass() == Item::ITEM_CLASS_SLAYER_PORTAL_ITEM ) 
	{
		SlayerPortalItem* pSlayerPortalItem = dynamic_cast<SlayerPortalItem*>(pResultItem);
		pSlayerPortalItem->setCharge(pSlayerPortalItem->getMaxCharge());
		isChargingItem = true;
		chargeNum = pSlayerPortalItem->getMaxCharge();
	}
	else if (pResultItem->getItemClass() == Item::ITEM_CLASS_VAMPIRE_PORTAL_ITEM )
	{
		VampirePortalItem* pVampirePortalItem = dynamic_cast<VampirePortalItem*>(pResultItem);
		pVampirePortalItem->setCharge(pVampirePortalItem->getMaxCharge());
		isChargingItem = true;
		chargeNum = pVampirePortalItem->getMaxCharge();
	}
	else if (pResultItem->getItemClass() == Item::ITEM_CLASS_OUSTERS_SUMMON_ITEM )
	{
		OustersSummonItem* pOustersSummonItem = dynamic_cast<OustersSummonItem*>(pResultItem);
		pOustersSummonItem->setCharge(pOustersSummonItem->getMaxCharge());
		isChargingItem = true;
		chargeNum = pOustersSummonItem->getMaxCharge();
	}

	pZone->registerObject(pResultItem);

	GCUseOK gcUseOK;
	pGamePlayer->sendPacket(&gcUseOK);
	// 검은색 선물 상자를 지우고 그 자리에 아이템을 넣는다
	pInventory->deleteItem(InvenX, InvenY);
	pItem->destroy();
	SAFE_DELETE(pItem);

	// inventory에 넣는다.
	if(pInventory->addItem(InvenX, InvenY, pResultItem))
	{
		pResultItem->create(pPC->getName(), STORAGE_INVENTORY, 0, InvenX, InvenY);

		GCCreateItem gcCreateItem;
/*		gcCreateItem.setObjectID(pResultItem->getObjectID());
		gcCreateItem.setItemClass(pResultItem->getItemClass());
		gcCreateItem.setItemType(pResultItem->getItemType());
		gcCreateItem.setOptionType(pResultItem->getOptionTypeList());
		gcCreateItem.setDurability(pResultItem->getDurability());
		gcCreateItem.setItemNum(pResultItem->getNum());

		if (isChargingItem )
			gcCreateItem.setEnchantLevel(chargeNum);

		gcCreateItem.setInvenX(InvenX);
		gcCreateItem.setInvenY(InvenY);*/
		makeGCCreateItem(&gcCreateItem, pResultItem, InvenX, InvenY);

		pGamePlayer->sendPacket(&gcCreateItem);

		// ItemTraceLog 를 남긴다
		if (pResultItem != NULL && pResultItem->isTraceItem() )
		{
			remainTraceLog(pResultItem, "BLACK BOX", pCreature->getName(), ITEM_LOG_CREATE, DETAIL_EVENTNPC);
		}

	}
	else
	{
		filelog("GiftBoxErrorLog.txt", "[Name] : %s : 인벤토리에 아이템을 넣을 수 없다. Item : %s\n", pCreature->getName().c_str(), pResultItem->toString().c_str());
		return;
	}



#endif

    __END_DEBUG_EX __END_CATCH
}

void CGUseItemFromInventoryHandler::executeTrapItem(CGUseItemFromInventory* pPacket, Player* pPlayer)
	throw(ProtocolException, Error)
{
#ifdef __GAME_SERVER__
	Assert(pPacket != NULL);
	Assert(pPlayer != NULL);

	// 상위 함수에서 에러 체크를 많이 했기 때문에,
	// 에러 체크를 대폭 축소한다.
	GamePlayer*     pGamePlayer  = dynamic_cast<GamePlayer*>(pPlayer);
	Creature*       pCreature    = pGamePlayer->getCreature();
	PlayerCreature* pPC          = dynamic_cast<PlayerCreature*>(pCreature);
	Inventory*      pInventory   = pPC->getInventory();
	CoordInven_t    InvenX       = pPacket->getX();
	CoordInven_t    InvenY       = pPacket->getY();
	Item*           pItem        = pInventory->getItem(InvenX, InvenY);

	TrapItem*		pTrapItem	= dynamic_cast<TrapItem*>(pItem);
	TrapItemInfo*	pInfo		= dynamic_cast<TrapItemInfo*>(g_pItemInfoManager->getItemInfo(pItem->getItemClass(), pItem->getItemType() ));

	if (!SiegeManager::Instance().isSiegeZone(pPC->getZoneID()) )
	{
		GCCannotUse _GCCannotUse;
		_GCCannotUse.setObjectID(pPacket->getObjectID());
		pGamePlayer->sendPacket(&_GCCannotUse);
		return;
	}

	if (pTrapItem != NULL && pInfo != NULL )
	{
		if (pTrapItem->getItemType() <= 3 )
		{
			// 트랩
			if (
					(pCreature->getX() < 97 || pCreature->getX() > 121 )
				||	(pCreature->getY() < 135 || pCreature->getY() > 170 )
			   )
			{
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
				return;
			}
		}
		else
		{
			// 장애물
			if (
					(pCreature->getX() < 132 || pCreature->getX() > 152 )
				||	(pCreature->getY() < 105 || pCreature->getY() > 135 )
			   )
			{
				GCCannotUse _GCCannotUse;
				_GCCannotUse.setObjectID(pPacket->getObjectID());
				pGamePlayer->sendPacket(&_GCCannotUse);
				return;
			}
		}

		switch (pInfo->getFunction() )
		{
			case TrapItemInfo::SUMMON_MONSTER :
			case TrapItemInfo::SUMMON_TRAP :
				{
					Monster* pMonster = new Monster(pInfo->getParameter());
					pCreature->getZone()->addCreature(pMonster, pCreature->getX(), pCreature->getY(), 2);
					if (pInfo->getFunction() == TrapItemInfo::SUMMON_TRAP )
						addSimpleCreatureEffect(pMonster, Effect::EFFECT_CLASS_HIDE_TO_ATTACKER);
				}
				break;
			case TrapItemInfo::MAKE_EFFECT :
				{
					Zone* pZone = pPC->getZone();

					ZoneCoord_t sx = pPC->getX();
					ZoneCoord_t sy = pPC->getY();

					Monster* pMonster = new Monster(pInfo->getParameter());
					pMonster->setBrain(NULL);
					EffectKillTimer* pTimer = new EffectKillTimer(pMonster);
					pTimer->setDeadline(65000);
					pMonster->setFlag(Effect::EFFECT_CLASS_NO_DAMAGE);
					pMonster->addEffect(pTimer);

					pCreature->getZone()->addCreature(pMonster, sx, sy, 2);
					addSimpleCreatureEffect(pMonster, Effect::EFFECT_CLASS_HIDE_TO_ATTACKER);
					sx = pMonster->getX();
					sy = pMonster->getY();

					GCAddEffectToTile gcAE;
					gcAE.setDuration(65000);
					gcAE.setXY(sx, sy);

					for (int i=1; i<=7; ++i )
					{
						ZoneCoord_t tx = sx+i;
						ZoneCoord_t ty = sy+i;
						if (!isValidZoneCoord(pZone, tx, ty ) ) continue;
						if (!pZone->getTile(tx, ty).canAddEffect() ) continue;

						EffectTurretLaser* pTurretLaser = new EffectTurretLaser(pZone, tx, ty);
						pTurretLaser->setDeadline(65000);
						pTurretLaser->setNextTime(0);
						pZone->registerObject(pTurretLaser);
						pZone->addEffect(pTurretLaser);
						pZone->getTile(tx, ty).addEffect(pTurretLaser);

						gcAE.setEffectID(pTurretLaser->getSendEffectClass());
						gcAE.setObjectID(pTurretLaser->getObjectID());
						gcAE.setXY(tx, ty);
						pZone->broadcastPacket(tx, ty, &gcAE);
					}
				}
				break;
		}

		GCUseOK _GCUseOK;
		pGamePlayer->sendPacket(&_GCUseOK);

		pInventory->deleteItem(InvenX, InvenY);
		pItem->destroy();
		SAFE_DELETE(pItem);
	}

#endif

}
