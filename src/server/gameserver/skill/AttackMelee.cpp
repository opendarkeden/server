//////////////////////////////////////////////////////////////////////////////
// Filename    : AttackMelee.cpp
// Written by  : elca@ewestsoft.com
// Description : 기본 공격
//////////////////////////////////////////////////////////////////////////////

#include "AttackMelee.h"
#include "CrossCounter.h"

#include "EffectPoison.h"
#include "EffectProtectionFromPoison.h"

#include "Gpackets/GCAttackMeleeOK1.h"
#include "Gpackets/GCAttackMeleeOK2.h"
#include "Gpackets/GCAttackMeleeOK3.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Gpackets/GCAddEffect.h"


//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트
//////////////////////////////////////////////////////////////////////////////
void AttackMelee::execute(Slayer* pSlayer, ObjectID_t TargetObjectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "Begin (slayer)" << endl;

	Assert(pSlayer != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Assert(pPlayer != NULL);

		Zone* pZone = pSlayer->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NPC를 공격할 수는 없다.
		if (pTargetCreature==NULL	// NoSuch제거 때문에.. by sigi. 2002.5.2
			|| !canAttack( pSlayer, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;
			return;
		}

		// 슬레이어는 맨손이면 공격할 수 없다. by sigi. 2002.6.29
		/*
		Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		
		if (pWeapon==NULL)
		{
			executeSkillFailException(pSlayer, getSkillType());
			return;
		}
		*/
		bool bIncreaseDomainExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);

		// 기본 공격 스킬 슬랏을 받아온다.
		SkillSlot* pSkillSlot = pSlayer->hasSkill(SKILL_ATTACK_MELEE);
		Assert(pSkillSlot != NULL);

		GCAttackMeleeOK1 _GCAttackMeleeOK1;
		GCAttackMeleeOK2 _GCAttackMeleeOK2;
		GCAttackMeleeOK3 _GCAttackMeleeOK3;

		bool     bCriticalHit = false;
		Damage_t Damage       = computeDamage(pSlayer, pTargetCreature, 0, bCriticalHit);
		bool     bTimeCheck   = verifyRunTime(pSkillSlot);
		bool     bRangeCheck  = verifyDistance(pSlayer, pTargetCreature, 1);
		bool     bHitRoll     = HitRoll::isSuccess(pSlayer, pTargetCreature);
		bool     bCanHit      = canHit(pSlayer, pTargetCreature, SKILL_ATTACK_MELEE);
		bool     bPK          = verifyPK(pSlayer, pTargetCreature);
		
		if (bTimeCheck && bRangeCheck && bHitRoll && bCanHit && bPK)
		{
			CheckCrossCounter(pSlayer, pTargetCreature, Damage);

			Exp_t Point = 1;

			// 데미지를 주고, 아이템 내구도를 떨어뜨린다.
			setDamage(pTargetCreature, Damage, pSlayer, SKILL_ATTACK_MELEE, &_GCAttackMeleeOK2, &_GCAttackMeleeOK1);
			computeAlignmentChange(pTargetCreature, Damage, pSlayer, &_GCAttackMeleeOK2, &_GCAttackMeleeOK1);
			decreaseDurability(pSlayer, pTargetCreature, NULL, &_GCAttackMeleeOK1, &_GCAttackMeleeOK2);

			// 크리티컬 히트라면 상대방을 뒤로 물러나게 한다.
			if (bCriticalHit)
			{
				knockbackCreature(pZone, pTargetCreature, pSlayer->getX(), pSlayer->getY());
			}

			// 타겟이 슬레이어가 아니라면 경험치를 올려준다.
			if (!pTargetCreature->isSlayer())
			{
				Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);

				if (pWeapon != NULL)
				{
					if ( bIncreaseDomainExp )
					{
						if (pWeapon->getItemClass() == Item::ITEM_CLASS_BLADE) 
						{
							shareAttrExp(pSlayer, Damage , 8, 1, 1, _GCAttackMeleeOK1);
							increaseDomainExp(pSlayer, SKILL_DOMAIN_BLADE, Point, _GCAttackMeleeOK1, pTargetCreature->getLevel());
						}
						else if (pWeapon->getItemClass() == Item::ITEM_CLASS_SWORD) 
						{
							shareAttrExp(pSlayer, Damage, 8, 1, 1, _GCAttackMeleeOK1);
							increaseDomainExp(pSlayer, SKILL_DOMAIN_SWORD, Point, _GCAttackMeleeOK1, pTargetCreature->getLevel());
						}
						else if (pWeapon->getItemClass() == Item::ITEM_CLASS_CROSS) 
						{
							// 십자가를 들고 있을 경우 Heal 계열의 경험치를 올려준다.
							shareAttrExp(pSlayer, Damage, 1, 1, 8, _GCAttackMeleeOK1);
							increaseDomainExp(pSlayer, SKILL_DOMAIN_HEAL, Point, _GCAttackMeleeOK1, pTargetCreature->getLevel());
						} 
						else if (pWeapon->getItemClass() == Item::ITEM_CLASS_MACE) 
						{
							// 메이스를 들고 있을 경우 Enchant 계열의 경험치를 올려준다.
							shareAttrExp(pSlayer, Damage, 1, 1, 8, _GCAttackMeleeOK1);
							increaseDomainExp(pSlayer, SKILL_DOMAIN_ENCHANT, Point, _GCAttackMeleeOK1, pTargetCreature->getLevel());
						}
						else 
						{
							// 다른 계열의 무기를 들고, AttackMelee를 하는 것은 불법(?)이다.
							Assert(false);
						}
					}
				}
				else
				{
					// 아무 무기도 들지 않고, 공격을 할 경우, 능력치 경험치만 약간 올려준다.
					shareAttrExp(pSlayer, Damage , 1, 1, 1, _GCAttackMeleeOK1);
				}

				increaseAlignment(pSlayer, pTargetCreature, _GCAttackMeleeOK1);
			}

			_GCAttackMeleeOK3.setObjectID(pSlayer->getObjectID());
			_GCAttackMeleeOK3.setTargetObjectID (TargetObjectID);

			_GCAttackMeleeOK1.setObjectID(TargetObjectID);

			pPlayer->sendPacket(&_GCAttackMeleeOK1);

			if (pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				if (pTargetPlayer != NULL) 
				{
					_GCAttackMeleeOK2.setObjectID(pSlayer->getObjectID());
					pTargetPlayer->sendPacket(&_GCAttackMeleeOK2);
				}
			} 
			else if (pTargetCreature->isMonster())
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				pMonster->addEnemy(pSlayer);

				// 이 부분은 새로 만들어진 부분을 생각해서 고쳐져야 하는데...
				// 마스터는 딜레이없다.
				if (!pMonster->isMaster()
#ifdef __UNDERWORLD__
						&& !pMonster->isUnderworld() && pMonster->getMonsterType() != 599
#endif
				)
				{
					Timeval NextTurn = pMonster->getNextTurn();
					Timeval DelayTurn;
					DelayTurn.tv_sec  = 0;
					DelayTurn.tv_usec = 200000;
					Timeval NewTurn   = NextTurn + DelayTurn;
					pMonster->setNextTurn(NewTurn);
				}
			}

			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pSlayer);
			pZone->broadcastPacket(pSlayer->getX(), pSlayer->getY(),  &_GCAttackMeleeOK3 , cList);

			pSkillSlot->setRunTime();
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, getSkillType(), pTargetCreature);
		}
    } 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
        //cout << t.toString();
    }

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트
//////////////////////////////////////////////////////////////////////////////
void AttackMelee::execute(Vampire* pVampire, ObjectID_t TargetObjectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "Begin (vampire)" << endl;

	Assert(pVampire != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);
	
		// NoSuch제거 때문에. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !canAttack( pVampire, pTargetCreature )
			)
		{
			executeSkillFailException(pVampire, getSkillType());
			return;
		}


		GCAttackMeleeOK1 _GCAttackMeleeOK1;
		GCAttackMeleeOK2 _GCAttackMeleeOK2;
		GCAttackMeleeOK3 _GCAttackMeleeOK3;

		// 스킬 슬랏을 받아온다.
		VampireSkillSlot* pSkillSlot = pVampire->hasSkill(SKILL_ATTACK_MELEE);
		Assert(pSkillSlot != NULL);

		bool bCriticalHit = false;

		Damage_t Damage = computeDamage(pVampire, pTargetCreature, 0, bCriticalHit);

		bool bTimeCheck         = verifyRunTime(pSkillSlot);
		bool bRangeCheck        = verifyDistance(pVampire, pTargetCreature, 1);
		bool bHitRoll           = HitRoll::isSuccess(pVampire, pTargetCreature);
		bool bCanHit            = canHit(pVampire, pTargetCreature, SKILL_ATTACK_MELEE);
		bool bPK                = verifyPK(pVampire, pTargetCreature);

		if (bTimeCheck && bRangeCheck && bHitRoll && bCanHit && bPK)
		{
			CheckCrossCounter(pVampire, pTargetCreature, Damage);

			// 데미지를 주고, 내구도를 떨어뜨린다.
			setDamage(pTargetCreature, Damage, pVampire, SKILL_ATTACK_MELEE, &_GCAttackMeleeOK2, &_GCAttackMeleeOK1);
			computeAlignmentChange(pTargetCreature, Damage, pVampire, &_GCAttackMeleeOK2, &_GCAttackMeleeOK1);
			decreaseDurability(pVampire, pTargetCreature, NULL, &_GCAttackMeleeOK1, &_GCAttackMeleeOK2);

			// 크리티컬 히트라면 상대방을 뒤로 물러나게 한다.
			if (bCriticalHit)
			{
				knockbackCreature(pZone, pTargetCreature, pVampire->getX(), pVampire->getY());
			}

			increaseAlignment(pVampire, pTargetCreature, _GCAttackMeleeOK1);

			// 상대가 죽었다면 경험치를 좀 올려준다.
			if (pTargetCreature->isDead())
			{
				int exp = computeCreatureExp(pTargetCreature, KILL_EXP);
				shareVampExp(pVampire, exp, _GCAttackMeleeOK1);
			}

			_GCAttackMeleeOK1.setObjectID(TargetObjectID);

			_GCAttackMeleeOK3.setObjectID(pVampire->getObjectID());
			_GCAttackMeleeOK3.setTargetObjectID (TargetObjectID);

			pPlayer->sendPacket(&_GCAttackMeleeOK1);

			if (pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				if (pTargetPlayer != NULL) 
				{
					_GCAttackMeleeOK2.setObjectID(pVampire->getObjectID());
					pTargetPlayer->sendPacket(&_GCAttackMeleeOK2);
				}
			} 
			else if (pTargetCreature->isMonster())
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				pMonster->addEnemy(pVampire);

				// 마스터는 딜레이없다.
				if (!pMonster->isMaster())
				{
					Timeval NextTurn = pMonster->getNextTurn();
					Timeval DelayTurn;
					DelayTurn.tv_sec = 0;
					DelayTurn.tv_usec = 200000;
					Timeval NewTurn = NextTurn + DelayTurn;
					pMonster->setNextTurn(NewTurn);
				}
			}

			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pVampire);
			pZone->broadcastPacket(pVampire->getX(), pVampire->getY(),  &_GCAttackMeleeOK3 , cList);

			pSkillSlot->setRunTime();
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(vampire)" << endl;

	__END_CATCH

}


//////////////////////////////////////////////////////////////////////////////
// 아우스터스 오브젝트
//////////////////////////////////////////////////////////////////////////////
void AttackMelee::execute(Ousters* pOusters, ObjectID_t TargetObjectID)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pOusters != NULL);

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
	
		// NoSuch제거 때문에. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| !canAttack( pOusters, pTargetCreature )
		   )
		{
			executeSkillFailException(pOusters, getSkillType());
			return;
		}

		GCAttackMeleeOK1 _GCAttackMeleeOK1;
		GCAttackMeleeOK2 _GCAttackMeleeOK2;
		GCAttackMeleeOK3 _GCAttackMeleeOK3;

		// 스킬 슬랏을 받아온다.
		OustersSkillSlot* pSkillSlot = pOusters->hasSkill(SKILL_ATTACK_MELEE);
		Assert(pSkillSlot != NULL);

		bool bCriticalHit = false;

		Damage_t Damage = computeDamage(pOusters, pTargetCreature, 0, bCriticalHit);

		bool bTimeCheck         = verifyRunTime(pSkillSlot);
		bool bRangeCheck        = verifyDistance(pOusters, pTargetCreature, 1);
		bool bHitRoll           = HitRoll::isSuccess(pOusters, pTargetCreature);
		bool bCanHit            = canHit(pOusters, pTargetCreature, SKILL_ATTACK_MELEE);
		bool bPK                = verifyPK(pOusters, pTargetCreature);

		if (bTimeCheck && bRangeCheck && bHitRoll && bCanHit && bPK)
		{
			Damage += computeElementalCombatSkill( pOusters, pTargetCreature, _GCAttackMeleeOK1 );
			CheckCrossCounter(pOusters, pTargetCreature, Damage);

			// 데미지를 주고, 내구도를 떨어뜨린다.
			setDamage(pTargetCreature, Damage, pOusters, SKILL_ATTACK_MELEE, &_GCAttackMeleeOK2, &_GCAttackMeleeOK1);
			computeAlignmentChange(pTargetCreature, Damage, pOusters, &_GCAttackMeleeOK2, &_GCAttackMeleeOK1);
			decreaseDurability(pOusters, pTargetCreature, NULL, &_GCAttackMeleeOK1, &_GCAttackMeleeOK2);

			// 크리티컬 히트라면 상대방을 뒤로 물러나게 한다.
			if (bCriticalHit)
			{
				knockbackCreature(pZone, pTargetCreature, pOusters->getX(), pOusters->getY());
			}

			increaseAlignment(pOusters, pTargetCreature, _GCAttackMeleeOK1);

			// 상대가 죽었다면 경험치를 좀 올려준다.
			if (pTargetCreature->isDead())
			{
				int exp = computeCreatureExp(pTargetCreature, 100, pOusters);
				shareOustersExp(pOusters, exp, _GCAttackMeleeOK1);
			}

			_GCAttackMeleeOK1.setObjectID(TargetObjectID);

			_GCAttackMeleeOK3.setObjectID(pOusters->getObjectID());
			_GCAttackMeleeOK3.setTargetObjectID (TargetObjectID);

			pPlayer->sendPacket(&_GCAttackMeleeOK1);

			if (pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();
				if (pTargetPlayer != NULL) 
				{
					_GCAttackMeleeOK2.setObjectID(pOusters->getObjectID());
					pTargetPlayer->sendPacket(&_GCAttackMeleeOK2);
				}
			} 
			else if (pTargetCreature->isMonster())
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				pMonster->addEnemy(pOusters);

				// 마스터는 딜레이없다.
				if (!pMonster->isMaster())
				{
					Timeval NextTurn = pMonster->getNextTurn();
					Timeval DelayTurn;
					DelayTurn.tv_sec = 0;
					DelayTurn.tv_usec = 200000;
					Timeval NewTurn = NextTurn + DelayTurn;
					pMonster->setNextTurn(NewTurn);
				}
			}

			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pOusters);
			pZone->broadcastPacket(pOusters->getX(), pOusters->getY(),  &_GCAttackMeleeOK3 , cList);

			pSkillSlot->setRunTime();
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(vampire)" << endl;

	__END_CATCH

}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 오브젝트
//////////////////////////////////////////////////////////////////////////////
void AttackMelee::execute(Monster* pMonster, Creature* pEnemy)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(monster)" << endl;

	Assert(pMonster != NULL);
	Assert(pEnemy != NULL);

	try 
	{ 
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		if (pMonster->isFlag(Effect::EFFECT_CLASS_HIDE))
		{
			//cout << "Monster cannot use skill while hiding." << endl;
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(monster)" << endl;
			return;
		}
		if (pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY))
		{
			addVisibleCreature(pZone, pMonster, true);
		}

		GCAttackMeleeOK2 _GCAttackMeleeOK2;
		GCAttackMeleeOK3 _GCAttackMeleeOK3;

		bool bCriticalHit = false;

		Damage_t Damage = computeDamage(pMonster, pEnemy, 0, bCriticalHit);

		bool bRangeCheck        = verifyDistance(pMonster, pEnemy, pMonster->getMeleeRange());
		bool bHitRoll           = HitRoll::isSuccess(pMonster, pEnemy);
		bool bCanHit            = canHit(pMonster, pEnemy, SKILL_ATTACK_MELEE);

		if (bRangeCheck && bHitRoll && bCanHit)
		{
			CheckCrossCounter(pMonster, pEnemy, Damage);

			// 데미지를 주고, 내구도를 떨어뜨린다.
			setDamage(pEnemy, Damage, pMonster, SKILL_ATTACK_MELEE, &_GCAttackMeleeOK2);
			decreaseDurability(pMonster, pEnemy, NULL, NULL, &_GCAttackMeleeOK2);

			// 크리티컬 히트라면 상대방을 뒤로 물러나게 한다.
			if (bCriticalHit)
			{
				knockbackCreature(pZone, pEnemy, pMonster->getX(), pMonster->getY());
			}

			_GCAttackMeleeOK3.setObjectID(pMonster->getObjectID());
			_GCAttackMeleeOK3.setTargetObjectID (pEnemy->getObjectID());

			if (pEnemy->isPC()) 
			{
				Player* pTargetPlayer = pEnemy->getPlayer();
				Assert(pTargetPlayer != NULL);

				_GCAttackMeleeOK2.setObjectID(pMonster->getObjectID());

				pTargetPlayer->sendPacket(&_GCAttackMeleeOK2);
			}
			else if (pEnemy->isMonster())
			{
				Monster* pTargetMonster = dynamic_cast<Monster*>(pEnemy);
				pTargetMonster->addEnemy(pMonster);
			}

			list<Creature *> cList;
			cList.push_back(pEnemy);

			cList.push_back(pMonster);
			pZone->broadcastPacket(pMonster->getX(), pMonster->getY(),  &_GCAttackMeleeOK3 , cList);
		} 
		else 
		{
			executeSkillFailNormal(pMonster, getSkillType(), pEnemy);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(monster)" << endl;

	__END_CATCH
}

AttackMelee g_AttackMelee;
