//////////////////////////////////////////////////////////////////////////////
// Filename    : ShadowWalk.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ShadowWalk.h"
#include "GCSkillToObjectOK1.h"
#include "GCSkillToObjectOK2.h"
#include "GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void ShadowWalk::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NPC는 공격할 수가 없다.
		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		// 무장하고 있는 무기가 널이거나, 도가 아니라면 사용할 수 없다.
		Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if (pItem == NULL || pItem->getItemClass() != Item::ITEM_CLASS_BLADE)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		bool bIncreaseExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		SkillLevel_t      SkillLevel = pSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, pTargetCreature, computeSkillRange(pSkillSlot, pSkillInfo));
		bool bHitRoll    = HitRoll::isSuccess(pSlayer, pTargetCreature, SkillLevel/2);
		bool bCanHit     = canHit(pSlayer, pTargetCreature, SkillType) && canAttack(pSlayer, pTargetCreature);
		bool bPK         = verifyPK(pSlayer, pTargetCreature);
		bool bEffected	 = pSlayer->hasRelicItem() 
							|| pSlayer->isFlag(Effect::EFFECT_CLASS_HAS_FLAG)
							|| pSlayer->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER);

		//if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bCanHit && bPK) // HitRoll 에 실패하더라도 7%의 데미지를 준다
		if (bManaCheck && bTimeCheck && bRangeCheck && bCanHit && bPK && !bEffected)
		{
			// 빠르게 PC를 움직여준다.
			if (pZone->moveFastPC(pSlayer, pSlayer->getX(), pSlayer->getY(), pTargetCreature->getX(), pTargetCreature->getY(), getSkillType()))
			{
				decreaseMana(pSlayer, RequiredMP, _GCSkillToObjectOK1);

				SkillInput input(pSlayer, pSkillSlot);
				SkillOutput output;
				computeOutput(input, output);
				
				bool bCriticalHit = false;

				// 데미지를 준다. (스킬 데미지는 없다.)
				Damage_t Damage = computeDamage(pSlayer, pTargetCreature, SkillLevel/5, bCriticalHit);
				// HitRoll에 실패했다면 7%의 데미지를 준다. - by bezz
				if (!bHitRoll )
					Damage = (Damage_t)getPercentValue(Damage, 7);
				setDamage(pTargetCreature, Damage, pSlayer, SkillType, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
				computeAlignmentChange(pTargetCreature, Damage, pSlayer, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);

//				Exp_t Point = pSkillInfo->getPoint();
				decreaseDurability(pSlayer, pTargetCreature, pSkillInfo, &_GCSkillToObjectOK1, &_GCSkillToObjectOK2);
				// 크리티컬 히트라면 상대방을 뒤로 물러나게 한다.
				if (bCriticalHit)
				{
					knockbackCreature(pZone, pTargetCreature, pSlayer->getX(), pSlayer->getY());
				}

				if (!pTargetCreature->isSlayer())
				{
					if (bIncreaseExp)
					{
						shareAttrExp(pSlayer, Damage, 8, 1, 1, _GCSkillToObjectOK1);
						increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToObjectOK1, pTargetCreature->getLevel());
						increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToObjectOK1);
					}
					increaseAlignment(pSlayer, pTargetCreature, _GCSkillToObjectOK1);
				}

				// 패킷을 준비하고 보낸다.
				_GCSkillToObjectOK1.setSkillType(SkillType);
				_GCSkillToObjectOK1.setCEffectID(CEffectID);
				_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
				_GCSkillToObjectOK1.setDuration(0);

				pPlayer->sendPacket(&_GCSkillToObjectOK1);

				if (pTargetCreature->isPC()) 
				{
					_GCSkillToObjectOK2.setObjectID(pSlayer->getObjectID());
					_GCSkillToObjectOK2.setSkillType(SkillType);
					_GCSkillToObjectOK2.setDuration(0);

					Player* pTargetPlayer = pTargetCreature->getPlayer();
					Assert(pTargetPlayer != NULL);
					pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
				}
				else 
				{
					Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
					pMonster->addEnemy(pSlayer);
				}

				// set Next Run Time
				pSkillSlot->setRunTime(output.Delay);
			}
			else
			{
				executeSkillFailException(pSlayer, getSkillType());
			}

		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

ShadowWalk g_ShadowWalk;


