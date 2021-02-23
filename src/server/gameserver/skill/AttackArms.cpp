//////////////////////////////////////////////////////////////////////////////
// Filename    : AttackArms.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "AttackArms.h"
#include "ItemUtil.h"
#include <fstream>
#include <list>

#include "Gpackets/GCAttackArmsOK1.h"
#include "Gpackets/GCAttackArmsOK2.h"
#include "Gpackets/GCAttackArmsOK3.h"
#include "Gpackets/GCAttackArmsOK4.h"
#include "Gpackets/GCAttackArmsOK5.h"
#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void AttackArms::execute(Slayer* pSlayer, ObjectID_t TargetObjectID)
	throw(Error)
{
	__BEGIN_TRY __BEGIN_DEBUG

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayer)" << endl;

	Assert(pSlayer != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NPC는 공격할 수 없다.
		if (pTargetCreature==NULL	// NoSuch제거 때문에.. by sigi. 2002.5.2
			|| !canAttack( pSlayer, pTargetCreature )
		   )
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;
			return;
		}

		// 패킷을 준비하고...
		GCAttackArmsOK1   _GCAttackArmsOK1;
		GCAttackArmsOK2   _GCAttackArmsOK2;
		GCAttackArmsOK3   _GCAttackArmsOK3;
		GCAttackArmsOK4   _GCAttackArmsOK4;
		GCAttackArmsOK5   _GCAttackArmsOK5;

		_GCAttackArmsOK5.setSkillSuccess(false);
		_GCAttackArmsOK1.setSkillSuccess(false);

		// 스킬 슬랏을 받아온다.
		SkillSlot* pSkillSlot = pSlayer->getSkill(SKILL_ATTACK_ARMS);
		Assert(pSkillSlot != NULL);

		// 슬레이어가 쓰고 있는 아이템을 가져온다.
		// 맨손이거나, 총 종류의 무기가 아니라면 에러다.
		Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if (pWeapon == NULL || isArmsWeapon(pWeapon) == false) 
		{
			executeSkillFailException(pSlayer, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;
			return;
		}

		bool bIncreaseDomainExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);

		bool bBulletCheck = (getRemainBullet(pWeapon) > 0) ? true : false;

		// 총알은 무조건 떨어뜨린다.
		Bullet_t RemainBullet = 0;
		if (bBulletCheck)
		{
			decreaseBullet(pWeapon);
			// 한발쓸때마다 저장할 필요 없다. by sigi. 2002.5.9
			//pWeapon->save(pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_RIGHTHAND, 0);
			RemainBullet = getRemainBullet(pWeapon);
		}

		// 총에 총알이 남아있다면...
		if (bBulletCheck) 
		{
			SkillDomainType_t DomainType  = SKILL_DOMAIN_GUN;
			int               ToHitBonus  = 0;
			int               DamageBonus = 0;
			ZoneCoord_t       myX         = pSlayer->getX();
			ZoneCoord_t       myY         = pSlayer->getY();
			ZoneCoord_t       targetX     = pTargetCreature->getX();
			ZoneCoord_t       targetY     = pTargetCreature->getY();
			Dir_t             dir         = calcDirection(myX, myY, targetX, targetY);

			int Splash = computeArmsWeaponSplashSize(pWeapon, myX, myY, targetX, targetY);

			////////////////////////////////////////////////////////////////////////////////
			// SG가 아닌 다른 총의 일반 공격
			////////////////////////////////////////////////////////////////////////////////
			if (Splash == 0)
			{
				ToHitBonus  = computeArmsWeaponToHitBonus(pWeapon, myX, myY, targetX, targetY);
				DamageBonus = computeArmsWeaponDamageBonus(pWeapon, myX, myY, targetX, targetY);

				bool bHitRoll    = HitRoll::isSuccess(pSlayer, pTargetCreature, ToHitBonus);
				bool bTimeCheck  = verifyRunTime(pSkillSlot);
				bool bRangeCheck = verifyDistance(pSlayer, pTargetCreature, pWeapon->getRange());
				bool bPK         = verifyPK(pSlayer, pTargetCreature);

				// 공격자와 상대의 아이템 내구성 떨어트림.
				// 밑에 있던걸 이쪽으로 옮겼다. by sigi. 2002.5.13
				decreaseDurability(pSlayer, pTargetCreature, NULL, &_GCAttackArmsOK1, &_GCAttackArmsOK2);

				if (bHitRoll && bTimeCheck && bRangeCheck && bPK) 
				{
					bool bCriticalHit = false;

					Damage_t Damage = computeDamage(pSlayer, pTargetCreature, 0, bCriticalHit) + DamageBonus;

					setDamage(pTargetCreature, Damage, pSlayer, getSkillType(), &_GCAttackArmsOK2, &_GCAttackArmsOK1);
					computeAlignmentChange(pTargetCreature, Damage, pSlayer, &_GCAttackArmsOK2, &_GCAttackArmsOK1);

					// 크리티컬 히트라면 상대방을 뒤로 물러나게 한다.
					if (bCriticalHit)
					{
						knockbackCreature(pZone, pTargetCreature, myX, myY);
					}

					if (!pTargetCreature->isSlayer())
					{
						if ( bIncreaseDomainExp )
						{
							shareAttrExp(pSlayer, Damage , 1, 8, 1, _GCAttackArmsOK1);
							increaseDomainExp(pSlayer, DomainType , 1, _GCAttackArmsOK1, pTargetCreature->getLevel());
						}

						increaseAlignment(pSlayer, pTargetCreature, _GCAttackArmsOK1);
					}

					_GCAttackArmsOK5.setSkillSuccess(true);
					_GCAttackArmsOK1.setSkillSuccess(true);

					if (pTargetCreature->isPC()) 
					{
						Player* pTargetPlayer = pTargetCreature->getPlayer();
						if (pTargetPlayer != NULL) 
						{ 
							_GCAttackArmsOK2.setObjectID(pSlayer->getObjectID());
							pTargetPlayer->sendPacket(&_GCAttackArmsOK2);
						}
					} 
					else if (pTargetCreature->isMonster())
					{
						Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
						pMonster->addEnemy(pSlayer);
					}
				}

				_GCAttackArmsOK1.setObjectID(TargetObjectID);
				_GCAttackArmsOK1.setBulletNum(RemainBullet);

				_GCAttackArmsOK3.setObjectID(pSlayer->getObjectID());
				_GCAttackArmsOK3.setTargetXY (targetX, targetY);
				
				_GCAttackArmsOK4.setTargetObjectID (TargetObjectID);
				
				_GCAttackArmsOK5.setObjectID(pSlayer->getObjectID());
				_GCAttackArmsOK5.setTargetObjectID (TargetObjectID);

				pPlayer->sendPacket(&_GCAttackArmsOK1);

				list<Creature *> cList;
				cList.push_back(pTargetCreature);
				cList.push_back(pSlayer);
				cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCAttackArmsOK5, cList);
				pZone->broadcastPacket(myX, myY, &_GCAttackArmsOK3, cList);
				pZone->broadcastPacket(targetX, targetY, &_GCAttackArmsOK4, cList);
			}
			////////////////////////////////////////////////////////////////////////////////
			// SG는 기본적으로 splash가 들어간다. 
			////////////////////////////////////////////////////////////////////////////////
			else
			{
				Damage_t Damage = 0;     // 마지막으로 입힌 데미지를 저장하기 위한 변수.
				bool     bHit   = false; // 한 명이라도 맞았는가를 저장하기 위한 변수.

				GCSkillToTileOK1  _GCSkillToTileOK1;
				GCSkillToTileOK2  _GCSkillToTileOK2;
				GCSkillToTileOK3  _GCSkillToTileOK3;
				GCSkillToTileOK4  _GCSkillToTileOK4;
				GCSkillToTileOK5  _GCSkillToTileOK5;
				
				list<Creature*> creatureList;
				list<Creature*> cList;
				getSplashVictims(pZone, targetX, targetY, pTargetCreature->getCreatureClass(), creatureList, Splash);

				Level_t maxEnemyLevel = 0;
				uint EnemyNum = 0;

				list<Creature*>::iterator itr = creatureList.begin();
				for (; itr != creatureList.end(); itr++)
				{
					Creature* pEnemy = (*itr);
					Assert(pEnemy != NULL);

					ToHitBonus  = computeArmsWeaponToHitBonus(pWeapon, myX, myY, pEnemy->getX(), pEnemy->getY());
					DamageBonus = computeArmsWeaponDamageBonus(pWeapon, myX, myY, pEnemy->getX(), pEnemy->getY());

					bool bInvokerCheck   = (pEnemy->getObjectID() == pSlayer->getObjectID()) ? true : false;
					bool bHitRoll        = HitRoll::isSuccess(pSlayer, pEnemy, ToHitBonus);
					bool bPK             = verifyPK(pSlayer, pEnemy);
					bool bZoneLevelCheck = checkZoneLevelToHitTarget(pEnemy);

					if (!bInvokerCheck && bHitRoll && bPK && bZoneLevelCheck)
					{
						bool bCriticalHit = false;

						Damage = computeDamage(pSlayer, pEnemy, 0, bCriticalHit);

						// 메인 타겟을 제외하고는, 스플래시 데미지를 입는데,
						// 스플래시 데미지는 일반 데미지의 50%이다.
						if (pTargetCreature != pEnemy)
						{
							Damage = Damage/2;
						}

						ObjectID_t targetObjectID = pEnemy->getObjectID();
						cList.push_back(pEnemy);
						_GCSkillToTileOK1.addCListElement(targetObjectID);
						_GCSkillToTileOK2.addCListElement(targetObjectID);
						_GCSkillToTileOK5.addCListElement(targetObjectID);

						setDamage(pEnemy, Damage, pSlayer, getSkillType(), NULL, &_GCSkillToTileOK1);
						computeAlignmentChange(pEnemy, Damage, pSlayer, NULL, &_GCSkillToTileOK1);

						increaseAlignment(pSlayer, pEnemy, _GCSkillToTileOK1);

						// 크리티컬 히트라면 상대방을 뒤로 물러나게 한다.
						if (bCriticalHit)
						{
							knockbackCreature(pZone, pEnemy, myX, myY);
						}

						// 타겟이 슬레이어가 아닐 경우에만 경험치를 올려준다.
						if (!pTargetCreature->isSlayer())
						{
							bHit = true;
							if ( maxEnemyLevel < pTargetCreature->getLevel() ) maxEnemyLevel = pTargetCreature->getLevel();
							EnemyNum++;
						}
					}
				}

				if (bHit)
				{
					shareAttrExp(pSlayer, Damage, 1, 8, 1, _GCSkillToTileOK1);
					increaseDomainExp(pSlayer, DomainType, 1, _GCSkillToTileOK1, maxEnemyLevel, EnemyNum);
				}

				// 총알 숫자를 줄이고, 총알 숫자를 저장하고, 남은 총알 숫자를 받은 다음에 내구력을 떨어뜨린다.
				_GCSkillToTileOK1.addShortData(MODIFY_BULLET, RemainBullet);

				decreaseDurability(pSlayer, NULL, NULL, &_GCSkillToTileOK1, NULL);

				_GCSkillToTileOK1.setSkillType(SKILL_MULTI_SHOT);
				_GCSkillToTileOK1.setCEffectID(0);
				_GCSkillToTileOK1.setX(targetX);
				_GCSkillToTileOK1.setY(targetX);
				_GCSkillToTileOK1.setRange(dir);
				_GCSkillToTileOK1.setDuration(0);

				_GCSkillToTileOK2.setObjectID(pSlayer->getObjectID());
				_GCSkillToTileOK2.setSkillType(SKILL_MULTI_SHOT);
				_GCSkillToTileOK2.setX(targetX);
				_GCSkillToTileOK2.setY(targetY);
				_GCSkillToTileOK2.setRange(dir);
				_GCSkillToTileOK2.setDuration(0);

				_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
				_GCSkillToTileOK3.setSkillType(SKILL_MULTI_SHOT);
				_GCSkillToTileOK3.setX(targetX);
				_GCSkillToTileOK3.setY(targetY);

				_GCSkillToTileOK4.setSkillType(SKILL_MULTI_SHOT);
				_GCSkillToTileOK4.setX(targetX);
				_GCSkillToTileOK4.setY(targetY);
				_GCSkillToTileOK4.setDuration(0);
				_GCSkillToTileOK4.setRange(dir);

				_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
				_GCSkillToTileOK5.setSkillType(SKILL_MULTI_SHOT);
				_GCSkillToTileOK5.setX(targetX);
				_GCSkillToTileOK5.setY(targetY);
				_GCSkillToTileOK5.setRange(dir);
				_GCSkillToTileOK5.setDuration(0);

				pPlayer->sendPacket(&_GCSkillToTileOK1);

				// 이 기술에 의해 영향을 받는 놈들에게 패킷을 보내줘야 한다.
				for(list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
				{
					Creature* pVictim = *itr;
					Assert(pVictim != NULL);

					if (pVictim->isPC())
					{
						_GCSkillToTileOK2.clearList();

						HP_t targetHP = 0;
						if (pVictim->isSlayer())
						{
							targetHP = (dynamic_cast<Slayer*>(pVictim))->getHP(ATTR_CURRENT);
						}
						else if (pVictim->isVampire())
						{
							targetHP = (dynamic_cast<Vampire*>(pVictim))->getHP(ATTR_CURRENT);
						}
						else if (pVictim->isOusters())
						{
							targetHP = (dynamic_cast<Ousters*>(pVictim))->getHP(ATTR_CURRENT);
						}
						else continue;

						_GCSkillToTileOK2.addShortData(MODIFY_CURRENT_HP, targetHP);

						decreaseDurability(NULL, pVictim, NULL, NULL, &_GCSkillToTileOK2);

						Player* pPlayer = pVictim->getPlayer();
						Assert(pPlayer != NULL);
						pPlayer->sendPacket(&_GCSkillToTileOK2);
					}
					else if (pVictim->isMonster())
					{
						Monster* pMonster = dynamic_cast<Monster*>(pVictim);
						pMonster->addEnemy(pSlayer);
					}
				}

				cList.push_back(pSlayer);

				cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCSkillToTileOK5, cList);

				pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK3, cList);
				pZone->broadcastPacket(targetX, targetY,  &_GCSkillToTileOK4, cList);
			}

			pSkillSlot->setRunTime();
		} 
		else 
		{
			executeSkillFailNormalWithGun(pSlayer, getSkillType(), pTargetCreature, RemainBullet);
		}
	} 
	catch (Throwable &t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
		//cerr << t.toString() << endl;
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayer)" << endl;

	__END_DEBUG __END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void AttackArms::execute(Monster* pMonster, Creature* pEnemy)
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
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end(monster)" << endl;
			return;
		}
		if (pMonster->isFlag(Effect::EFFECT_CLASS_INVISIBILITY)) 
		{
			addVisibleCreature(pZone, pMonster, true);
		}

		GCAttackArmsOK2 _GCAttackArmsOK2;
		GCAttackArmsOK3 _GCAttackArmsOK3;
		GCAttackArmsOK4 _GCAttackArmsOK4;
		GCAttackArmsOK5 _GCAttackArmsOK5;

		_GCAttackArmsOK5.setSkillSuccess(false);

		if (HitRoll::isSuccess(pMonster, pEnemy) && verifyDistance(pMonster, pEnemy, pMonster->getMissileRange())) 
		{
			bool bCriticalHit = false;

			Damage_t Damage = computeDamage(pMonster, pEnemy, 0, bCriticalHit);
			setDamage(pEnemy, Damage, pMonster, SKILL_ATTACK_ARMS, &_GCAttackArmsOK2, NULL);

			// 크리티컬 히트라면 상대방을 뒤로 물러나게 한다.
			if (bCriticalHit)
			{
				knockbackCreature(pZone, pEnemy, pMonster->getX(), pMonster->getY());
			}

			_GCAttackArmsOK5.setSkillSuccess(true);
		
			if (pEnemy->isPC()) 
			{
				Player* pTargetPlayer = pEnemy->getPlayer();
				if (pTargetPlayer != NULL) 
				{ 
					_GCAttackArmsOK2.setObjectID(pMonster->getObjectID());
					pTargetPlayer->sendPacket(&_GCAttackArmsOK2);
				}
			} 
			else if (pEnemy->isMonster())
			{
				Monster* pTargetMonster = dynamic_cast<Monster*>(pEnemy);

				pTargetMonster->addEnemy(pMonster);

				// 마스터는 딜레이없다.
				if (!pMonster->isMaster()
#ifdef __UNDERWORLD__
						&& !pMonster->isUnderworld() && pMonster->getMonsterType() != 599
#endif
				)
				{
					Timeval NextTurn = pMonster->getNextTurn();
					Timeval DelayTurn;
					DelayTurn.tv_sec = 0;
					DelayTurn.tv_usec = 200000;
					Timeval NewTurn = NextTurn + DelayTurn;

					pTargetMonster->setNextTurn(NewTurn);
				}
			}

			// 공격자와 상대의 아이템 내구성 떨어트림.
			decreaseDurability(pMonster, pEnemy, NULL, NULL, &_GCAttackArmsOK2);

			ZoneCoord_t targetX = pEnemy->getX();
			ZoneCoord_t targetY = pEnemy->getY();
			ZoneCoord_t myX     = pMonster->getX();
			ZoneCoord_t myY     = pMonster->getY();

			_GCAttackArmsOK3.setObjectID(pMonster->getObjectID());
			_GCAttackArmsOK3.setTargetXY (targetX, targetY);
			
			_GCAttackArmsOK4.setTargetObjectID (pEnemy->getObjectID());
			
			_GCAttackArmsOK5.setObjectID(pMonster->getObjectID());
			_GCAttackArmsOK5.setTargetObjectID (pEnemy->getObjectID());

			list<Creature *> cList;
			cList.push_back(pEnemy);
			cList.push_back(pMonster);
			cList = pZone->broadcastSkillPacket(myX, myY, targetX, targetY, &_GCAttackArmsOK5, cList);
			pZone->broadcastPacket(myX, myY, &_GCAttackArmsOK3, cList);
			pZone->broadcastPacket(targetX, targetY, &_GCAttackArmsOK4, cList);
		}
		else
		{
			executeSkillFailNormal(pMonster, getSkillType(), pEnemy);
		}
	} 
	catch (Throwable& t) 
	{
		executeSkillFailException(pMonster, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(monster)" << endl;

	__END_CATCH
}

AttackArms g_AttackArms;
