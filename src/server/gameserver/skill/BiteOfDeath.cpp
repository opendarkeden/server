//////////////////////////////////////////////////////////////////////////////
// Filename    : BiteOfDeath.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "BiteOfDeath.h"
#include "RankBonus.h"

#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToObjectOK6.h"
#include "Gpackets/GCStatusCurrentHP.h"
#include "Reflection.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void BiteOfDeath::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY
		
	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pVampire != NULL);
	
	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NPC는 공격할 수 없다.
		// 저주 면역. by sigi. 2002.9.13
		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !canAttack( pVampire, pTargetCreature )
			|| pTargetCreature->isNPC()
			|| !pVampire->isFlag(Effect::EFFECT_CLASS_TRANSFORM_TO_WERWOLF)
			|| pTargetCreature->isDead()
			|| pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA))
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;
		GCSkillToObjectOK6 _GCSkillToObjectOK6;

		SkillType_t SkillType  = getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		int  RequiredMP  = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck  = hasEnoughMana(pVampire, RequiredMP);
		bool bRangeCheck = verifyDistance(pVampire, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessBloodDrain(pVampire, pTargetCreature);
		bool bCanHit     = canHit(pVampire, pTargetCreature, SkillType);
		bool bPK         = verifyPK(pVampire, pTargetCreature);
		bool bMaster	 = false;

		if ( pTargetCreature->isMonster() )
		{
			Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
			Assert( pTargetMonster != NULL );

			if ( pTargetMonster->isMaster()
#ifdef __UNDERWORLD__
					|| pTargetMonster->isUnderworld() || pTargetMonster->getMonsterType() == 599
#endif
			)
			{
				bMaster = true;
			}
		}

		ZoneCoord_t targetX = pTargetCreature->getX();
		ZoneCoord_t targetY = pTargetCreature->getY();
		ZoneCoord_t myX     = pVampire->getX();
		ZoneCoord_t myY     = pVampire->getY();

		if (bManaCheck && bRangeCheck && bHitRoll && bCanHit && bPK && !bMaster)
		{
			decreaseMana(pVampire, RequiredMP, _GCSkillToObjectOK1);

        	bool bCanSeeCaster = canSee(pTargetCreature, pVampire);

			Exp_t Exp = computeCreatureExp(pTargetCreature, BLOODDRAIN_EXP + KILL_EXP);
			shareVampExp(pVampire, Exp, _GCSkillToObjectOK1);

			if (!pVampire->isFlag(Effect::EFFECT_CLASS_MEPHISTO))
			{
				HP_t HealPoint = (Exp==0? computeBloodDrainHealPoint(pTargetCreature, BLOODDRAIN_EXP) : Exp);
				HP_t CurrentHP = pVampire->getHP();
				HP_t MaxHP	   = pVampire->getHP(ATTR_MAX);
				HP_t NewHP     = min((int)MaxHP , (int)CurrentHP + (int)HealPoint);

				// 은 데미지 관련 처리를 해 준다.
				Silver_t newSilverDamage = max(0, (int)pVampire->getSilverDamage()-(int)HealPoint);
				pVampire->saveSilverDamage(newSilverDamage);
				_GCSkillToObjectOK1.addShortData(MODIFY_SILVER_DAMAGE, newSilverDamage);

				// 뱀파이어의 HP를 세팅한다.
				pVampire->setHP(NewHP);

				GCStatusCurrentHP gcStatusCurrentHP;
				gcStatusCurrentHP.setObjectID(pVampire->getObjectID());
				gcStatusCurrentHP.setCurrentHP(NewHP);
				pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcStatusCurrentHP, pVampire);

				_GCSkillToObjectOK1.addShortData(MODIFY_CURRENT_HP, NewHP);
			}


			// 타겟 쥑여뿐다.
			if ( pTargetCreature->isSlayer() )
			{
				Slayer* pSlayer = dynamic_cast<Slayer*>(pTargetCreature);
				pSlayer->setHP(0);
			}
			else if ( pTargetCreature->isVampire() )
			{
				Vampire* pTargetVampire = dynamic_cast<Vampire*>(pTargetCreature);
				pTargetVampire->setHP(0);
			}
			else if ( pTargetCreature->isOusters() )
			{
				Ousters* pOusters = dynamic_cast<Ousters*>(pTargetCreature);
				pOusters->setHP(0);
			}
			else if ( pTargetCreature->isMonster() )
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				HP_t decreaseHP = pMonster->getHP();
				pMonster->setHP(0);

				increaseFame( pVampire, decreaseHP );
				_GCSkillToObjectOK1.addLongData( MODIFY_FAME, pVampire->getFame() );
			}
			else Assert(false);

			affectKillCount( pVampire, pTargetCreature );

			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
		
			_GCSkillToObjectOK2.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
		
			_GCSkillToObjectOK3.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK3.setSkillType(SkillType);
			_GCSkillToObjectOK3.setTargetXY (targetX, targetY);
			
			_GCSkillToObjectOK4.setSkillType(SkillType);
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);
			
			_GCSkillToObjectOK5.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setTargetObjectID (TargetObjectID);
			
			_GCSkillToObjectOK6.setXY(myX, myY);
			_GCSkillToObjectOK6.setSkillType(SkillType);

			if (bCanSeeCaster) // 10은 땜빵 수치다.
			{
				computeAlignmentChange(pTargetCreature, 10, pVampire, &_GCSkillToObjectOK2, &_GCSkillToObjectOK1);
			}
			else // 10은 땜빵 수치다.
			{
				computeAlignmentChange(pTargetCreature, 10, pVampire, &_GCSkillToObjectOK6, &_GCSkillToObjectOK1);
			}
								
			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pVampire);
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
				pTargetMonster->addEnemy(pVampire);
			}
		} 
		else 
		{
			executeSkillFailNormal(pVampire, getSkillType(), pTargetCreature);
		}
	}
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

BiteOfDeath g_BiteOfDeath;
