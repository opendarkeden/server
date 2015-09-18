//////////////////////////////////////////////////////////////////////////////
// Filename    : TransformToBat.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "TransformToBat.h"
#include "EffectTransformToBat.h"
#include "ZoneUtil.h"
#include "ItemUtil.h"
#include "RankBonus.h"
#include "PKZoneInfoManager.h"

#include "CreatureUtil.h"
#include "GamePlayer.h"

#include "GCSkillToSelfOK1.h"
#include "GCSkillToInventoryOK1.h"
#include "GCSkillToSelfOK3.h"
#include "GCDeleteObject.h"
#include "GCAddBat.h"
#include "GDRLairManager.h"
#include "SiegeManager.h"
#include "GQuestManager.h"
#include "DynamicZone.h"

#include "item/SubInventory.h"
#include "TradeManager.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 인벤토리 핸들러
//////////////////////////////////////////////////////////////////////////////
void TransformToBat::execute(Vampire* pVampire, ObjectID_t InvenObjectID, ObjectID_t InventoryItemObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, VampireSkillSlot* pSkillSlot)
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
		Assert(pInventory != NULL);
		Assert(pZone != NULL);

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
		// 적당한 아이템이 아니라면 당연히 변신할 수 없다.
		// PK존이라면 변신할 수 없다.
		if (pItem == NULL 
			|| pItem->getItemClass() != Item::ITEM_CLASS_VAMPIRE_ETC 
			|| pItem->getItemType() != 1
			|| pVampire->hasRelicItem()
			|| g_pPKZoneInfoManager->isPKZone(pZone->getZoneID() )
			|| pVampire->isFlag(Effect::EFFECT_CLASS_REFINIUM_TICKET )
			|| GDRLairManager::Instance().isGDRLairZone(pZone->getZoneID())
			|| SiegeManager::Instance().isSiegeZone(pZone->getZoneID())
			|| (pZone->isDynamicZone() && pZone->getDynamicZone()->getTemplateZoneID() == 4002 )
			|| pZone->isNoPortalZone()
		)
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		GCSkillToInventoryOK1 _GCSkillToInventoryOK1;

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t x    = pVampire->getX();
		ZoneCoord_t y    = pVampire->getY();
		Tile&       tile = pZone->getTile(x, y);

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
		bool bTileCheck     = (canAddCreature(pZone, x, y, Creature::MOVE_MODE_FLYING) && tile.hasFlyingCreature() == false);
		bool bEffected      = pVampire->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT)
								|| pVampire->isFlag(Effect::EFFECT_CLASS_HAS_FLAG)
								|| pVampire->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bMoveModeCheck && bTileCheck && !bEffected)
		{
			TPOINT pt = findSuitablePosition(pZone, x, y, Creature::MOVE_MODE_FLYING);

			if (pt.x!=-1)	// 들어갈 좌표 체크. by sigi. 2002.5.2
			{
				decreaseMana(pVampire, RequiredMP, _GCSkillToInventoryOK1);

				SkillInput input(pVampire);
				SkillOutput output;
				computeOutput(input, output);

				// 이펙트 클래스를 만들어 붙인다.
				EffectTransformToBat* pEffectTTW = new EffectTransformToBat(pVampire);
				pEffectTTW->setDeadline(99999999);
				pVampire->addEffect(pEffectTTW);
				pVampire->setFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT);

				// 이로 인해서 변하는 능력치들을 보내준다.
				VAMPIRE_RECORD prev;
				pVampire->getVampireRecord(prev);
				pVampire->initAllStat();
				pVampire->addModifyInfo(prev, _GCSkillToInventoryOK1);

				_GCSkillToInventoryOK1.setSkillType(SkillType);
				_GCSkillToInventoryOK1.setCEffectID(0);
				_GCSkillToInventoryOK1.setDuration(0);
			
				pPlayer->sendPacket(&_GCSkillToInventoryOK1);

				// 뱀파이어 대신 박쥐를 더하라고 알려준다.
				GCAddBat gcAddBat;
				gcAddBat.setObjectID(pVampire->getObjectID());
				gcAddBat.setName(pVampire->getName());
				gcAddBat.setXYDir(x, y, pVampire->getDir());
				gcAddBat.setItemType(pItem->getItemType());
				gcAddBat.setCurrentHP(pVampire->getHP());
				gcAddBat.setMaxHP(pVampire->getHP(ATTR_MAX));
				gcAddBat.setGuildID(pVampire->getGuildID());
				gcAddBat.setColor(pVampire->getBatColor());
				pZone->broadcastPacket(x, y, &gcAddBat, pVampire);

				// 타일에다 지웠다, 다시 더함으로서 무브모드를 바꿀 수 잇다.
				tile.deleteCreature(pVampire->getObjectID());

				Tile& newtile = pZone->getTile(pt.x, pt.y);

				pVampire->setMoveMode(Creature::MOVE_MODE_FLYING);
				newtile.addCreature(pVampire);
				pVampire->setXYDir(pt.x, pt.y, pVampire->getDir());

				decreaseItemNum(pItem, pInventory, pVampire->getName(), STORAGE_INVENTORY, invenID, X, Y);

				pSkillSlot->setRunTime(output.Delay);

				if (pVampire->getPetInfo() != NULL )
				{
					pVampire->setPetInfo(NULL);
					sendPetInfo(dynamic_cast<GamePlayer*>(pVampire->getPlayer()), true);
				}

				pVampire->getGQuestManager()->rideMotorcycle();
			}
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
void TransformToBat::execute(Monster* pMonster)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pMonster != NULL);

	try 
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		SkillType_t SkillType  = SKILL_TRANSFORM_TO_BAT;
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t x = pMonster->getX();
		ZoneCoord_t y = pMonster->getY();
		Tile&       tile = pZone->getTile(x, y);

		bool bRangeCheck    = checkZoneLevelToUseSkill(pMonster);
		bool bHitRoll       = HitRoll::isSuccessMagic(pMonster, pSkillInfo);
		bool bMoveModeCheck = pMonster->isWalking();
		bool bTileCheck     = (canAddCreature(pZone, x, y, Creature::MOVE_MODE_FLYING) && tile.hasFlyingCreature() == false);
		bool bEffected      = pMonster->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT);

		if (bRangeCheck && bHitRoll && bMoveModeCheck && bTileCheck && !bEffected)
		{
			SkillInput input(pMonster);
			SkillOutput output;
			computeOutput(input, output);

			// 이펙트 클래스를 만들어 붙인다.
			EffectTransformToBat* pEffectTTW = new EffectTransformToBat(pMonster);
			pEffectTTW->setDeadline(99999999);
			pMonster->addEffect(pEffectTTW);
			pMonster->setFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_BAT);

			// 이로 인해서 변하는 능력치들을 보내준다.
			pMonster->initAllStat();

			// 뱀파이어 대신 박쥐를 더하라고 알려준다.
			GCAddBat gcAddBat;
			gcAddBat.setObjectID(pMonster->getObjectID());
			gcAddBat.setName(pMonster->getName());
			gcAddBat.setXYDir(x, y, pMonster->getDir());
			gcAddBat.setItemType(1);
			gcAddBat.setCurrentHP(pMonster->getHP());
			gcAddBat.setMaxHP(pMonster->getHP(ATTR_MAX));
			gcAddBat.setGuildID(1);
			gcAddBat.setColor(0);
			pZone->broadcastPacket(x, y, &gcAddBat, pMonster);



			// 타일에다 지웠다, 다시 더함으로서 무브모드를 바꿀 수 잇다.
			Tile& tile = pZone->getTile(x, y);
			tile.deleteCreature(pMonster->getObjectID());

			TPOINT pt = findSuitablePosition(pZone, x, y, Creature::MOVE_MODE_FLYING);
			pMonster->setMoveMode(Creature::MOVE_MODE_FLYING);
			Tile& newtile = pZone->getTile(pt.x, pt.y);

			newtile.addCreature(pMonster);
			pMonster->setXYDir(pt.x, pt.y, pMonster->getDir());

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


TransformToBat g_TransformToBat;
