//////////////////////////////////////////////////////////////////////////////
// Filename    : RingOfFlare.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "RingOfFlare.h"
#include "EffectRingOfFlare.h"

#include "GCSkillToSelfOK1.h"
#include "GCSkillToSelfOK2.h"
#include "GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void RingOfFlare::execute(Ousters* pOusters, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	BYTE Grade = 0;
	if (pOustersSkillSlot->getExpLevel() < 15 ) Grade = 0;
	else if (pOustersSkillSlot->getExpLevel() < 30 ) Grade = 1;
	else Grade = 2;

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Item* pWeapon = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
		if (pWeapon == NULL || pWeapon->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
		{
			executeSkillFailException(pOusters, pOustersSkillSlot->getSkillType(), Grade);
			return;
		}

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t       SkillType  = pOustersSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		//SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		//SkillLevel_t      SkillLevel = pOustersSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP() + pOustersSkillSlot->getExpLevel()/2;
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pOusters);
		bool bHitRoll    = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot);
		bool bEffected   = pOusters->isFlag(Effect::EFFECT_CLASS_RING_OF_FLARE);
		bool bSatisfyRequire = pOusters->satisfySkillRequire(pSkillInfo);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected && bSatisfyRequire)
		{
			decreaseMana(pOusters, RequiredMP, _GCSkillToSelfOK1);

			// 지속 시간을 계산한다.
			SkillInput input(pOusters, pOustersSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			//cout << pOusters->getName() << "이 RingOfFlare를 썼고 데미지는 " << output.Damage << "입니다." << endl;

			// 이팩트 클래스를 만들어 붙인다.
			EffectRingOfFlare* pEffect = new EffectRingOfFlare(pOusters);
			pEffect->setDeadline(output.Duration);
			pEffect->setDamage(output.Damage);
			pEffect->setNextTime(0);
			if (Grade > 0 )
			{
				if (Grade == 1 ) pEffect->setSendEffectClass(Effect::EFFECT_CLASS_RING_OF_FLARE_2);
				else pEffect->setSendEffectClass(Effect::EFFECT_CLASS_RING_OF_FLARE_3);
			}
			else pEffect->setSendEffectClass(Effect::EFFECT_CLASS_RING_OF_FLARE);

			pOusters->addEffect(pEffect);
			pOusters->setFlag(Effect::EFFECT_CLASS_RING_OF_FLARE);

			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(output.Duration);
			_GCSkillToSelfOK1.setGrade(Grade);
		
			_GCSkillToSelfOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(output.Duration);
			_GCSkillToSelfOK2.setGrade(Grade);
		
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(),  &_GCSkillToSelfOK2, pOusters);

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pOusters->getObjectID());
			gcAddEffect.setEffectID(pEffect->getSendEffectClass());
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(), &gcAddEffect);

			pOustersSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pOusters, getSkillType(), NULL, Grade);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType(), Grade);
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	__END_CATCH
}

RingOfFlare g_RingOfFlare;
