//////////////////////////////////////////////////////////////////////////////
// Filename    : PlasmaRocketLauncher.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "PlasmaRocketLauncher.h"
#include "EffectPlasmaRocketLauncher.h"
#include "ItemUtil.h"
#include "GCSkillToObjectOK1.h"
#include "GCSkillToObjectOK2.h"
#include "GCSkillToObjectOK5.h"
#include "GCSkillToSelfOK1.h"
#include "GCSkillToSelfOK2.h"
#include "GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void PlasmaRocketLauncher::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

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
		if (pTargetCreature==NULL
			|| !canAttack(pSlayer, pTargetCreature )
		)
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}

		// 이펙트의 효과와 지속시간을 계산한다.
		SkillInput input(pSlayer, pSkillSlot);
		SkillOutput output;
		input.Range = getDistance(pSlayer->getX(), pSlayer->getY(), pTargetCreature->getX(), pTargetCreature->getY()); 
		computeOutput(input, output);

		Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if(pWeapon == NULL || isArmsWeapon(pWeapon) == false)
		{
			executeSkillFailException(pSlayer, getSkillType());
			return;
		}
		
		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;

		SkillType_t       SkillType  = pSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		
		// 페널티 값을 계산한다.
		int ToHitPenalty = getPercentValue(pSlayer->getToHit(), output.ToHit); 

		bool bIncreaseDomainExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll     = HitRoll::isSuccess(pSlayer, pTargetCreature, ToHitPenalty);
		bool bEffected   = false; //pTargetCreature->isFlag(Effect::EFFECT_CLASS_PLASMA_ROCKET_LAUNCHER);
		bool bPK         = verifyPK(pSlayer, pTargetCreature);
		bool bBulletCheck = (getRemainBullet(pWeapon) > 0) ? true : false;
		

		//cout << "remp : " << RequiredMP << ", bMcheck : " << bManaCheck << ", bTimeCheck : " << bTimeCheck << ", bRangeCheck : " << bRangeCheck << ", bHitroll : " << bHitRoll << ", bEffect : " << bEffected << ", bPK : " << bPK << endl;

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && !bEffected && bPK && bBulletCheck)
		{
			//cout << "check OK" << endl;
			// 마나를 줄인다.
			decreaseMana(pSlayer, RequiredMP, _GCSkillToObjectOK1);

			Bullet_t RemainBullet = 0;
			decreaseBullet(pWeapon);
			// 한발쓸때마다 저장할 필요 없다. by sigi. 2002.5.9
			//pWeapon->save(pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_RIGHTHAND, 0);
			RemainBullet = getRemainBullet(pWeapon);

			
			if (!pTargetCreature->isSlayer())
			{
				// 경험치를 올려준다.
				//SkillGrade Grade = g_pSkillInfoManager->getGradeByDomainLevel(pSlayer->getSkillDomainLevel(DomainType));
				//Exp_t      ExpUp = 10* (Grade + 1);
				//shareAttrExp(pSlayer, ExpUp, 1, 1, 8, _GCSkillToObjectOK1);
				//
				if (bIncreaseDomainExp )
				{
					increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToObjectOK1, pTargetCreature->getLevel());
				}

				increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToObjectOK1);
			}
		
			// 이펙트를 생성해서 붙인다.
			EffectPlasmaRocketLauncher* pEffect = new EffectPlasmaRocketLauncher(pTargetCreature);
			Assert(pEffect != NULL);
			pEffect->setNextTime(output.Duration);
			pEffect->setPoint(output.Damage); 
			pEffect->setUserObjectID(pSlayer->getObjectID());

			pTargetCreature->addEffect(pEffect);
			pTargetCreature->setFlag(Effect::EFFECT_CLASS_PLASMA_ROCKET_LAUNCHER);

			// 패킷을 준비해서 보낸다.
			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(output.Duration);

			_GCSkillToObjectOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
			_GCSkillToObjectOK2.setDuration (output.Duration);

			_GCSkillToObjectOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setTargetObjectID (TargetObjectID);
			_GCSkillToObjectOK5.setDuration (output.Duration);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToObjectOK1);

			if (pSlayer != pTargetCreature && pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);
				pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
			}
			else if (pTargetCreature->isMonster() )
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				if (pMonster != NULL ) pMonster->addEnemy(pSlayer);
			}

			list<Creature*> cList;
			cList.push_back(pSlayer);
			cList.push_back(pTargetCreature);
		
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(),  &_GCSkillToObjectOK5 , cList);

//			// 이펙트가 붙었다고 알려준다.
//			GCAddEffect gcAddEffect;
//			gcAddEffect.setObjectID(pTargetCreature->getObjectID());
//			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_PLASMA_ROCKET_LAUNCHER);
//			gcAddEffect.setDuration(output.Duration);
//			pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcAddEffect, pTargetCreature);
//
			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			//cout << "nonono~1" << endl;
			executeSkillFailNormal(pSlayer, getSkillType(), pTargetCreature);
		}
	} 
	catch (Throwable & t) 
	{
		//cout << "skill exception!!~1" << endl;
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

PlasmaRocketLauncher g_PlasmaRocketLauncher;
