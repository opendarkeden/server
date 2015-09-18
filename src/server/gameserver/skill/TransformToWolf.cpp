//////////////////////////////////////////////////////////////////////////////
// Filename    : TransformToWolf.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "TransformToWolf.h"
#include "EffectTransformToWolf.h"
#include "ItemUtil.h"
#include "RankBonus.h"
#include "PKZoneInfoManager.h"

#include "CreatureUtil.h"
#include "GamePlayer.h"

#include "GCSkillToSelfOK1.h"
#include "GCSkillToInventoryOK1.h"
#include "GCSkillToSelfOK3.h"
#include "GCDeleteObject.h"
#include "GCAddWolf.h"
#include "GDRLairManager.h"

#include "item/SubInventory.h"
#include "TradeManager.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 인벤토리 핸들러
//////////////////////////////////////////////////////////////////////////////
void TransformToWolf::execute(Vampire* pVampire, ObjectID_t InvenObjectID, ObjectID_t InventoryItemObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, VampireSkillSlot* pSkillSlot)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pVampire != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();
		Inventory* pInventory = pVampire->getInventory();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);
		Assert(pInventory!= NULL);

		SubInventory* pInventoryItem = NULL;
		int invenID = 0;

		if (InventoryItemObjectID != 0 )
		{
			//cout << "서브 인벤토리에서 사용 : " << InventoryItemObjectID << endl;
			CoordInven_t X, Y;
			pInventoryItem = dynamic_cast<SubInventory*>(pInventory->findItemOID(InventoryItemObjectID, X, Y ));

			TradeManager* pTradeManager = pZone->getTradeManager();
			Assert(pTradeManager != NULL);

			if (pInventoryItem == NULL || pTradeManager->hasTradeInfo(pVampire->getName()) )
			{
				//cout << "근데 서브 인벤토리가 없다." <<endl;
				executeSkillFailException(pVampire, getSkillType());
				return;
			}

			pInventory = pInventoryItem->getInventory();
			invenID = pInventoryItem->getItemID();
		}

		Item* pItem = pInventory->getItem(X, Y);
		Assert(pItem != NULL);

		// 적당한 아이템이 아니라면 당연히 변신할 수 없다.
		// PK존에서는 변신할 수 없다.
		if (pItem->getItemClass() != Item::ITEM_CLASS_VAMPIRE_ETC 
			|| pItem->getItemType() != 0
			|| pVampire->hasRelicItem()
			|| g_pPKZoneInfoManager->isPKZone(pZone->getZoneID() )
			|| pVampire->isFlag(Effect::EFFECT_CLASS_REFINIUM_TICKET )
			|| GDRLairManager::Instance().isGDRLairZone(pZone->getZoneID())
		)
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}
		
		GCSkillToInventoryOK1 _GCSkillToInventoryOK1;

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t x = pVampire->getX();
		ZoneCoord_t y = pVampire->getY();

		// Knowledge of Innate 가 있다면 hit bonus 10
		int HitBonus = 0;
		if (pVampire->hasRankBonus(RankBonus::RANK_BONUS_KNOWLEDGE_OF_INNATE ) )
		{
			RankBonus* pRankBonus = pVampire->getRankBonus(RankBonus::RANK_BONUS_KNOWLEDGE_OF_INNATE);
			Assert(pRankBonus != NULL);

			HitBonus = pRankBonus->getPoint();
		}

		int  RequiredMP     = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck     = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck     = verifyRunTime(pSkillSlot);
		bool bRangeCheck    = checkZoneLevelToUseSkill(pVampire);
		bool bHitRoll       = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pSkillSlot, HitBonus);
		bool bMoveModeCheck = pVampire->isWalking();
		bool bEffected      = pVampire->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF)
								|| pVampire->isFlag(Effect::EFFECT_CLASS_HAS_FLAG)
								|| pVampire->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bMoveModeCheck && !bEffected)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToInventoryOK1);

			SkillInput input(pVampire);
			SkillOutput output;
			computeOutput(input, output);

			// 이펙트 클래스를 만들어 붙인다.
			EffectTransformToWolf* pEffectTTW = new EffectTransformToWolf(pVampire);
			pEffectTTW->setDeadline(999999999);
			pVampire->addEffect(pEffectTTW);
			pVampire->setFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF);

			// 이로 인해서 변하는 능력치들을 보내준다.
			VAMPIRE_RECORD prev;
			pVampire->getVampireRecord(prev);
			pVampire->initAllStat();
			pVampire->addModifyInfo(prev, _GCSkillToInventoryOK1);

			_GCSkillToInventoryOK1.setSkillType(SkillType);
			_GCSkillToInventoryOK1.setCEffectID(0);
			_GCSkillToInventoryOK1.setDuration(0);
		
			pPlayer->sendPacket(&_GCSkillToInventoryOK1);

			// 뱀파이어 대신 늑대를 더하라고 알려준다.
			GCAddWolf gcAddWolf;
			gcAddWolf.setObjectID(pVampire->getObjectID());
			gcAddWolf.setName(pVampire->getName());
			gcAddWolf.setXYDir(x, y, pVampire->getDir());
			gcAddWolf.setItemType(pItem->getItemType());
			gcAddWolf.setCurrentHP(pVampire->getHP());
			gcAddWolf.setMaxHP(pVampire->getHP(ATTR_MAX));
			gcAddWolf.setGuildID(pVampire->getGuildID());
			pZone->broadcastPacket(x, y, &gcAddWolf, pVampire);

			decreaseItemNum(pItem, pInventory, pVampire->getName(), STORAGE_INVENTORY, invenID, X, Y);

			if (pVampire->getPetInfo() != NULL )
			{
				pVampire->setPetInfo(NULL);
				sendPetInfo(dynamic_cast<GamePlayer*>(pVampire->getPlayer()), true);
			}

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pVampire, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void TransformToWolf::execute(Monster* pMonster)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pMonster != NULL);

	try 
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);
		
		SkillType_t SkillType  = SKILL_TRANSFORM_TO_WOLF;
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t x = pMonster->getX();
		ZoneCoord_t y = pMonster->getY();

		bool bRangeCheck    = checkZoneLevelToUseSkill(pMonster);
		bool bHitRoll       = HitRoll::isSuccessMagic(pMonster, pSkillInfo);
		bool bMoveModeCheck = pMonster->isWalking();
		bool bEffected      = pMonster->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF);

		if (bRangeCheck && bHitRoll && bMoveModeCheck && !bEffected)
		{
			SkillInput input(pMonster);
			SkillOutput output;
			computeOutput(input, output);

			// 이펙트 클래스를 만들어 붙인다.
			EffectTransformToWolf* pEffectTTW = new EffectTransformToWolf(pMonster);
			pEffectTTW->setDeadline(999999999);
			pMonster->addEffect(pEffectTTW);
			pMonster->setFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF);

			// 이로 인해서 변하는 능력치들을 보내준다.
			pMonster->initAllStat();

			// 뱀파이어 대신 늑대를 더하라고 알려준다.
			GCAddWolf gcAddWolf;
			gcAddWolf.setObjectID(pMonster->getObjectID());
			gcAddWolf.setName(pMonster->getName());
			gcAddWolf.setXYDir(x, y, pMonster->getDir());
			gcAddWolf.setItemType(0);
			gcAddWolf.setCurrentHP(pMonster->getHP());
			gcAddWolf.setMaxHP(pMonster->getHP(ATTR_MAX));
			gcAddWolf.setGuildID(1);
			pZone->broadcastPacket(x, y, &gcAddWolf, pMonster);
		} 
		else 
		{
			executeSkillFailNormal(pMonster, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t) 
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

TransformToWolf g_TransformToWolf;
