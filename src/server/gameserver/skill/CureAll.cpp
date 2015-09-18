//////////////////////////////////////////////////////////////////////////////
// Filename    : CureAll.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CureAll.h"
#include "SimpleCureSkill.h"
#include "GCSkillToObjectOK1.h"
#include "GCSkillToObjectOK2.h"
#include "GCSkillToObjectOK3.h"
#include "GCSkillToObjectOK4.h"
#include "GCSkillToObjectOK5.h"
#include "GCSkillToSelfOK1.h"
#include "GCSkillToSelfOK2.h"
#include "EffectDoom.h"
#include "EffectParalyze.h"
#include "EffectSeduction.h"
#include "CurePoison.h"
#include "EffectPoison.h"
#include "EffectYellowPoisonToCreature.h"
#include "EffectDarkBluePoison.h"
#include "EffectGreenStalker.h"
#include "EffectBloodDrain.h"
#include "EffectBlunting.h"
#include "GCRemoveEffect.h"
#include "GCStatusCurrentHP.h"
#include "EffectAftermath.h"

const uint CureAllBloodDrainLevel = 75;

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void CureAll::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	SkillInput input(pSlayer, pSkillSlot);
	SkillOutput output;
	input.TargetType = SkillInput::TARGET_OTHER;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.STRMultiplier = 1;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 8;
	param.Level         = CureAllBloodDrainLevel;


	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch제거. by sigi. 2002.5.2
		// 슬레이어 외에는 치료할 수가 없다.
		if (pTargetCreature==NULL
			|| pTargetCreature->isSlayer() == false)
		{
			executeSkillFailException(pSlayer, param.SkillType);
			return;
		}

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		Level_t 		  SkillLevel = pSkillSlot->getExpLevel();

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;

		bool bHPCheck = false;

		// 체력이 닳거나, 흡혈을 당한 상태여야 한다.
		Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);
		Assert(pTargetSlayer != NULL);

		EffectBloodDrain* pEffectBloodDrain = NULL;

		bool bEffected  = false; // 아무 저주나 걸려 있으면 켠다.

		if (pTargetSlayer->getHP(ATTR_CURRENT) < pTargetSlayer->getHP(ATTR_MAX))
		{
			bHPCheck = true;
		}
		if (pTargetSlayer->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN))
		{
			Effect* pEffect = pTargetSlayer->findEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);
			pEffectBloodDrain = dynamic_cast<EffectBloodDrain*>(pEffect);
			Assert(pEffectBloodDrain != NULL);

			if (pEffectBloodDrain->getLevel() < CureAllBloodDrainLevel) bHPCheck = true;
			bEffected = true;
		}

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);

		bool bDoom      = false;
		bool bBlunting	= false;
		bool bParalyze  = false;
		bool bSeduction = false;

		EffectDoom*      pEffectDoom     = NULL;
		EffectBlunting*  pEffectBlunting = NULL;
		EffectParalyze*  pEffectParalyze = NULL;
		EffectSeduction* pEffectSeduction = NULL;

		// 저주 계열 해소
		if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_DOOM)) 
		{
			pEffectDoom = (EffectDoom*)pTargetCreature->findEffect(Effect::EFFECT_CLASS_DOOM);
			Assert(pEffectDoom != NULL);

			bDoom = HitRoll::isSuccessRemoveCurse(50, SkillLevel, 10, pEffectDoom->getLevel(), 10);
			bEffected = true;
			bHPCheck = true;
		}
		if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_BLUNTING)) 
		{
			pEffectBlunting = (EffectBlunting*)pTargetCreature->findEffect(Effect::EFFECT_CLASS_BLUNTING);
			Assert(pEffectBlunting != NULL);

			bBlunting = HitRoll::isSuccessRemoveCurse(50, SkillLevel, 15, pEffectBlunting->getLevel(), 10);
			bEffected = true;
			bHPCheck = true;
		}
		if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_PARALYZE)) 
		{
			pEffectParalyze = (EffectParalyze*)pTargetCreature->findEffect(Effect::EFFECT_CLASS_PARALYZE);
			Assert(pEffectParalyze != NULL);

			bParalyze = HitRoll::isSuccessRemoveCurse(50, SkillLevel, 20, pEffectParalyze->getLevel(), 10);
			bEffected = true;
			bHPCheck = true;
		}
		if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_SEDUCTION)) 
		{
			pEffectSeduction = (EffectSeduction*)pTargetCreature->findEffect(Effect::EFFECT_CLASS_SEDUCTION);
			Assert(pEffectSeduction != NULL);

			bSeduction = HitRoll::isSuccessRemoveCurse(50, SkillLevel, 30, pEffectSeduction->getLevel(), 10);
			bEffected = true;
			bHPCheck = true;
		}

		// 독 계열 해소
		bool bGreenPoison    = false; // GreenPoison을 치료할까의 여부
		bool bYellowPoison   = false; // YellowPoison을 치료할까의 여부
		bool bDarkBluePoison = false; // DarkBluePoison을 치료할까의 여부
		bool bGreenStalker   = false; // GreenStalker를 치료할까의 여부

		EffectPoison*                 pEffectPoison                 = NULL;
		EffectYellowPoisonToCreature* pEffectYellowPoisonToCreature = NULL;
		EffectDarkBluePoison*         pEffectDBP                   = NULL;
		EffectGreenStalker*           pEffectGreenStalker           = NULL;

		if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_POISON)) 
		{
			pEffectPoison = (EffectPoison*)pTargetCreature->findEffect(Effect::EFFECT_CLASS_POISON);
			Assert(pEffectPoison != NULL);

			bGreenPoison = HitRoll::isSuccessCurePoison(50, SkillLevel, 10, pEffectPoison->getLevel(), 10);
			bEffected = true;
			bHPCheck = true;
		}

		if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE)) 
		{
			pEffectYellowPoisonToCreature = (EffectYellowPoisonToCreature*)pTargetCreature->findEffect(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
			Assert(pEffectYellowPoisonToCreature != NULL);

			bYellowPoison = HitRoll::isSuccessCurePoison(50, SkillLevel, 20, pEffectYellowPoisonToCreature->getLevel(), 10);
			bEffected = true;
			bHPCheck = true;
		}

		if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_DARKBLUE_POISON)) 
		{
			pEffectDBP = (EffectDarkBluePoison*)pTargetCreature->findEffect(Effect::EFFECT_CLASS_DARKBLUE_POISON);
			Assert(pEffectDBP != NULL);

			bDarkBluePoison = HitRoll::isSuccessCurePoison(50, SkillLevel, 30, pEffectDBP->getLevel(), 10);
			bEffected = true;
			bHPCheck = true;
		}

		if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_GREEN_STALKER)) 
		{
			pEffectGreenStalker = (EffectGreenStalker*)pTargetCreature->findEffect(Effect::EFFECT_CLASS_GREEN_STALKER);
			Assert(pEffectGreenStalker != NULL);

			bGreenStalker = HitRoll::isSuccessCurePoison(50, SkillLevel, 40, pEffectGreenStalker->getLevel(), 10);
			bEffected = true;
			bHPCheck = true;
		}

		if (bHPCheck && bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && pTargetCreature->isAlive())
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToObjectOK1);

			uint HealPoint = param.SkillDamage;

			// 각각의 저주를 삭제하고,
			// 패킷에다 이펙트 삭제하라고 더한다.
			GCRemoveEffect gcRemoveEffect;
			gcRemoveEffect.setObjectID(pTargetCreature->getObjectID());

			// 흡혈당한 상태라면 흡혈 상태를 날려준다.
			if (pEffectBloodDrain != NULL && pEffectBloodDrain->getLevel() < CureAllBloodDrainLevel)
			{
				// 흡혈 아르바이트를 방지하기 위한 후유증 이펙트를 붙여준다.
				if (pTargetCreature->isFlag(Effect::EFFECT_CLASS_AFTERMATH))
				{
						Effect* pEffect = pTargetCreature->findEffect(Effect::EFFECT_CLASS_AFTERMATH);
						EffectAftermath* pEffectAftermath = dynamic_cast<EffectAftermath*>(pEffect);
						pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
				}
				else
				{
						EffectAftermath* pEffectAftermath = new EffectAftermath(pTargetCreature);
						pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
						pTargetCreature->addEffect(pEffectAftermath);
						pTargetCreature->setFlag(Effect::EFFECT_CLASS_AFTERMATH);
						pEffectAftermath->create(pTargetCreature->getName());
				}

				pEffectBloodDrain->destroy(pTargetSlayer->getName());
				pTargetSlayer->deleteEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);

				SLAYER_RECORD prev;
				pTargetSlayer->getSlayerRecord(prev);
				pTargetSlayer->initAllStat();
				pTargetSlayer->sendRealWearingInfo();
				pTargetSlayer->addModifyInfo(prev, _GCSkillToObjectOK2);

				gcRemoveEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_BLOOD_DRAIN);
			}

			if (bDoom)
			{
				pEffectDoom->setDeadline(0);
				pTargetCreature->removeFlag(Effect::EFFECT_CLASS_DOOM);
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_DOOM);
			}
			if (bBlunting)
			{
				pEffectBlunting->setDeadline(0);
				pTargetCreature->removeFlag(Effect::EFFECT_CLASS_BLUNTING);
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_BLUNTING);
			}
			if (bParalyze)
			{
				pEffectParalyze->setDeadline(0);
				pTargetCreature->removeFlag(Effect::EFFECT_CLASS_PARALYZE);
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_PARALYZE);
			}
			if (bSeduction)
			{
				pEffectSeduction->setDeadline(0);
				pTargetCreature->removeFlag(Effect::EFFECT_CLASS_SEDUCTION);
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_SEDUCTION);
			}

			// 각각의 독마다 치료를 하고,
			// 패킷에다 이펙트 삭제하라고 더한다.
			if (bGreenPoison)
			{
				pEffectPoison->setDeadline(0);
				pTargetCreature->removeFlag(Effect::EFFECT_CLASS_POISON);
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_POISON);
			}
			if (bYellowPoison)
			{
				pEffectYellowPoisonToCreature->setDeadline(0);
				pTargetCreature->removeFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
			}
			if (bDarkBluePoison)
			{
				pEffectDBP->setDeadline(0);
				pTargetCreature->removeFlag(Effect::EFFECT_CLASS_DARKBLUE_POISON);
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_DARKBLUE_POISON);
			}
			if (bGreenStalker)
			{
				pEffectGreenStalker->setDeadline(0);
				pTargetCreature->removeFlag(Effect::EFFECT_CLASS_GREEN_STALKER);
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_GREEN_STALKER);
			}

			if(bEffected ) {
				pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcRemoveEffect);
			}

			// 다른 사람을 치료한다.
			HP_t CurrentHP = pTargetSlayer->getHP(ATTR_CURRENT);
			HP_t MaxHP     = pTargetSlayer->getHP(ATTR_MAX);

			// 실제 회복 수치를 계산한다.
			int RealHealPoint = 0;
			if(CurrentHP + HealPoint <= MaxHP ) {
				RealHealPoint = max((unsigned int)0, HealPoint);
			} else {
				RealHealPoint = max(0, MaxHP - CurrentHP);
			}

			// 경험치를 올려준다.
			shareAttrExp(pSlayer, RealHealPoint , param.STRMultiplier, param.DEXMultiplier, param.INTMultiplier, _GCSkillToObjectOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToObjectOK1);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToObjectOK1);
	
			// HP를 셋팅한다.
			CurrentHP = min((int)(MaxHP), (int)(CurrentHP + HealPoint));
			pTargetSlayer->setHP(CurrentHP, ATTR_CURRENT);

			// 치료가 되었으니 HP를 브로드캐스팅한다.
			GCStatusCurrentHP gcStatusCurrentHP;
			gcStatusCurrentHP.setObjectID(TargetObjectID);
			gcStatusCurrentHP.setCurrentHP (CurrentHP);
			pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcStatusCurrentHP);

			_GCSkillToObjectOK2.addShortData(MODIFY_CURRENT_HP, CurrentHP);
			
			ZoneCoord_t myX     = pSlayer->getX();
			ZoneCoord_t myY     = pSlayer->getY();
			ZoneCoord_t targetX = pTargetCreature->getX();
			ZoneCoord_t targetY = pTargetCreature->getY();

			_GCSkillToObjectOK1.setSkillType(param.SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(0);

			_GCSkillToObjectOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK2.setSkillType(param.SkillType);
			_GCSkillToObjectOK2.setDuration (0);

			_GCSkillToObjectOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK3.setSkillType(param.SkillType);
			_GCSkillToObjectOK3.setTargetXY(targetX, targetY);

			_GCSkillToObjectOK4.setSkillType(param.SkillType);
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);
			
			_GCSkillToObjectOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK5.setSkillType(param.SkillType);
			_GCSkillToObjectOK5.setTargetObjectID (TargetObjectID);
			_GCSkillToObjectOK5.setDuration (0);

			pPlayer->sendPacket(&_GCSkillToObjectOK1);

			if (pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);
				pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
			}
			
			list<Creature*> cList;
			cList.push_back(pSlayer);
			cList.push_back(pTargetCreature);

			cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCSkillToObjectOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToObjectOK3 , cList);
			pZone->broadcastPacket(targetX, targetY,  &_GCSkillToObjectOK4 , cList);
			
			pSkillSlot->setRunTime(param.Delay);

		} 
		else 
		{
			executeSkillFailNormal(pSlayer, param.SkillType, pTargetCreature);
		}
	} 
	catch(Throwable & t)  
	{
		executeSkillFailException(pSlayer, param.SkillType);
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void CureAll::execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	SkillInput input(pSlayer, pSkillSlot);
	SkillOutput output;
	input.TargetType = SkillInput::TARGET_SELF;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.STRMultiplier = 1;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 8;
	param.Level         = CureAllBloodDrainLevel;

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		Level_t 		  SkillLevel = pSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bHPCheck    = false;

		EffectBloodDrain* pEffectBloodDrain = NULL;
		
		bool bEffected  = false; // 아무 저주나 걸려 있으면 켠다.
		if (pSlayer->getHP(ATTR_CURRENT) < pSlayer->getHP(ATTR_MAX))
		{
			bHPCheck = true;
		}
		if (pSlayer->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN))
		{
			Effect* pEffect = pSlayer->findEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);
			pEffectBloodDrain = dynamic_cast<EffectBloodDrain*>(pEffect);
			Assert(pEffectBloodDrain != NULL);
				
			if (pEffectBloodDrain->getLevel() < param.Level) bHPCheck = true;
			bEffected = true;
		}

		bool bDoom      = false;
		bool bBlunting  = false;
		bool bParalyze  = false;
		bool bSeduction = false;

		EffectDoom*      pEffectDoom     = NULL;
		EffectBlunting*  pEffectBlunting = NULL;
		EffectParalyze*  pEffectParalyze = NULL;
		EffectSeduction* pEffectSeduction = NULL;

		// 저주 계열 해소
		if (pSlayer->isEffect(Effect::EFFECT_CLASS_DOOM)) 
		{
			pEffectDoom = (EffectDoom*)pSlayer->findEffect(Effect::EFFECT_CLASS_DOOM);
			Assert(pEffectDoom != NULL);

			bDoom = HitRoll::isSuccessRemoveCurse(75, SkillLevel, 10, pEffectDoom->getLevel(), 25);
			bEffected = true;
			bHPCheck = true;
		}
		if (pSlayer->isEffect(Effect::EFFECT_CLASS_BLUNTING)) 
		{
			pEffectBlunting = (EffectBlunting*)pSlayer->findEffect(Effect::EFFECT_CLASS_BLUNTING);
			Assert(pEffectBlunting != NULL);

			bBlunting = HitRoll::isSuccessRemoveCurse(75, SkillLevel, 15, pEffectBlunting->getLevel(), 25);
			bEffected = true;
			bHPCheck = true;
		}
		if (pSlayer->isEffect(Effect::EFFECT_CLASS_PARALYZE)) 
		{
			pEffectParalyze = (EffectParalyze*)pSlayer->findEffect(Effect::EFFECT_CLASS_PARALYZE);
			Assert(pEffectParalyze != NULL);

			bParalyze = HitRoll::isSuccessRemoveCurse(75, SkillLevel, 20, pEffectParalyze->getLevel(), 25);
			bEffected = true;
			bHPCheck = true;
		}
		if (pSlayer->isEffect(Effect::EFFECT_CLASS_SEDUCTION)) 
		{
			pEffectSeduction = (EffectSeduction*)pSlayer->findEffect(Effect::EFFECT_CLASS_SEDUCTION);
			Assert(pEffectSeduction != NULL);

			bSeduction = HitRoll::isSuccessRemoveCurse(75, SkillLevel, 30, pEffectSeduction->getLevel(), 25);
			bEffected = true;
			bHPCheck = true;
		}

		// 독 계열 해소
		bool bGreenPoison    = false; // GreenPoison을 치료할까의 여부
		bool bYellowPoison   = false; // YellowPoison을 치료할까의 여부
		bool bDarkBluePoison = false; // DarkBluePoison을 치료할까의 여부
		bool bGreenStalker   = false; // GreenStalker를 치료할까의 여부

		EffectPoison*                 pEffectPoison                 = NULL;
		EffectYellowPoisonToCreature* pEffectYellowPoisonToCreature = NULL;
		EffectDarkBluePoison*         pEffectDBP                   = NULL;
		EffectGreenStalker*           pEffectGreenStalker           = NULL;

		if (pSlayer->isEffect(Effect::EFFECT_CLASS_POISON)) 
		{
			pEffectPoison = (EffectPoison*)pSlayer->findEffect(Effect::EFFECT_CLASS_POISON);
			Assert(pEffectPoison != NULL);

			bGreenPoison = HitRoll::isSuccessCurePoison(75, SkillLevel, 10, pEffectPoison->getLevel(), 25);
			bEffected = true;
			bHPCheck = true;
		}

		if (pSlayer->isEffect(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE)) 
		{
			pEffectYellowPoisonToCreature = (EffectYellowPoisonToCreature*)pSlayer->findEffect(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
			Assert(pEffectYellowPoisonToCreature != NULL);

			bYellowPoison = HitRoll::isSuccessCurePoison(75, SkillLevel, 20, pEffectYellowPoisonToCreature->getLevel(), 25);
			bEffected = true;
			bHPCheck = true;
		}

		if (pSlayer->isEffect(Effect::EFFECT_CLASS_DARKBLUE_POISON)) 
		{
			pEffectDBP = (EffectDarkBluePoison*)pSlayer->findEffect(Effect::EFFECT_CLASS_DARKBLUE_POISON);
			Assert(pEffectDBP != NULL);

			bDarkBluePoison = HitRoll::isSuccessCurePoison(75, SkillLevel, 30, pEffectDBP->getLevel(), 25);
			bEffected = true;
			bHPCheck = true;
		}

		if (pSlayer->isEffect(Effect::EFFECT_CLASS_GREEN_STALKER)) 
		{
			pEffectGreenStalker = (EffectGreenStalker*)pSlayer->findEffect(Effect::EFFECT_CLASS_GREEN_STALKER);
			Assert(pEffectGreenStalker != NULL);

			bGreenStalker = HitRoll::isSuccessCurePoison(75, SkillLevel, 40, pEffectGreenStalker->getLevel(), 25);
			bEffected = true;
			bHPCheck = true;
		}


		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bHPCheck && pSlayer->isAlive())
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToSelfOK1);

			uint HealPoint = param.SkillDamage;

			// 흡혈당한 상태라면 흡혈 상태를 날려준다.
			if (pEffectBloodDrain != NULL && pEffectBloodDrain->getLevel() < param.Level)
			{
                                // 흡혈 아르바이트를 방지하기 위한 후유증 이펙트를 붙여준다.
				if (pSlayer->isFlag(Effect::EFFECT_CLASS_AFTERMATH))
				{
						Effect* pEffect = pSlayer->findEffect(Effect::EFFECT_CLASS_AFTERMATH);
						EffectAftermath* pEffectAftermath = dynamic_cast<EffectAftermath*>(pEffect);
						pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
				}
				else
				{
						EffectAftermath* pEffectAftermath = new EffectAftermath(pSlayer);
						pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
						pSlayer->addEffect(pEffectAftermath);
						pSlayer->setFlag(Effect::EFFECT_CLASS_AFTERMATH);
						pEffectAftermath->create(pSlayer->getName());
				}


				pEffectBloodDrain->destroy(pSlayer->getName());
				pSlayer->deleteEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);

				SLAYER_RECORD prev;
				pSlayer->getSlayerRecord(prev);
				pSlayer->initAllStat();
				pSlayer->sendRealWearingInfo();
				pSlayer->addModifyInfo(prev, _GCSkillToSelfOK1);

				GCRemoveEffect gcRemoveEffect;
				gcRemoveEffect.setObjectID(pSlayer->getObjectID());
				gcRemoveEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_BLOOD_DRAIN);
				pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcRemoveEffect);
			}

			// 각각의 저주를 삭제하고,
			// 패킷에다 이펙트 삭제하라고 더한다.
			GCRemoveEffect gcRemoveEffect;
			gcRemoveEffect.setObjectID(pSlayer->getObjectID());

			if (bDoom)
			{
				pEffectDoom->setDeadline(0);
				pSlayer->removeFlag(Effect::EFFECT_CLASS_DOOM);
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_DOOM);
			}
			if (bBlunting)
			{
				pEffectBlunting->setDeadline(0);
				pSlayer->removeFlag(Effect::EFFECT_CLASS_BLUNTING);
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_BLUNTING);
			}
			if (bParalyze)
			{
				pEffectParalyze->setDeadline(0);
				pSlayer->removeFlag(Effect::EFFECT_CLASS_PARALYZE);
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_PARALYZE);
			}
			if (bSeduction)
			{
				pEffectSeduction->setDeadline(0);
				pSlayer->removeFlag(Effect::EFFECT_CLASS_SEDUCTION);
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_SEDUCTION);
			}

			// 각각의 독마다 치료를 하고,
			// 패킷에다 이펙트 삭제하라고 더한다.
			if (bGreenPoison)
			{
				pEffectPoison->setDeadline(0);
				pSlayer->removeFlag(Effect::EFFECT_CLASS_POISON);
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_POISON);
			}
			if (bYellowPoison)
			{
				pEffectYellowPoisonToCreature->setDeadline(0);
				pSlayer->removeFlag(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
			}
			if (bDarkBluePoison)
			{
				pEffectDBP->setDeadline(0);
				pSlayer->removeFlag(Effect::EFFECT_CLASS_DARKBLUE_POISON);
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_DARKBLUE_POISON);
			}
			if (bGreenStalker)
			{
				pEffectGreenStalker->setDeadline(0);
				pSlayer->removeFlag(Effect::EFFECT_CLASS_GREEN_STALKER);
				gcRemoveEffect.addEffectList(Effect::EFFECT_CLASS_GREEN_STALKER);
			}

			if(bEffected ) {
				pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcRemoveEffect);
			}


			// HP를 세팅한다.
			HP_t CurrentHP = pSlayer->getHP(ATTR_CURRENT);
			HP_t MaxHP     = pSlayer->getHP(ATTR_MAX);

			// 실제 회복 수치를 계산한다.
			int RealHealPoint = 0;
			if(CurrentHP + HealPoint <= MaxHP ) {
				RealHealPoint = max((unsigned int)0, HealPoint);
			} else {
				RealHealPoint = max(0, MaxHP - CurrentHP);
			}
			// 경험치를 올려준다.
			shareAttrExp(pSlayer, RealHealPoint, param.STRMultiplier, param.DEXMultiplier, param.INTMultiplier, _GCSkillToSelfOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToSelfOK1);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToSelfOK1);

			CurrentHP = min((int)MaxHP, (int)(CurrentHP + HealPoint));
			pSlayer->setHP(CurrentHP , ATTR_CURRENT);

			// HP를 브로드캐스팅한다.
			GCStatusCurrentHP gcStatusCurrentHP;
			gcStatusCurrentHP.setObjectID(pSlayer->getObjectID());
			gcStatusCurrentHP.setCurrentHP (CurrentHP);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(), &gcStatusCurrentHP);
			
			ZoneCoord_t myX = pSlayer->getX();
			ZoneCoord_t myY = pSlayer->getY();

			_GCSkillToSelfOK1.setSkillType(param.SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(0);
			
			_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToSelfOK2.setSkillType(param.SkillType);
			_GCSkillToSelfOK2.setDuration (0);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToSelfOK1);

			pZone->broadcastPacket(myX, myY, &_GCSkillToSelfOK2, pSlayer);

			pSkillSlot->setRunTime(param.Delay);

		} 
		else 
		{
			executeSkillFailNormal(pSlayer, param.SkillType, NULL);
		}
	} 
	catch(Throwable & t)  
	{
		executeSkillFailException(pSlayer, param.SkillType);
	}

	__END_CATCH
}

CureAll g_CureAll;
