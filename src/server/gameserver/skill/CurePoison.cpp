//////////////////////////////////////////////////////////////////////////////
// Filename    : CurePoison.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "CurePoison.h"
#include "EffectPoison.h"
#include "EffectYellowPoisonToCreature.h"
#include "EffectDarkBluePoison.h"
#include "EffectGreenStalker.h"

#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void CurePoison::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
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

		// NoSuch제거. by sigi. 2002.5.2
		// 슬레이어 외에는 치료할 수 없다.
		if (pTargetCreature==NULL
			|| pTargetCreature->isSlayer() == false)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		// by sigi. 2002.12.3
		SkillLevel_t      SkillLevel = pSlayer->getINT()/2; //pSkillSlot->getExpLevel();

		bool bGreenPoison    = false; // GreenPoison을 치료할까의 여부
		bool bYellowPoison   = false; // YellowPoison을 치료할까의 여부
		bool bDarkBluePoison = false; // DarkBluePoison을 치료할까의 여부
		bool bGreenStalker   = false; // GreenStalker를 치료할까의 여부
		bool bEffected       = false; // 아무 독이나 걸려있으면 켠다.

		EffectPoison*                 pEffectPoison                 = NULL;
		EffectYellowPoisonToCreature* pEffectYellowPoisonToCreature = NULL;
		EffectDarkBluePoison*         pEffectDBP                   = NULL;
		EffectGreenStalker*           pEffectGreenStalker           = NULL;

		if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_POISON)) 
		{
			pEffectPoison = (EffectPoison*)pTargetCreature->findEffect(Effect::EFFECT_CLASS_POISON);
			Assert(pEffectPoison != NULL);

			bGreenPoison = HitRoll::isSuccessCurePoison(60, SkillLevel, 10, pEffectPoison->getLevel());
			bEffected = true;
		}

		if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE)) 
		{
			pEffectYellowPoisonToCreature = (EffectYellowPoisonToCreature*)pTargetCreature->findEffect(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
			Assert(pEffectYellowPoisonToCreature != NULL);

			bYellowPoison = HitRoll::isSuccessCurePoison(60, SkillLevel, 20, pEffectYellowPoisonToCreature->getLevel());
			bEffected = true;
		}

		if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_DARKBLUE_POISON)) 
		{
			pEffectDBP = (EffectDarkBluePoison*)pTargetCreature->findEffect(Effect::EFFECT_CLASS_DARKBLUE_POISON);
			Assert(pEffectDBP != NULL);

			bDarkBluePoison = HitRoll::isSuccessCurePoison(60, SkillLevel, 30, pEffectDBP->getLevel());
			bEffected = true;
		}

		if (pTargetCreature->isEffect(Effect::EFFECT_CLASS_GREEN_STALKER)) 
		{
			pEffectGreenStalker = (EffectGreenStalker*)pTargetCreature->findEffect(Effect::EFFECT_CLASS_GREEN_STALKER);
			Assert(pEffectGreenStalker != NULL);

			bGreenStalker = HitRoll::isSuccessCurePoison(60, SkillLevel, 40, pEffectGreenStalker->getLevel());
			bEffected = true;
		}

		int  RequiredMP = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, pTargetCreature, pSkillInfo->getRange());

		// 마나가 있고, 시간이 됐고, 거리가 적당하며,
		// 독이 하나라도 걸려있어야 한다.
		if (bManaCheck && bTimeCheck && bRangeCheck && bEffected)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToObjectOK1);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);
		
			// 각각의 독마다 치료를 하고,
			// 패킷에다 이펙트 삭제하라고 더한다.
			GCRemoveEffect gcRemoveEffect;
			gcRemoveEffect.setObjectID(pTargetCreature->getObjectID());

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

			// 경험치를 올린다.
			SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));
			Exp_t ExpUp = 10*(Grade+1);
			shareAttrExp(pSlayer, ExpUp, 1, 1, 8, _GCSkillToObjectOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToObjectOK1);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToObjectOK1);

			ZoneCoord_t myX     = pSlayer->getX();
			ZoneCoord_t myY     = pSlayer->getY();
			ZoneCoord_t targetX = pTargetCreature->getX();
			ZoneCoord_t targetY = pTargetCreature->getY();

			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(0);

			_GCSkillToObjectOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
			_GCSkillToObjectOK2.setDuration (0);

			_GCSkillToObjectOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK3.setSkillType(SkillType);
			_GCSkillToObjectOK3.setTargetXY(targetX, targetY);

			_GCSkillToObjectOK4.setSkillType(SkillType);
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);

			_GCSkillToObjectOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setTargetObjectID (TargetObjectID);
			_GCSkillToObjectOK5.setDuration (0);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToObjectOK1);

			if (pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
			}

			pZone->broadcastPacket(targetX, targetY, &gcRemoveEffect);

			list< Creature*> cList;
			cList.push_back(pSlayer);
			cList.push_back(pTargetCreature);

			cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCSkillToObjectOK5 , cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToObjectOK3 , cList);
			pZone->broadcastPacket(targetX, targetY,  &_GCSkillToObjectOK4 , cList);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), pTargetCreature);
		}
	} 
	catch(Throwable & t)  
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void CurePoison::execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
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

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		// by sigi. 2002.12.3
		//SkillLevel_t      SkillLevel = pSkillSlot->getExpLevel();
		SkillLevel_t      SkillLevel = pSlayer->getINT()/2; //pSkillSlot->getExpLevel();

		bool bGreenPoison    = false; // GreenPoison을 치료할까의 여부
		bool bYellowPoison   = false; // YellowPoison을 치료할까의 여부
		bool bDarkBluePoison = false; // DarkBluePoison을 치료할까의 여부
		bool bGreenStalker   = false; // GreenStalker를 치료할까의 여부
		bool bEffected       = false; // 아무 독이나 걸려있으면 켠다.

		EffectPoison*                 pEffectPoison                 = NULL;
		EffectYellowPoisonToCreature* pEffectYellowPoisonToCreature = NULL;
		EffectDarkBluePoison*         pEffectDBP                   = NULL;
		EffectGreenStalker*           pEffectGreenStalker           = NULL;

		if (pSlayer->isEffect(Effect::EFFECT_CLASS_POISON)) 
		{
			pEffectPoison = (EffectPoison*)pSlayer->findEffect(Effect::EFFECT_CLASS_POISON);
			Assert(pEffectPoison != NULL);

			bGreenPoison = HitRoll::isSuccessCurePoison(75, SkillLevel, 10, pEffectPoison->getLevel());
			bEffected = true;
		}

		if (pSlayer->isEffect(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE)) 
		{
			pEffectYellowPoisonToCreature = (EffectYellowPoisonToCreature*)pSlayer->findEffect(Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE);
			Assert(pEffectYellowPoisonToCreature != NULL);

			bYellowPoison = HitRoll::isSuccessCurePoison(75, SkillLevel, 20, pEffectYellowPoisonToCreature->getLevel());
			bEffected = true;
		}

		if (pSlayer->isEffect(Effect::EFFECT_CLASS_DARKBLUE_POISON)) 
		{
			pEffectDBP = (EffectDarkBluePoison*)pSlayer->findEffect(Effect::EFFECT_CLASS_DARKBLUE_POISON);
			Assert(pEffectDBP != NULL);

			bDarkBluePoison = HitRoll::isSuccessCurePoison(75, SkillLevel, 30, pEffectDBP->getLevel());
			bEffected = true;
		}

		if (pSlayer->isEffect(Effect::EFFECT_CLASS_GREEN_STALKER)) 
		{
			pEffectGreenStalker = (EffectGreenStalker*)pSlayer->findEffect(Effect::EFFECT_CLASS_GREEN_STALKER);
			Assert(pEffectGreenStalker != NULL);

			bGreenStalker = HitRoll::isSuccessCurePoison(75, SkillLevel, 40, pEffectGreenStalker->getLevel());
			bEffected = true;
		}

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);

		// 마나가 있고, 시간이 됐고, 거리가 적당하며,
		// 독이 하나라도 걸려있어야 한다.
		if (bManaCheck && bTimeCheck && bRangeCheck && bEffected)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToSelfOK1);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			// 각각의 독마다 치료를 하고,
			// 패킷에다 이펙트 삭제하라고 더한다.
			GCRemoveEffect gcRemoveEffect;
			gcRemoveEffect.setObjectID(pSlayer->getObjectID());

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

			// 경험치를 올린다.
			SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));
			Exp_t ExpUp = 10* (Grade + 1);
			shareAttrExp(pSlayer, ExpUp, 1, 1, 8, _GCSkillToSelfOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToSelfOK1);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToSelfOK1);

			ZoneCoord_t myX = pSlayer->getX();
			ZoneCoord_t myY = pSlayer->getY();

			_GCSkillToSelfOK1.setSkillType(SkillType);
			_GCSkillToSelfOK1.setCEffectID(CEffectID);
			_GCSkillToSelfOK1.setDuration(0);

			_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToSelfOK2.setSkillType(SkillType);
			_GCSkillToSelfOK2.setDuration (0);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToSelfOK1);
			pZone->broadcastPacket(myX, myY,  &_GCSkillToSelfOK2 , pSlayer);

			// 기술이 풀렸다는 것을 알려준다아.
			pZone->broadcastPacket(myX, myY, &gcRemoveEffect);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), NULL);
		}
	} 
	catch(Throwable & t)  
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH

}

CurePoison g_CurePoison;
