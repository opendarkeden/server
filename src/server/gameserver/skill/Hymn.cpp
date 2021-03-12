//////////////////////////////////////////////////////////////////////////////
// Filename    : Hymn.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Hymn.h"
#include "EffectHymn.h"
#include "EffectProtectionFromCurse.h"

#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToObjectOK6.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCRemoveEffect.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void Hymn::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
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

		// NPC는 공격할 수 없다.
		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !canAttack( pSlayer, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;
		GCSkillToObjectOK6 _GCSkillToObjectOK6;

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessCurse(pSkillInfo->getLevel()/2, pTargetCreature->getResist(MAGIC_DOMAIN_CURSE));
		bool bHitRoll2   = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
		bool bCanHit     = canHit(pSlayer, pTargetCreature, SkillType);
		bool bEffected   = pTargetCreature->isFlag(Effect::EFFECT_CLASS_HYMN);
		bool bPK         = verifyPK(pSlayer, pTargetCreature);

		ZoneCoord_t targetX = pTargetCreature->getX();
		ZoneCoord_t targetY = pTargetCreature->getY();
		ZoneCoord_t myX     = pSlayer->getX();
		ZoneCoord_t myY     = pSlayer->getY();

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bHitRoll2 && bCanHit && !bEffected && bPK)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToObjectOK1);

        	bool bCanSeeCaster = canSee(pTargetCreature, pSlayer);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			// 이펙트 오브젝트를 생성해 붙인다.
			EffectHymn* pEffect = new EffectHymn(pTargetCreature);
			pEffect->setDeadline(output.Duration);
			pEffect->setLevel(pSkillInfo->getLevel()/2);
			pEffect->setDamagePenalty(output.Damage);
			pEffect->setToHitPenalty(output.Damage);
			pTargetCreature->addEffect(pEffect);
			pTargetCreature->setFlag(Effect::EFFECT_CLASS_HYMN);

			// 능력치를 계산해서 보내준다.
			if (pTargetCreature->isVampire())
			{
				Vampire* pTargetVampire = dynamic_cast<Vampire*>(pTargetCreature);
				VAMPIRE_RECORD prev;

				pTargetVampire->getVampireRecord(prev);
				pTargetVampire->initAllStat();
				if (bCanSeeCaster)
				{
					pTargetVampire->addModifyInfo(prev, _GCSkillToObjectOK2);
				}
				else
				{
					pTargetVampire->addModifyInfo(prev, _GCSkillToObjectOK6);
				}
			}
			else if (pTargetCreature->isMonster())
			{
				Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
				pTargetMonster->initAllStat();
			}
			else if (pTargetCreature->isSlayer())
			{
				Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);

				if (bCanSeeCaster) 
				{
					SLAYER_RECORD prev;
					pTargetSlayer->getSlayerRecord(prev);
					pTargetSlayer->initAllStat();
					pTargetSlayer->addModifyInfo(prev, _GCSkillToObjectOK2);
				} 
				else 
				{
					SLAYER_RECORD prev;
					pTargetSlayer->getSlayerRecord(prev);
					pTargetSlayer->initAllStat();
					pTargetSlayer->addModifyInfo(prev, _GCSkillToObjectOK6);
				}
			}
			else if (pTargetCreature->isOusters())
			{
				Ousters* pTargetOusters = dynamic_cast<Ousters*>(pTargetCreature);

				if (bCanSeeCaster) 
				{
					OUSTERS_RECORD prev;
					pTargetOusters->getOustersRecord(prev);
					pTargetOusters->initAllStat();
					pTargetOusters->addModifyInfo(prev, _GCSkillToObjectOK2);
				} 
				else 
				{
					OUSTERS_RECORD prev;
					pTargetOusters->getOustersRecord(prev);
					pTargetOusters->initAllStat();
					pTargetOusters->addModifyInfo(prev, _GCSkillToObjectOK6);
				}
			}
			else Assert(false);
								
			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(output.Duration);
		
			_GCSkillToObjectOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
			_GCSkillToObjectOK2.setDuration(output.Duration);
		
			_GCSkillToObjectOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK3.setSkillType(SkillType);
			_GCSkillToObjectOK3.setTargetXY (targetX, targetY);
			
			_GCSkillToObjectOK4.setSkillType(SkillType);
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK4.setDuration(output.Duration);
			
			_GCSkillToObjectOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setTargetObjectID (TargetObjectID);
			_GCSkillToObjectOK5.setDuration(output.Duration);
			
			_GCSkillToObjectOK6.setXY(myX, myY);
			_GCSkillToObjectOK6.setSkillType(SkillType);
			_GCSkillToObjectOK6.setDuration(output.Duration);

			if (bCanSeeCaster) // 10은 땜빵 수치다.
			{
				computeAlignmentChange(pTargetCreature, 10, pSlayer, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
			}
			else // 10은 땜빵 수치다.
			{
				computeAlignmentChange(pTargetCreature, 10, pSlayer, &_GCSkillToObjectOK6, &_GCSkillToObjectOK1);
			}
								
			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pSlayer);
			cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCSkillToObjectOK5, cList);

			pZone->broadcastPacket(myX, myY, &_GCSkillToObjectOK3, cList);
			pZone->broadcastPacket(targetX, targetY, &_GCSkillToObjectOK4, cList);

			// Send Packet
			pPlayer->sendPacket(&_GCSkillToObjectOK1);

			if (pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				if (pTargetPlayer == NULL)
				{
					//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
					return;
				}

				if (bCanSeeCaster) pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
				else pTargetPlayer->sendPacket(&_GCSkillToObjectOK6);
			}
			else if (pTargetCreature->isMonster())
			{
				Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
				pTargetMonster->addEnemy(pSlayer);
			}

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(TargetObjectID);
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_HYMN);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(targetX, targetY, &gcAddEffect);
			
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}



Hymn g_Hymn;
