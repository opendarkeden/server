//////////////////////////////////////////////////////////////////////////////
// Filename    : Resurrect.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Resurrect.h"
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
void Resurrect::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
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

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// 슬레이어만을 되살릴 수 있다.
		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !pTargetCreature->isSlayer()
			|| ( g_pConfig->hasKey("Hardcore") && g_pConfig->getPropertyInt("Hardcore")!=0 ) )
		{
			executeSkillFailException(pSlayer, getSkillType());
			return;
		}

		Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);
		Assert(pTargetSlayer != NULL);

		// 타겟에게 코마 이펙트가 걸려있지 않거나, 죽은 상태가 아니라면 쓸 수 없다.
		if (!pTargetSlayer->isFlag(Effect::EFFECT_CLASS_COMA) || !pTargetSlayer->isDead())
		{
			executeSkillFailException(pSlayer, getSkillType());
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

		ZoneCoord_t myX     = pSlayer->getX();
		ZoneCoord_t myY     = pSlayer->getY();
		ZoneCoord_t targetX = pTargetCreature->getX();
		ZoneCoord_t targetY = pTargetCreature->getY();
		
		int  RequiredMP    = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck    = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck    = verifyRunTime(pSkillSlot);
		bool bRangeCheck   = verifyDistance(pSlayer, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll      = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bCanResurrect = false;

		EffectComa* pEffectComa = (EffectComa*)(pTargetCreature->findEffect(Effect::EFFECT_CLASS_COMA));
		Assert(pEffectComa != NULL);

		if (pEffectComa->canResurrect())
		{
			bCanResurrect = true;
		}

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bCanResurrect)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToObjectOK1);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			// 타겟의 이펙트 매니저에서 코마 이펙트를 삭제한다.
			pTargetCreature->deleteEffect(Effect::EFFECT_CLASS_COMA);
			pTargetCreature->removeFlag(Effect::EFFECT_CLASS_COMA);

			// 코마 이펙트가 날아갔다고 알려준다.
			GCRemoveEffect gcRemoveEffect;
			gcRemoveEffect.setObjectID(pTargetSlayer->getObjectID());
			gcRemoveEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_COMA);
			pZone->broadcastPacket(targetX, targetY, &gcRemoveEffect);

			// 이펙트 정보를 다시 보내준다. by sigi. 2002.11.14
			pTargetSlayer->getEffectManager()->sendEffectInfo(pTargetSlayer, pZone, pTargetSlayer->getX(), pTargetSlayer->getY());

			// 부활 아르바이드를 방지하기 위해서 Aftermath 이펙트를 붙인다.
			// 2002.11.19 장홍창 
			if (pTargetSlayer->isFlag(Effect::EFFECT_CLASS_KILL_AFTERMATH))
			{
				Effect *pEffect = pTargetSlayer->findEffect(Effect::EFFECT_CLASS_KILL_AFTERMATH);
				EffectKillAftermath* pEffectKillAftermath = dynamic_cast<EffectKillAftermath*>(pEffect);
				pEffectKillAftermath->setDeadline(5*600);
			}
			else
			{
				EffectKillAftermath* pEffectKillAftermath = new EffectKillAftermath(pTargetSlayer);
				pEffectKillAftermath->setDeadline(5*600);
				pTargetSlayer->addEffect(pEffectKillAftermath);
				pTargetSlayer->setFlag(Effect::EFFECT_CLASS_KILL_AFTERMATH);
				pEffectKillAftermath->create(pTargetSlayer->getName());
			}

			// 대상의 체력을 10%만 채운다.
			HP_t CurrentHP = getPercentValue(pTargetSlayer->getHP(ATTR_MAX), 10);
			pTargetSlayer->setHP(CurrentHP, ATTR_CURRENT);
			pTargetSlayer->setMP(0, ATTR_CURRENT);

			// 주위에 체력이 채워졌다는 사실을 알린다. 
			GCStatusCurrentHP gcStatusCurrentHP;
			gcStatusCurrentHP.setObjectID(pTargetSlayer->getObjectID());
			gcStatusCurrentHP.setCurrentHP(pTargetSlayer->getHP(ATTR_CURRENT));
			pZone->broadcastPacket(targetX, targetY, &gcStatusCurrentHP);

			// 경험치를 올려준다.
			shareAttrExp(pSlayer, pSkillInfo->getPoint(), 1, 1, 8, _GCSkillToObjectOK1);
			increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToObjectOK1);
			increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToObjectOK1);
			increaseAlignment(pSlayer, pTargetCreature, _GCSkillToObjectOK1);

			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(0);
			
			_GCSkillToObjectOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
			_GCSkillToObjectOK2.setDuration(0);
			_GCSkillToObjectOK2.addShortData(MODIFY_CURRENT_MP, pTargetSlayer->getMP(ATTR_CURRENT));
		
			_GCSkillToObjectOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK3.setSkillType(SkillType);
			_GCSkillToObjectOK3.setTargetXY(targetX, targetY);
		
			_GCSkillToObjectOK4.setSkillType(SkillType);
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);

			_GCSkillToObjectOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK5.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setDuration(0);
			
			pPlayer->sendPacket(&_GCSkillToObjectOK1);
		
			Player* pTargetPlayer = pTargetSlayer->getPlayer();
			Assert(pTargetPlayer != NULL);
			pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);

			list<Creature*> cList;
			cList.push_back(pSlayer);
			cList.push_back(pTargetCreature);

			cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCSkillToObjectOK5, cList);
			
			pZone->broadcastPacket(myX, myY, &_GCSkillToObjectOK3 , cList);
			pZone->broadcastPacket(targetX, targetY, &_GCSkillToObjectOK4 , cList);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), pTargetCreature);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	__END_CATCH
}

Resurrect g_Resurrect;
