//////////////////////////////////////////////////////////////////////////////
// Filename    : WillOfLife.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////
#include "WillOfLife.h"
#include "EffectWillOfLife.h"
#include "RankBonus.h"

#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "HitRoll.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void WillOfLife::execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayerself)" << endl;

	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();

		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t       SkillType  = pVampireSkillSlot->getSkillType();
		//SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		// 스킬 레벨에 따라 데미지 보너스가 달라진다.
		SkillInput input( pVampire );
		SkillOutput output;
		computeOutput(input, output);

		int  RequiredMP  = output.Damage;
		bool bManaCheck  = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pVampire);
		bool bHitRoll    = HitRoll::isSuccessWillOfLife(pVampire);
		bool bEffected   = pVampire->isFlag(Effect::EFFECT_CLASS_WILL_OF_LIFE);

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToSelfOK1);

			// 이펙트 클래스를 만들어 붙인다.
			EffectWillOfLife* pEffect = new EffectWillOfLife(pVampire);
			pEffect->setDeadline(output.Duration);
			pEffect->setBonus(output.Damage);
			pEffect->setNextTime(0);
			pVampire->addEffect(pEffect);
			pVampire->setFlag(Effect::EFFECT_CLASS_WILL_OF_LIFE);

			// 패킷을 만들어 보낸다.
			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(output.Duration);
		
			_GCSkillToSelfOK2.setObjectID(pVampire->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration(output.Duration);
		
			pPlayer->sendPacket(&_GCSkillToSelfOK1);

			GCStatusCurrentHP gcStatusCurrentHP;

			gcStatusCurrentHP.setObjectID( pVampire->getObjectID() );
			gcStatusCurrentHP.setCurrentHP( pVampire->getHP() );
		
			pZone->broadcastPacket(pVampire->getX(), pVampire->getY(),  &_GCSkillToSelfOK2, pVampire);
			pZone->broadcastPacket(pVampire->getX(), pVampire->getY(),  &gcStatusCurrentHP);

			// 이펙트가 붙었다고 알려준다.
			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(pVampire->getObjectID());
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_WILL_OF_LIFE);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcAddEffect);
		} 
		else 
		{
			executeSkillFailNormal(pVampire, getSkillType(), NULL);
		}

		// set Next Run Time
		if ( bTimeCheck ) pVampireSkillSlot->setRunTime(output.Delay);
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerself)" << endl;

	__END_CATCH
}

WillOfLife g_WillOfLife;
