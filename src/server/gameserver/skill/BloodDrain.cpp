//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodDrain.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "BloodDrain.h"
#include "EffectBloodDrain.h"
#include "EffectPrecedence.h"
#include "EffectDecreaseHP.h"
#include "GQuestManager.h"

#include "GCBloodDrainOK1.h"
#include "GCBloodDrainOK2.h"
#include "GCBloodDrainOK3.h"
#include "GCStatusCurrentHP.h"
#include "GCChangeDarkLight.h"

#include "LogClient.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void BloodDrain::execute(Vampire* pVampire, ObjectID_t TargetObjectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(vampire)" << endl;

	Assert(pVampire != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NPC는 공격할 수가 없다.
		// 면역 상태. by sigi. 2002.9.13
		// 무적상태 체크. by sigi.2002.9.5
		// 죽은 애는 피 빨 수 없다. by Sequoia.2003. 3. 20
		if (pTargetCreature==NULL		// NoSuch 제거. by sigi. 2002.5.2
			|| pTargetCreature->isNPC()
			|| pTargetCreature->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_BLOOD_DRAIN)
			|| !canAttack( pVampire, pTargetCreature )
			|| pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA)
			|| pTargetCreature->isDead()
		)
		{
			executeSkillFailException(pVampire, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(vampire)" << endl;
			return;
		}

		GCBloodDrainOK1 _GCBloodDrainOK1;
		GCBloodDrainOK2 _GCBloodDrainOK2;
		GCBloodDrainOK3 _GCBloodDrainOK3;

		Timeval CurrentTime;
		getCurrentTime(CurrentTime);

		bool bHitRoll    = HitRoll::isSuccessBloodDrain(pVampire, pTargetCreature);
		bool bCanHit     = canHit(pVampire, pTargetCreature, SKILL_BLOOD_DRAIN);
		bool bTimeCheck  = CurrentTime.tv_sec > 1 ? true : false;
		bool bRangeCheck = verifyDistance(pVampire, pTargetCreature, 2);
		bool bPK         = verifyPK(pVampire, pTargetCreature);

		if (bHitRoll && bCanHit && bTimeCheck && bRangeCheck && bPK)
		{
			// 슬레이어일 경우에만 이펙트 오브젝트를 생성한다.
			if (pTargetCreature->isSlayer())
			{
				EffectBloodDrain* pEffectBloodDrain = new EffectBloodDrain(pTargetCreature);
				pEffectBloodDrain->setLevel(pVampire->getLevel());
				pEffectBloodDrain->setDeadline(BLOODDRAIN_DURATION);	// 3일??
				pTargetCreature->addEffect(pEffectBloodDrain);
				pEffectBloodDrain->create(pTargetCreature->getName());
				_GCBloodDrainOK2.addShortData(MODIFY_EFFECT_STAT, Effect::EFFECT_CLASS_BLOOD_DRAIN);

				// 타겟이 뭐든 플래그는 건다.
				pTargetCreature->setFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);

				Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);
				SLAYER_RECORD prev;
				pTargetSlayer->getSlayerRecord(prev);
				pTargetSlayer->initAllStat();
				pTargetSlayer->sendRealWearingInfo();
				pTargetSlayer->addModifyInfo(prev, _GCBloodDrainOK2);

				// 로그를 남긴다.
				log(LOG_BLOODDRAINED, pTargetCreature->getName(), pVampire->getName());
			}
			// 아우스터즈의 경우엔..... -_-; 제한시간 없는 이펙트를 생성한다. 엄밀히 말해 제한시간이 없는 건 아니지만..
//			else if ( pTargetCreature->isOusters() )
//			{
//				EffectBloodDrain* pEffectBloodDrain = new EffectBloodDrain(pTargetCreature);
//				pEffectBloodDrain->setLevel(pVampire->getLevel());
//				pTargetCreature->addEffect(pEffectBloodDrain);
//				pEffectBloodDrain->create(pTargetCreature->getName());
//				_GCBloodDrainOK2.addShortData(MODIFY_EFFECT_STAT, Effect::EFFECT_CLASS_BLOOD_DRAIN);
//
//				// 타겟이 뭐든 플래그는 건다.
//				pTargetCreature->setFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
//
//				Sight_t oldSight = pTargetCreature->getSight();
//				Sight_t newSight = pTargetCreature->getEffectedSight();
//
//				if ( oldSight != newSight )
//				{
//					pTargetCreature->setSight(newSight);
//					pZone->updateScan(pTargetCreature, oldSight, pTargetCreature->getSight());
//					_GCBloodDrainOK2.addShortData(MODIFY_VISION, pTargetCreature->getSight());
//
//					GCChangeDarkLight gcChangeDarkLight;
//					gcChangeDarkLight.setDarkLevel(15);
//					gcChangeDarkLight.setLightLevel(newSight);
//					pTargetCreature->getPlayer()->sendPacket(&gcChangeDarkLight);
//				}
//			}

			// 타겟이 뭐든 플래그는 건다.
			pTargetCreature->setFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
			
			// 올릴 경험치량을 계산한다.
			Exp_t Exp = computeCreatureExp(pTargetCreature, BLOODDRAIN_EXP);

			int targetLevel = 0;
			int targetMaxHP = 0;
			// 페임을 올려준다.
			if (pTargetCreature->isSlayer()) 
			{
				//increaseFame(pVampire, Exp);
				Slayer* pTargetSlayer  = dynamic_cast<Slayer*>(pTargetCreature);
				targetLevel = pTargetSlayer->getHighestSkillDomainLevel();
				targetMaxHP = pTargetSlayer->getHP(ATTR_MAX);
			}
			else if (pTargetCreature->isVampire()) 
			{
				//increaseFame(pVampire, Exp);
				Vampire* pTargetVampire  = dynamic_cast<Vampire*>(pTargetCreature);
				targetLevel = pTargetVampire->getLevel();
				targetMaxHP = pTargetVampire->getHP(ATTR_MAX);
			}
			else if (pTargetCreature->isOusters()) 
			{
				//increaseFame(pOusters, Exp);
				Ousters* pTargetOusters  = dynamic_cast<Ousters*>(pTargetCreature);
				targetLevel = pTargetOusters->getLevel();
				targetMaxHP = pTargetOusters->getHP(ATTR_MAX);
			}
			else if (pTargetCreature->isMonster())
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);

				Timeval NextTurn = pMonster->getNextTurn();
				Timeval DelayTurn;
				DelayTurn.tv_sec = 4;
				DelayTurn.tv_usec = 500000;
				pMonster->addAccuDelay(DelayTurn);
				pMonster->addEnemy(pVampire);

				targetLevel = pMonster->getLevel();
				targetMaxHP = pMonster->getHP(ATTR_MAX);
			}

			shareVampExp(pVampire, Exp, _GCBloodDrainOK1);

			// 흡혈을 하게 되면 흡혈한 사람의 체력이 올라간다.
			// Mephisto이펙트가 걸려있으면 HP는 안 올라간다.
			if (!pVampire->isFlag(Effect::EFFECT_CLASS_MEPHISTO))
			{
				HP_t HealPoint = (Exp==0? computeBloodDrainHealPoint(pTargetCreature, BLOODDRAIN_EXP) : Exp);
				HP_t CurrentHP = pVampire->getHP();
				HP_t MaxHP	   = pVampire->getHP(ATTR_MAX);
				HP_t NewHP     = min((int)MaxHP , (int)CurrentHP + (int)HealPoint);

				// 은 데미지 관련 처리를 해 준다.
				Silver_t newSilverDamage = max(0, (int)pVampire->getSilverDamage()-(int)HealPoint);
				pVampire->saveSilverDamage(newSilverDamage);
				_GCBloodDrainOK1.addShortData(MODIFY_SILVER_DAMAGE, newSilverDamage);

				// 뱀파이어의 HP를 세팅한다.
				pVampire->setHP(NewHP);

				GCStatusCurrentHP gcStatusCurrentHP;
				gcStatusCurrentHP.setObjectID(pVampire->getObjectID());
				gcStatusCurrentHP.setCurrentHP(NewHP);
				pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcStatusCurrentHP, pVampire);

				_GCBloodDrainOK1.addShortData(MODIFY_CURRENT_HP, NewHP);
			}

			// 흡혈을 당한 애는 HP가 줄어든다.
			// 대상이 내 레벨보다 높다면.. MaxHP의 10~15% damage
			// by sigi. 2002.9.14
			int drainDamage = 0;
			int myLevel = pVampire->getLevel();

			if (targetLevel > myLevel)
			{
				drainDamage = targetMaxHP * (rand()%6+10) / 100;
			}
			else
			{
				// 레벨 5차이마다 1%씩 더~
				int damagePercent = min(30, (rand()%6+10+(myLevel-targetLevel)));
				drainDamage = targetMaxHP * damagePercent / 100;
			}
			
			if (drainDamage > 0)
			{
				//decreaseHP(pZone, pTargetCreature, drainDamage, pVampire->getObjectID()); 
				EffectDecreaseHP* pEffect = new EffectDecreaseHP(pTargetCreature);
				pEffect->setPoint(drainDamage);
				pEffect->setDeadline( 20 );	// 2초 후
				pEffect->setUserObjectID( pVampire->getObjectID() );
				pTargetCreature->addEffect(pEffect);
				pTargetCreature->setFlag(Effect::EFFECT_CLASS_DECREASE_HP);
			}

			pVampire->getGQuestManager()->blooddrain();

			// 흡혈시에도 성향 바뀜
			// by sigi. 2002.12.16
			// EffectDecreaseHP에서 HP가 닳아서 0이 되어야하는 경우가 있어서 
			// EffectDecreaseHP::unaffect()로 옮긴다.
			//computeAlignmentChange(pTargetCreature, drainDamage, pVampire, NULL, &_GCBloodDrainOK1);

			_GCBloodDrainOK1.setObjectID(TargetObjectID);

			_GCBloodDrainOK3.setObjectID(pVampire->getObjectID());
			_GCBloodDrainOK3.setTargetObjectID (TargetObjectID);

			pPlayer->sendPacket(&_GCBloodDrainOK1);

			if (pTargetCreature != NULL && pTargetCreature->isPC()) 
			{
				Player* pTargetPlayer = pTargetCreature->getPlayer();

				if (pTargetPlayer != NULL) 
				{ 
					_GCBloodDrainOK2.setObjectID(pVampire->getObjectID());
					_GCBloodDrainOK2.addLongData(MODIFY_DURATION, BLOODDRAIN_DURATION);
					pTargetPlayer->sendPacket(&_GCBloodDrainOK2);
				}
			}

			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pVampire);
			pZone->broadcastPacket(pVampire->getX(), pVampire->getY(),  &_GCBloodDrainOK3 , cList);
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


//////////////////////////////////////////////////////////////////////
//
// BloodDrain::execute()
//
//////////////////////////////////////////////////////////////////////
void BloodDrain::execute(Monster* pMonster, Creature* pEnemy)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(monster)" << endl;

	Assert(pMonster != NULL);
	Assert(pEnemy != NULL);

	bool bSuccess = false;

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

		// 마스터 : 광역 흡혈 - -;
		if (pMonster->isMaster()
#ifdef __UNDERWORLD__
				|| pMonster->isUnderworld() || pMonster->getMonsterType() == 599
#endif
		)
		{
//			cout << pMonster->getName() << "가 광역흡혈함" << endl;
			int x = pMonster->getX();
			int y = pMonster->getY();
			int Splash = 3 + rand()%5; // 3~7 마리
			int range = 5;	// 11 x 11
			list<Creature*> creatureList;
			getSplashVictims(pMonster->getZone(), x, y, Creature::CREATURE_CLASS_MAX, creatureList, Splash, range);

			list<Creature*>::iterator itr = creatureList.begin();
			for (; itr != creatureList.end(); itr++)
			{
				Creature* pTargetCreature = (*itr);
				Assert(pTargetCreature != NULL);
			
				if (pMonster!=pTargetCreature)
				{
					//cout << "BloodDrain: " << pTargetCreature->getName().c_str() << endl;
					executeMonster(pMonster, pTargetCreature);
				}
			}
		}
		// 일반 몹 : 한 마리
		else
		{
			if (executeMonster(pMonster, pEnemy))
			{
				bSuccess = true;
			}
			else 
			{
				executeSkillFailNormal(pMonster, getSkillType(), pEnemy);
			}
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	// 성공이든 실패든 몬스터에게 딜레이는 걸어준다.
	Timeval NextTurn = pMonster->getNextTurn();
	Timeval DelayTurn;
	DelayTurn.tv_sec = (bSuccess? 4 : 1);	// 성공과 실패의 delay를 다르게 한다. by sigi. 2002.9.14
	DelayTurn.tv_usec = 500000;
	pMonster->addAccuDelay(DelayTurn);


	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(monster)" << endl;

	__END_CATCH
}

bool BloodDrain::executeMonster(Monster* pMonster, Creature* pEnemy)
	
{
	__BEGIN_TRY

	bool isMaster    = pMonster->isMaster()
#ifdef __UNDERWORLD__
	|| pMonster->isUnderworld() || pMonster->getMonsterType() == 599
#endif
	;

	// 죽었으면 흡혈 못하고..
	// 마스터는 아무나 다 빤다 - -;
	// 대상이 죽었으면 못 빤다.
	if (pMonster->isDead()
		|| pMonster->isFlag(Effect::EFFECT_CLASS_COMA)
		|| !pMonster->isEnemyToAttack(pEnemy) && !isMaster
		|| pEnemy->isDead() || pEnemy->isFlag(Effect::EFFECT_CLASS_COMA))
	{
		return false;
	}

	Zone* pZone = pMonster->getZone();
	Assert(pZone != NULL);

	GCBloodDrainOK1 _GCBloodDrainOK1;
	GCBloodDrainOK2 _GCBloodDrainOK2;
	GCBloodDrainOK3 _GCBloodDrainOK3;

	// 마스터는 체력 100% 라도 문다.
	int HPMultiplier = (isMaster? 1 : 3);	// 현재 HP가 1/1,  1/3
	bool bHitRoll    = HitRoll::isSuccessBloodDrain(pMonster, pEnemy, HPMultiplier);
	bool bCanHit     = canHit(pMonster, pEnemy, SKILL_BLOOD_DRAIN);
	// 마스터는 거리에 관계없이 문다~
	bool bRangeCheck = isMaster || verifyDistance(pMonster, pEnemy, 1);

	// 흡혈 면역 상태. by sigi. 2002.9.13
	bool bEffected = pEnemy->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_BLOOD_DRAIN);

	if (bHitRoll && bCanHit && bRangeCheck && !bEffected)
	{
		if (pEnemy->isSlayer())
		{
			// Set EffectBloodDrain
			// 마스터면 안건다.
			if (!isMaster)
			{
				EffectBloodDrain* pEffectBloodDrain = new EffectBloodDrain(pEnemy);
				pEffectBloodDrain->setLevel(pMonster->getLevel());
				pEffectBloodDrain->setDeadline(BLOODDRAIN_DURATION);	// 게임시간으로 3일 정도
				pEnemy->addEffect(pEffectBloodDrain);
				pEffectBloodDrain->create(pEnemy->getName());
				_GCBloodDrainOK2.addShortData(MODIFY_EFFECT_STAT, Effect::EFFECT_CLASS_BLOOD_DRAIN);

				pEnemy->setFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);

				Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pEnemy);
				SLAYER_RECORD prev;
				pTargetSlayer->getSlayerRecord(prev);
				pTargetSlayer->initAllStat();
				pTargetSlayer->sendRealWearingInfo();
				pTargetSlayer->addModifyInfo(prev, _GCBloodDrainOK2);
			}

			// 로그를 남긴다.
			log(LOG_BLOODDRAINED, pEnemy->getName(), "게임 내의 몬스터");
		}
		// 아우스터즈의 경우엔..... -_-; 제한시간 없는 이펙트를 생성한다. 엄밀히 말해 제한시간이 없는 건 아니지만..
//		else if ( pEnemy->isOusters() && !isMaster )
//		{
//			EffectBloodDrain* pEffectBloodDrain = new EffectBloodDrain(pEnemy);
//			pEffectBloodDrain->setLevel(pMonster->getLevel());
//			pEnemy->addEffect(pEffectBloodDrain);
//			pEffectBloodDrain->create(pEnemy->getName());
//			_GCBloodDrainOK2.addShortData(MODIFY_EFFECT_STAT, Effect::EFFECT_CLASS_BLOOD_DRAIN);
//
//			pEnemy->setFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
//
//			Sight_t oldSight = pEnemy->getSight();
//			Sight_t newSight = pEnemy->getEffectedSight();
//
//			if ( oldSight != newSight )
//			{
//				pEnemy->setSight(newSight);
//				pZone->updateScan(pEnemy, oldSight, pEnemy->getSight());
//				_GCBloodDrainOK2.addShortData(MODIFY_VISION, pEnemy->getSight());
//
//				GCChangeDarkLight gcChangeDarkLight;
//				gcChangeDarkLight.setDarkLevel(15);
//				gcChangeDarkLight.setLightLevel(newSight);
//				pEnemy->getPlayer()->sendPacket(&gcChangeDarkLight);
//			}
//		}


		_GCBloodDrainOK3.setObjectID(pMonster->getObjectID());
		_GCBloodDrainOK3.setTargetObjectID (pEnemy->getObjectID());

		// 타겟이 뭐든 플래그는 건다.
		// 마스터면 안건다.
		if (!isMaster)
		{
			pEnemy->setFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);
		}

		if (pEnemy != NULL && pEnemy->isPC()) 
		{
			Player* pTargetPlayer = pEnemy->getPlayer();
			if (pTargetPlayer != NULL) 
			{ 
				_GCBloodDrainOK2.setObjectID(pMonster->getObjectID());
	
				if (!isMaster)
				{
					_GCBloodDrainOK2.addLongData(MODIFY_DURATION, BLOODDRAIN_DURATION);
				}
				pTargetPlayer->sendPacket(&_GCBloodDrainOK2);
			}
		}

		// target
		int targetLevel = 0;
		int targetMaxHP = 0;

		if (pEnemy->isSlayer()) 
		{
			Slayer* pTargetSlayer  = dynamic_cast<Slayer*>(pEnemy);
			targetLevel = pTargetSlayer->getHighestSkillDomainLevel();
			targetMaxHP = pTargetSlayer->getHP(ATTR_MAX);
		}
		else if (pEnemy->isVampire()) 
		{
			Vampire* pTargetVampire  = dynamic_cast<Vampire*>(pEnemy);
			targetLevel = pTargetVampire->getLevel();
			targetMaxHP = pTargetVampire->getHP(ATTR_MAX);
		}
		else if (pEnemy->isOusters()) 
		{
			Ousters* pTargetOusters  = dynamic_cast<Ousters*>(pEnemy);
			targetLevel = pTargetOusters->getLevel();
			targetMaxHP = pTargetOusters->getHP(ATTR_MAX);
		}
		else if (pEnemy->isMonster())
		{
			Monster* pEnemyMonster = dynamic_cast<Monster*>(pEnemy);

			// 흡혈당하는 몬스터한테 딜레이 걸어준다.
			Timeval DelayTurn;
			DelayTurn.tv_sec = 4;
			DelayTurn.tv_usec = 500000;
			pEnemyMonster->addAccuDelay(DelayTurn);

			if ( ( pMonster->isMaster()
#ifdef __UNDERWORLD__
				|| pMonster->isUnderworld() || pMonster->getMonsterType() == 599 
#endif
			)
				&& pMonster->getClanType()==pEnemyMonster->getClanType())
			{
				// 같은 clan의 마스터이면 피 상납이라고 볼 수 있을까 -_-;
			}
			else
			{
				pEnemyMonster->addEnemy(pMonster);
			}

			targetLevel = pEnemyMonster->getLevel();
			targetMaxHP = pEnemyMonster->getHP(ATTR_MAX);
		}

		// 자신이나 상대방 중.. HP가 많은 쪽의 15~25%
		HP_t maxHP = max((int)pMonster->getHP(ATTR_MAX), targetMaxHP);
		HP_t drainHP = maxHP*(rand()%11+15)/100; // 15~25%

		// 한번에 1000이상 안 찬다.
		if ( pMonster->getMonsterType() >= 717 )
			drainHP = min((int)drainHP, 2000);
		else
			drainHP = min((int)drainHP, 1000);

		// 몬스터의 HP를 올려준다.
		HP_t CurrentHP = pMonster->getHP();
		HP_t MaxHP	   = pMonster->getHP(ATTR_MAX);
		HP_t NewHP     = min((int)MaxHP , (int)CurrentHP + (int)drainHP);

		// 뱀파이어의 HP를 세팅한다.
		pMonster->setHP(NewHP);

		GCStatusCurrentHP gcStatusCurrentHP;
		gcStatusCurrentHP.setObjectID(pMonster->getObjectID());
		gcStatusCurrentHP.setCurrentHP(NewHP);
		pZone->broadcastPacket(pMonster->getX(), pMonster->getY(), &gcStatusCurrentHP);

		// 흡혈 당한 애의 HP를 줄인다.
		// 대상이 내 레벨보다 높다면.. MaxHP의 10~15% damage
		// by sigi. 2002.9.14
		int drainDamage = 0;
		int myLevel = pMonster->getLevel();

		if (targetLevel > myLevel)
		{
			drainDamage = targetMaxHP * (rand()%6+10) / 100;
		}
		else
		{
			// 레벨 5차이마다 1%씩 더~
			int damagePercent = min(30, (rand()%6+10+(myLevel-targetLevel)));
			drainDamage = targetMaxHP * damagePercent / 100;
		}
		
		if (drainDamage > 0)
		{
			//decreaseHP(pZone, pEnemy, drainDamage);
			EffectDecreaseHP* pEffect = new EffectDecreaseHP(pEnemy);
			pEffect->setPoint(drainDamage);
			pEffect->setDeadline( 20 );	// 2초 후
			pEffect->setUserObjectID( pMonster->getObjectID() );
			pEnemy->addEffect(pEffect);
			pEnemy->setFlag(Effect::EFFECT_CLASS_DECREASE_HP);
		}

		// 흡혈 모습 보이게..
		list<Creature *> cList;
		cList.push_back(pEnemy);
		cList.push_back(pMonster);
		pZone->broadcastPacket(pMonster->getX(), pMonster->getY(), &_GCBloodDrainOK3 , cList);

		// 흡혈 성공
		return true;
	}

	__END_CATCH

	return false;
}

BloodDrain g_BloodDrain;
