//////////////////////////////////////////////////////////////////////////////
// Filename    : SoulRebirth.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SoulRebirth.h"
#include "EffectComa.h"
#include "EffectKillAftermath.h"
#include "Properties.h"

#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCStatusCurrentHP.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void SoulRebirth::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot * pOustersSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;

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

		// 아우스터즈만 되살릴 수 있다.
		if (pTargetCreature==NULL
			|| !pTargetCreature->isOusters()
			|| ( g_pConfig->hasKey("Hardcore") && g_pConfig->getPropertyInt("Hardcore")!=0 ) )
		{
			executeSkillFailException(pOusters, getSkillType());
			return;
		}

		Ousters* pTargetOusters = dynamic_cast<Ousters*>(pTargetCreature);
		Assert(pTargetOusters != NULL);

		// 타겟에게 코마 이펙트가 걸려있지 않거나, 죽은 상태가 아니라면 쓸 수 없다.
		if (!pTargetOusters->isFlag(Effect::EFFECT_CLASS_COMA) || !pTargetOusters->isDead())
		{
			executeSkillFailException(pOusters, getSkillType());
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;

		SkillType_t       SkillType  = pOustersSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		ZoneCoord_t myX     = pOusters->getX();
		ZoneCoord_t myY     = pOusters->getY();
		ZoneCoord_t targetX = pTargetCreature->getX();
		ZoneCoord_t targetY = pTargetCreature->getY();
		
		SkillInput input(pOusters, pOustersSkillSlot);
		SkillOutput output;
		computeOutput(input, output);

		int HealRatio = 10;

		OustersSkillSlot* pPassiveSkill = pOusters->getSkill( SKILL_SOUL_REBIRTH_MASTERY );
		if ( pPassiveSkill != NULL )
		{
			output.Range += pPassiveSkill->getExpLevel()/10;
			if ( pOustersSkillSlot->getExpLevel() > 15 )
				output.Tick += pPassiveSkill->getExpLevel()*2;

			if ( pPassiveSkill->getExpLevel() >= 30 ) HealRatio = 50;
			else if ( pPassiveSkill->getExpLevel() >= 26 ) HealRatio = 40;
			else if ( pPassiveSkill->getExpLevel() >= 16 ) HealRatio = 25;
		}

		int  RequiredMP    = (int)pSkillInfo->getConsumeMP() + pOustersSkillSlot->getExpLevel()*3/2;
		bool bManaCheck    = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck    = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck   = verifyDistance(pOusters, pTargetCreature, output.Range);
		bool bHitRoll      = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot);
		bool bCanSoulRebirth = false;

		EffectComa* pEffectComa = (EffectComa*)(pTargetCreature->findEffect(Effect::EFFECT_CLASS_COMA));
		Assert(pEffectComa != NULL);

		if (pEffectComa->canResurrect())
		{
			bCanSoulRebirth = true;
		}

		bool bCheckRatio = (rand()%100) < output.Tick;

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bCanSoulRebirth && bCheckRatio)
		{
			decreaseMana(pOusters, RequiredMP, _GCSkillToObjectOK1);

			// 타겟의 이펙트 매니저에서 코마 이펙트를 삭제한다.
			pTargetCreature->deleteEffect(Effect::EFFECT_CLASS_COMA);
			pTargetCreature->removeFlag(Effect::EFFECT_CLASS_COMA);

			// 코마 이펙트가 날아갔다고 알려준다.
			GCRemoveEffect gcRemoveEffect;
			gcRemoveEffect.setObjectID(pTargetOusters->getObjectID());
			gcRemoveEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_COMA);
			pZone->broadcastPacket(targetX, targetY, &gcRemoveEffect);

			pTargetOusters->getEffectManager()->sendEffectInfo(pTargetOusters, pZone, pTargetOusters->getX(), pTargetOusters->getY());

			if (pTargetOusters->isFlag(Effect::EFFECT_CLASS_KILL_AFTERMATH))
			{
				Effect *pEffect = pTargetOusters->findEffect(Effect::EFFECT_CLASS_KILL_AFTERMATH);
				EffectKillAftermath* pEffectKillAftermath = dynamic_cast<EffectKillAftermath*>(pEffect);
				pEffectKillAftermath->setDeadline(5*600);
			}
			else
			{
				EffectKillAftermath* pEffectKillAftermath = new EffectKillAftermath(pTargetOusters);
				pEffectKillAftermath->setDeadline(5*600);
				pTargetOusters->addEffect(pEffectKillAftermath);
				pTargetOusters->setFlag(Effect::EFFECT_CLASS_KILL_AFTERMATH);
				pEffectKillAftermath->create(pTargetOusters->getName());
			}

			// 대상의 체력을 10%만 채운다.
			HP_t CurrentHP = getPercentValue(pTargetOusters->getHP(ATTR_MAX), HealRatio);
			pTargetOusters->setHP(CurrentHP, ATTR_CURRENT);
//			pTargetOusters->setMP(0, ATTR_CURRENT);

			// 주위에 체력이 채워졌다는 사실을 알린다. 
			GCStatusCurrentHP gcStatusCurrentHP;
			gcStatusCurrentHP.setObjectID(pTargetOusters->getObjectID());
			gcStatusCurrentHP.setCurrentHP(pTargetOusters->getHP(ATTR_CURRENT));
			pZone->broadcastPacket(targetX, targetY, &gcStatusCurrentHP);

			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(0);
			
			_GCSkillToObjectOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
			_GCSkillToObjectOK2.setDuration(0);
//			_GCSkillToObjectOK2.addShortData(MODIFY_CURRENT_MP, pTargetOusters->getMP(ATTR_CURRENT));
		
			_GCSkillToObjectOK3.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK3.setSkillType(SkillType);
			_GCSkillToObjectOK3.setTargetXY(targetX, targetY);
		
			_GCSkillToObjectOK4.setSkillType(SkillType);
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);

			_GCSkillToObjectOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK5.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setDuration(0);
			
			pPlayer->sendPacket(&_GCSkillToObjectOK1);
		
			Player* pTargetPlayer = pTargetOusters->getPlayer();
			Assert(pTargetPlayer != NULL);
			pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);

			list<Creature*> cList;
			cList.push_back(pOusters);
			cList.push_back(pTargetCreature);

			cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCSkillToObjectOK5, cList);
			
			pZone->broadcastPacket(myX, myY, &_GCSkillToObjectOK3 , cList);
			pZone->broadcastPacket(targetX, targetY, &_GCSkillToObjectOK4 , cList);

			pOustersSkillSlot->setRunTime(output.Delay);
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	__END_CATCH
}

SoulRebirth g_SoulRebirth;
