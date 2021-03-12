//////////////////////////////////////////////////////////////////////////////
// Filename    : Reflection.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Reflection.h"
#include "EffectReflection.h"

#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void Reflection::execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		SkillLevel_t      SkillLevel = pSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bEffected   = pSlayer->isFlag(Effect::EFFECT_CLASS_REFLECTION);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToSelfOK1);

			// 지속 시간을 계산한다.
			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			// 이팩트 클래스를 만들어 붙인다.
			EffectReflection* pEffect = new EffectReflection(pSlayer);
			pEffect->setDeadline(output.Duration);
			pEffect->setLevel(SkillLevel);
			pSlayer->addEffect(pEffect);
			pSlayer->setFlag(Effect::EFFECT_CLASS_REFLECTION);

			// 경험치를 올린다.
			SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));
			Exp_t ExpUp = 10* (Grade + 1);
			shareAttrExp(pSlayer, ExpUp, 1, 1, 8, _GCSkillToSelfOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToSelfOK1);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToSelfOK1);

			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(0);
		
			_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(0);
		
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(),  &_GCSkillToSelfOK2, pSlayer);

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pSlayer->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_REFLECTION);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcAddEffect);

			pSkillSlot->setRunTime(output.Delay);
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	__END_CATCH
}



// Reflection이 되는가?
bool CheckReflection(Creature* pAttacker, Creature* pTargetCreature, SkillType_t SkillType)
{
	__BEGIN_TRY

	//Assert(pAttacker != NULL);
	//Assert(pTargetCreature != NULL);

	// 슬레이어만이 이 기술을 쓸 수 있다.
	if (pAttacker==NULL
		|| pTargetCreature==NULL
		|| pTargetCreature->isSlayer() == false)
	{
		return false;
	}

	// 기술이 걸려있고, 현재 마비 상태가 아니라면...
	if (pTargetCreature->isFlag(Effect::EFFECT_CLASS_REFLECTION) 
		&& !pTargetCreature->isFlag(Effect::EFFECT_CLASS_PARALYZE))
	{
		Slayer*           pTargetSlayer          = dynamic_cast<Slayer*>(pTargetCreature);
		SkillSlot*        pSkillSlot = pTargetSlayer->hasSkill(SKILL_REFLECTION);
		SkillInfo*        pSkillInfo             = g_pSkillInfoManager->getSkillInfo(SKILL_REFLECTION);
		//SkillDomainType_t DomainType             = pSkillInfo->getDomainType();
		Zone*             pZone                  = pAttacker->getZone();

		Assert(pTargetSlayer != NULL);
		Assert(pSkillSlot != NULL);
		Assert(pSkillInfo != NULL);
		Assert(pZone != NULL);

		// hitroll이 성공했다면...
		//if (HitRoll::isSuccess(pTargetSlayer, pAttacker) && canHit(pTargetSlayer, pAttacker, SKILL_REFLECTION))

		int SuccessRate = 30 + pSkillSlot->getExpLevel()/5;
		SuccessRate = min(SuccessRate, 50);	// 최대 50%

		if (rand()%100 < SuccessRate)
		{
			GCSkillToSelfOK1 _GCSkillToSelfOK1;
			GCSkillToSelfOK2 _GCSkillToSelfOK2;

			// 본인에게 reflection effect를 붙여준다.
			if (pTargetCreature->isPC())
			{
				_GCSkillToSelfOK1.setSkillType(SKILL_CURE_EFFECT);
				_GCSkillToSelfOK1.setDuration(0);
				pTargetCreature->getPlayer()->sendPacket(&_GCSkillToSelfOK1);
			}

			// 다른 사람들에게 reflection effect를 보여준다.
			_GCSkillToSelfOK2.setObjectID(pTargetCreature->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SKILL_CURE_EFFECT);
			_GCSkillToSelfOK2.setDuration(0);
			pZone->broadcastPacket( pTargetCreature->getX(), pTargetCreature->getY(), &_GCSkillToSelfOK2, pTargetCreature );


			return true;
		}
	}

	return false;

	__END_CATCH
}


	
Reflection g_Reflection;
