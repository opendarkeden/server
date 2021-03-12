//////////////////////////////////////////////////////////////////////////////
// Filename    : SimpleCureSkill.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SimpleCureSkill.h"
#include "EffectBloodDrain.h"
#include "EffectAftermath.h"

#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Gpackets/GCRemoveEffect.h"

SimpleCureSkill g_SimpleCureSkill;

//////////////////////////////////////////////////////////////////////////////
// class SimpleCureSkill member methods
//////////////////////////////////////////////////////////////////////////////

void SimpleCureSkill::execute(Slayer* pSlayer, SkillSlot* pSkillSlot, 
	const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bHPCheck    = false;

		EffectBloodDrain* pEffectBloodDrain = NULL;
		
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
		
			// HP를 세팅한다.
			HP_t CurrentHP = pSlayer->getHP(ATTR_CURRENT);
			HP_t MaxHP     = pSlayer->getHP(ATTR_MAX);

			// 실제 회복 수치를 계산한다.
			int RealHealPoint = 0;
			if( CurrentHP + HealPoint <= MaxHP ) {
				RealHealPoint = max( (unsigned int)0, HealPoint );
			} else {
				RealHealPoint = max( 0, MaxHP - CurrentHP );
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

			result.bSuccess = true;
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

void SimpleCureSkill::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, 
	const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID) 
	
{
	__BEGIN_TRY

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

		// 슬레이어 외에는 치료할 수가 없다.
		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| pTargetCreature->isSlayer() == false)
		{
			executeSkillFailException(pSlayer, param.SkillType);
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		bool bHPCheck = false;

		// 체력이 닳거나, 흡혈을 당한 상태여야 한다.
		Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);
		Assert(pTargetSlayer != NULL);

		EffectBloodDrain* pEffectBloodDrain = NULL;

		if (pTargetSlayer->getHP(ATTR_CURRENT) < pTargetSlayer->getHP(ATTR_MAX))
		{
			bHPCheck = true;
		}
		if (pTargetSlayer->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN))
		{
			Effect* pEffect = pTargetSlayer->findEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);
			pEffectBloodDrain = dynamic_cast<EffectBloodDrain*>(pEffect);
			Assert(pEffectBloodDrain != NULL);

			if (pEffectBloodDrain->getLevel() < param.Level) bHPCheck = true;
		}

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);

		if (bHPCheck && bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && pTargetCreature->isAlive())
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToObjectOK1);

			uint HealPoint = param.SkillDamage;

			// 흡혈당한 상태라면 흡혈 상태를 날려준다.
			if (pEffectBloodDrain != NULL && pEffectBloodDrain->getLevel() < param.Level)
			{
				// 흡혈 아르바이트를 방지하기 위한 후유증 이펙트를 붙여준다.
				if (pTargetSlayer->isFlag(Effect::EFFECT_CLASS_AFTERMATH))
				{
					Effect* pEffect = pTargetSlayer->findEffect(Effect::EFFECT_CLASS_AFTERMATH);
					EffectAftermath* pEffectAftermath = dynamic_cast<EffectAftermath*>(pEffect);
					pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
				}
				else
				{
					EffectAftermath* pEffectAftermath = new EffectAftermath(pTargetSlayer);
					pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
					pTargetSlayer->addEffect(pEffectAftermath);
					pTargetSlayer->setFlag(Effect::EFFECT_CLASS_AFTERMATH);
					pEffectAftermath->create(pTargetSlayer->getName());
				}


				pEffectBloodDrain->destroy(pTargetSlayer->getName());
				pTargetSlayer->deleteEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);

				SLAYER_RECORD prev;
				pTargetSlayer->getSlayerRecord(prev);
				pTargetSlayer->initAllStat();
				pTargetSlayer->sendRealWearingInfo();
				pTargetSlayer->addModifyInfo(prev, _GCSkillToObjectOK2);

				GCRemoveEffect gcRemoveEffect;
				gcRemoveEffect.setObjectID(pTargetSlayer->getObjectID());
				gcRemoveEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_BLOOD_DRAIN);
				pZone->broadcastPacket(pTargetSlayer->getX(), pTargetSlayer->getY(), &gcRemoveEffect);
			}

			// 다른 사람을 치료한다.
			HP_t CurrentHP = pTargetSlayer->getHP(ATTR_CURRENT);
			HP_t MaxHP     = pTargetSlayer->getHP(ATTR_MAX);

			// 실제 회복 수치를 계산한다.
			int RealHealPoint = 0;
			if( CurrentHP + HealPoint <= MaxHP ) {
				RealHealPoint = max( (unsigned int)0, HealPoint );
			} else {
				RealHealPoint = max( 0, MaxHP - CurrentHP );
			}

			// 경험치를 올려준다.
			shareAttrExp(pSlayer, HealPoint , param.STRMultiplier, param.DEXMultiplier, param.INTMultiplier, _GCSkillToObjectOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToObjectOK1);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToObjectOK1);

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

			result.bSuccess = true;
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
	



