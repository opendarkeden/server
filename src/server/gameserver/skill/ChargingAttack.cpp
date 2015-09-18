//////////////////////////////////////////////////////////////////////////////
// Filename    : ChargingAttack.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "ChargingAttack.h"
#include "GCSkillToObjectOK1.h"
#include "GCSkillToObjectOK2.h"
#include "GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
// 아우스터즈 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void ChargingAttack::execute(Ousters * pOusters, ObjectID_t TargetObjectID, OustersSkillSlot * pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch제거. by sigi. 2002.5.2
		// NPC는 공격할 수가 없다.
		if (pTargetCreature==NULL
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pOusters, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		// 무장하고 있는 무기가 널이거나, 검이 아니라면 기술을 사용할 수 없다.
		Item* pItem = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
		if (pItem == NULL)
		{
			executeSkillFailException(pOusters, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;

		SkillType_t       SkillType  = pOustersSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillLevel_t      SkillLevel = pOustersSkillSlot->getExpLevel();

		SkillInput input(pOusters, pOustersSkillSlot);
		SkillOutput output;
		computeOutput(input, output);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, pTargetCreature, output.Range);
		bool bHitRoll    = HitRoll::isSuccess(pOusters, pTargetCreature, SkillLevel/2);
		bool bCanHit     = canHit(pOusters, pTargetCreature, SkillType) && canAttack(pOusters, pTargetCreature);
		bool bPK         = verifyPK(pOusters, pTargetCreature);
		bool bEffected	 = pOusters->hasRelicItem() 
							|| pOusters->isFlag(Effect::EFFECT_CLASS_HAS_FLAG)
							|| pOusters->isFlag(Effect::EFFECT_CLASS_HAS_SWEEPER);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bCanHit && bPK && !bEffected )
		{
			// 빠르게 PC를 움직여준다.
			if (pZone->moveFastPC(pOusters, pOusters->getX(), pOusters->getY(), pTargetCreature->getX(), pTargetCreature->getY(), getSkillType())) 
			{
				decreaseMana(pOusters, RequiredMP, _GCSkillToObjectOK1);

				bool bCriticalHit = false;

				// 데미지를 준다.
				Damage_t Damage = computeDamage(pOusters, pTargetCreature, 0, bCriticalHit) + output.Damage;
				setDamage(pTargetCreature, Damage, pOusters, SkillType, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
				computeAlignmentChange(pTargetCreature, Damage, pOusters, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
				decreaseDurability(pOusters, pTargetCreature, pSkillInfo, &_GCSkillToObjectOK1, &_GCSkillToObjectOK2);

				// 크리티컬 히트라면 상대방을 뒤로 물러나게 한다.
				if (bCriticalHit)
				{
					knockbackCreature(pZone, pTargetCreature, pOusters->getX(), pOusters->getY());
				}

				if (pTargetCreature->isDead())
				{
					int exp = computeCreatureExp(pTargetCreature, 100, pOusters);
					shareOustersExp(pOusters, exp, _GCSkillToObjectOK1);
				}

				// 패킷을 준비하고 보낸다.
				_GCSkillToObjectOK1.setSkillType(SkillType);
				_GCSkillToObjectOK1.setCEffectID(CEffectID);
				_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
				_GCSkillToObjectOK1.setDuration(0);

				pPlayer->sendPacket(&_GCSkillToObjectOK1);
				_GCSkillToObjectOK2.setObjectID(pOusters->getObjectID());
				_GCSkillToObjectOK2.setSkillType(SkillType);
				_GCSkillToObjectOK2.setDuration(0);

				if (pTargetCreature->isPC()) 
				{
					Player* pTargetPlayer = pTargetCreature->getPlayer();
					Assert(pTargetPlayer != NULL);
					pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
				} 
				else 
				{
					Monster * pMonster = dynamic_cast<Monster*>(pTargetCreature);
					pMonster->addEnemy(pOusters);
				}

				pOustersSkillSlot->setRunTime(output.Delay);

			} 
			else 
			{
				executeSkillFailNormal(pOusters, getSkillType(), pTargetCreature);
			}
		} 
		else 
		{
			executeSkillFailNormal(pOusters, getSkillType(), pTargetCreature);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

ChargingAttack g_ChargingAttack;
