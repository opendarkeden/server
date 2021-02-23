//////////////////////////////////////////////////////////////////////////////
// Filename    : MultiShot.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "MultiShot.h"
#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "ItemUtil.h"
#include <list>

//////////////////////////////////////////////////////////////////////////////
// 생성자 - 마스크를 초기화한다.
//////////////////////////////////////////////////////////////////////////////
MultiShot::MultiShot()
	throw()
{
	__BEGIN_TRY

	// SG 마스크는 방향과는 관계없이 항상 + 모양이다.
	m_pSGMask[0].set(-1, -1);
	m_pSGMask[1].set(0, -1);
	m_pSGMask[2].set(1, -1);
	m_pSGMask[3].set(-1,  0);
	m_pSGMask[4].set(0,  0);
	m_pSGMask[5].set(1,  0);
	m_pSGMask[6].set(-1,  1);
	m_pSGMask[7].set(0,  1);
	m_pSGMask[8].set(1,  1);

	// AR 마스크를 초기화시킨다.
	// SwordWave와 비슷하지만, SwordWave는 시전자 주위를 
	// 마스크를 이용해 검사하지만. MultiShot은 타겟의 주위를 마스크를
	// 이용해 검사한다는 것을 생각해야 한다.
	//
	// (-1,-1)(0,-1)(1,-1)
	// (-1, 0)(0, 0)(1, 0)
	// (-1, 1)(0, 1)(1, 1)
	//
	// 각 방향에 따라 어느 타일이 명중 대상이냐를
	// 생각하면 마스크를 이해하기 쉽다.

	m_pARMask[LEFT][0].set(0,-1);
	m_pARMask[LEFT][1].set(0, 0);
	m_pARMask[LEFT][2].set(0, 1);

	m_pARMask[RIGHT][0].set(0,-1);
	m_pARMask[RIGHT][1].set(0, 0);
	m_pARMask[RIGHT][2].set(0, 1);

	m_pARMask[UP][0].set(-1,0);
	m_pARMask[UP][1].set(0,0);
	m_pARMask[UP][2].set(1,0);

	m_pARMask[DOWN][0].set(-1,0);
	m_pARMask[DOWN][1].set(0,0);
	m_pARMask[DOWN][2].set(1,0);

	m_pARMask[LEFTUP][0].set(1,-1);
	m_pARMask[LEFTUP][1].set(0, 0);
	m_pARMask[LEFTUP][2].set(-1, 1);

	m_pARMask[RIGHTDOWN][0].set(1,-1);
	m_pARMask[RIGHTDOWN][1].set(0, 0);
	m_pARMask[RIGHTDOWN][2].set(-1, 1);

	m_pARMask[LEFTDOWN][0].set(-1,-1);
	m_pARMask[LEFTDOWN][1].set(0, 0);
	m_pARMask[LEFTDOWN][2].set(1, 1);

	m_pARMask[RIGHTUP][0].set(-1,-1);
	m_pARMask[RIGHTUP][1].set(0, 0);
	m_pARMask[RIGHTUP][2].set(1, 1);

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void MultiShot::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Zone* pZone = pSlayer->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL)
		{
			executeSkillFailException(pSlayer, getSkillType());
			return;
		}

		// 아이템이 없거나, 총 계열의 무기가 아니거나, SR이라면
		// 이 기술을 사용할 수 없다.
		Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if (pItem == NULL 
			|| !isArmsWeapon(pItem))
			// SR도 사용 가능하게 수정. by sigi. 2002.12.3
			//	|| pItem->getItemClass() == Item::ITEM_CLASS_SR)
		{
			executeSkillFailException(pSlayer, getSkillType());
			return;
		}

		Item::ItemClass IClass = pItem->getItemClass();
		if (IClass == Item::ITEM_CLASS_SG) 
		{
			SGexecute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
		} 
		else if (IClass == Item::ITEM_CLASS_AR 
				|| IClass == Item::ITEM_CLASS_SMG
				// SR도 사용 가능하게 수정. by sigi. 2002.12.3
				|| IClass == Item::ITEM_CLASS_SR) 
		{
			ARSMGexecute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void MultiShot::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Zone* pZone = pSlayer->getZone();
		Assert(pZone != NULL);

		// 아이템이 없거나, 총 계열의 무기가 아니거나, SR이라면
		// 이 기술을 사용할 수 없다.
		Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		if (pItem == NULL 
			|| !isArmsWeapon(pItem))
			// SR도 사용 가능하게 수정. by sigi. 2002.12.3
			//|| pItem->getItemClass() == Item::ITEM_CLASS_SR)
		{
			executeSkillFailException(pSlayer, getSkillType());
			return;
		}

		Item::ItemClass IClass = pItem->getItemClass();
		if (IClass == Item::ITEM_CLASS_SG) 
		{
			SGexecute(pSlayer, X, Y, pSkillSlot, CEffectID);
		} 
		else if (IClass == Item::ITEM_CLASS_AR 
				|| IClass == Item::ITEM_CLASS_SMG
				// SR도 사용 가능하게 수정. by sigi. 2002.12.3
				|| IClass == Item::ITEM_CLASS_SR) 
		{
			ARSMGexecute(pSlayer, X, Y, pSkillSlot, CEffectID);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 타일 핸들러 - SG를 들고 있을 경우
//////////////////////////////////////////////////////////////////////////////
void MultiShot::SGexecute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " SGexecute  Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(getSkillType());
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		Level_t 	      SkillLevel = pSkillSlot->getExpLevel();

		Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		Assert(pWeapon != NULL);

		bool bIncreaseExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);
 
		int  RequiredMP   = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck   = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck   = verifyRunTime(pSkillSlot);
		bool bRangeCheck  = verifyDistance(pSlayer, X, Y, pWeapon->getRange());
		bool bBulletCheck = (getRemainBullet(pWeapon) > 0) ? true : false;

		// 총알 수는 무조건 떨어뜨린다.
		Bullet_t RemainBullet = 0;
		if (bBulletCheck)
		{
			decreaseBullet(pWeapon);
			// 한발쓸때마다 저장할 필요 없다. by sigi. 2002.5.9
			//pWeapon->save(pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_RIGHTHAND, 0);
			RemainBullet = getRemainBullet(pWeapon);
		}

		// 데미지, 투힛 보너스, 좌표와 방향을 구한다.
		int         ToHitBonus    = 0;
		int         DamageBonus   = 0;
		int         ToHitPenalty  = 0;
		int         DamagePenalty = 0;
		ZoneCoord_t myX           = pSlayer->getX();
		ZoneCoord_t myY           = pSlayer->getY();	
		Dir_t       dir           = calcDirection(myX, myY, X, Y);
		bool        bHit          = false; // 한번이라도 맞았는가를 저장하기 위한 변수
		Damage_t    Damage        = 0;     // 마지막으로 입힌 데미지를 저장하기 위한 변수

		// SG일 경우에는 4부터 시작해서 9까지의 splash 데미지를 입힌다.
		int Splash = 3 + pSkillSlot->getExpLevel()/10 + 1;

		if (bManaCheck && bTimeCheck && bRangeCheck && bBulletCheck)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			// output.ToHit값이 음수이기 때문에, %값이 음수로 돌아온다.
			ToHitPenalty = getPercentValue(pSlayer->getToHit(), output.ToHit);

			list<Creature*> cList;
			list<Creature*> creatureList;
			getSplashVictims(pZone, X, Y, Creature::CREATURE_CLASS_MAX, creatureList, Splash);

			Level_t maxEnemyLevel = 0;
			uint EnemyNum = 0;

			list<Creature*>::iterator itr = creatureList.begin();
			for (; itr != creatureList.end(); itr++)
			{
				Creature* pTargetCreature = (*itr);
				Assert(pTargetCreature != NULL);

				ToHitBonus  = computeArmsWeaponToHitBonus(pWeapon, myX, myY, pTargetCreature->getX(), pTargetCreature->getY());
				DamageBonus = computeArmsWeaponDamageBonus(pWeapon, myX, myY, pTargetCreature->getX(), pTargetCreature->getY());

				bool bInvokerCheck   = (pTargetCreature->getObjectID() == pSlayer->getObjectID()) ? true : false;
				bool bRaceCheck      = pTargetCreature->isSlayer() || pTargetCreature->isNPC();
				bool bHitRoll        = HitRoll::isSuccess(pSlayer, pTargetCreature, ToHitPenalty + ToHitBonus);
				bool bPK             = verifyPK(pSlayer, pTargetCreature);
				bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);

				if ( !canAttack( pSlayer, pTargetCreature )
					|| pTargetCreature->isFlag( Effect::EFFECT_CLASS_COMA )
				)
				{
					bHitRoll = false;
				}

				if (!bInvokerCheck && !bRaceCheck && bHitRoll && bPK && bZoneLevelCheck)
				{
					bool bCriticalHit = false;

					// 데미지를 계산해서 페널티를 가한다.
					// 보너스는 멀티샷 페널티 때문에 음수가 될 수도 있다.
					Damage        = computeDamage(pSlayer, pTargetCreature, SkillLevel/5, bCriticalHit);
					DamagePenalty = getPercentValue(Damage, output.Damage);
					Damage        = max(0, Damage + DamagePenalty + DamageBonus);

					// 메인 타겟을 제외하고는, 스플래시 데미지를 입는데,
					// 스플래시 데미지는 일반 데미지의 50%다.
					if (pTargetCreature->getX() != X || pTargetCreature->getY() != Y)
					{
						Damage = Damage/2;
					}

					// 소드웨이브와는 달리 크로스 카운터 체크는 하지 않는다.
					ObjectID_t targetObjectID = pTargetCreature->getObjectID();
					cList.push_back(pTargetCreature);
					_GCSkillToTileOK1.addCListElement(targetObjectID);
					_GCSkillToTileOK2.addCListElement(targetObjectID);
					_GCSkillToTileOK5.addCListElement(targetObjectID);
					
					setDamage(pTargetCreature, Damage, pSlayer, getSkillType(), NULL, &_GCSkillToTileOK1);
					computeAlignmentChange(pTargetCreature, Damage, pSlayer, NULL, &_GCSkillToTileOK1);

					increaseAlignment(pSlayer, pTargetCreature, _GCSkillToTileOK1);

					// 크리티컬 히트라면 상대방을 뒤로 물러나게 한다.
					if (bCriticalHit)
					{
						knockbackCreature(pZone, pTargetCreature, myX, myY);
					}

					// 슬레이어 아닌 경우에만 hit한 걸로 간주한다.
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
				if (bIncreaseExp)
				{
					shareAttrExp(pSlayer, Damage , 1, 8, 1, _GCSkillToTileOK1);
					increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1, maxEnemyLevel, EnemyNum);
					increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToTileOK1);
				}
			}

			_GCSkillToTileOK1.addShortData(MODIFY_BULLET, RemainBullet);

			// 총알 숫자를 줄이고, 총알 숫자를 저장하고, 남은 총알 숫자를 받은 다음에 내구력을 떨어뜨린다.
			decreaseDurability(pSlayer, NULL, pSkillInfo, &_GCSkillToTileOK1, NULL);

			_GCSkillToTileOK1.setSkillType(getSkillType());
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setRange(dir);
			_GCSkillToTileOK1.setDuration(0);
		
			_GCSkillToTileOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK2.setSkillType(getSkillType());
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setRange(dir);
			_GCSkillToTileOK2.setDuration(0);

			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(getSkillType());
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			_GCSkillToTileOK4.setSkillType(getSkillType());
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(0);
			_GCSkillToTileOK4.setRange(dir);
		
			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(getSkillType());
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(dir);
			_GCSkillToTileOK5.setDuration(0);
			
			pPlayer->sendPacket(&_GCSkillToTileOK1);
		
			// 이 기술에 의해 영향을 받는 놈들에게 패킷을 보내줘야 한다.
			for(list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
			{
				Creature* pTargetCreature = *itr;
				Assert(pTargetCreature != NULL);

				if (pTargetCreature->isPC())
				{
					_GCSkillToTileOK2.clearList();

					HP_t targetHP = 0;
					if (pTargetCreature->isSlayer())
					{
						targetHP = (dynamic_cast<Slayer*>(pTargetCreature))->getHP();
					}
					else if (pTargetCreature->isVampire())
					{
						targetHP = (dynamic_cast<Vampire*>(pTargetCreature))->getHP();
					}
					else if (pTargetCreature->isOusters())
					{
						targetHP = (dynamic_cast<Ousters*>(pTargetCreature))->getHP();
					}

					_GCSkillToTileOK2.addShortData(MODIFY_CURRENT_HP, targetHP);

					// 아이템의 내구력을 떨어뜨린다.
					decreaseDurability(NULL, pTargetCreature, pSkillInfo, NULL, &_GCSkillToTileOK2);

					// 패킷을 보내준다.
					Player* pPlayer = pTargetCreature->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&_GCSkillToTileOK2);
				}
				else if (pTargetCreature->isMonster())
				{
					// 당근 적으로 인식한다.
					Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
					pMonster->addEnemy(pSlayer);
				}
			}

			cList.push_back(pSlayer);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormalWithGun(pSlayer, getSkillType(), NULL, RemainBullet);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " SGexecute End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 타일 핸들러 - AR이나 SMG를 들고 있을 경우
//////////////////////////////////////////////////////////////////////////////
void MultiShot::ARSMGexecute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " SGexecute  Begin" << endl;

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(getSkillType());
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		Level_t 	      SkillLevel = pSkillSlot->getExpLevel();

		Item* pWeapon = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
		Assert(pWeapon != NULL);

		bool bIncreaseExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);
 
		int  RequiredMP   = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck   = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck   = verifyRunTime(pSkillSlot);
		bool bRangeCheck  = verifyDistance(pSlayer, X, Y, pWeapon->getRange());
		bool bBulletCheck = (getRemainBullet(pWeapon) > 0) ? true : false;

		// 총알 숫자는 무조건 떨어뜨린다.
		Bullet_t RemainBullet = 0;
		if (bBulletCheck)
		{
			decreaseBullet(pWeapon);
			// 한발쓸때마다 저장할 필요 없다. by sigi. 2002.5.9
			// pWeapon->save(pSlayer->getName(), STORAGE_GEAR, 0, Slayer::WEAR_RIGHTHAND, 0);
			RemainBullet = getRemainBullet(pWeapon);
		}

		// 데미지, 투힛 보너스, 좌표와 방향을 구한다.
		int         ToHitBonus    = 0;
		int         DamageBonus   = 0;
		int         ToHitPenalty  = 0;
		int         DamagePenalty = 0;
		ZoneCoord_t myX           = pSlayer->getX();
		ZoneCoord_t myY           = pSlayer->getY();	
		Dir_t       dir           = calcDirection(myX, myY, X, Y);
		bool        bHit          = false; // 한번이라도 맞았는가를 저장하기 위한 변수
		Damage_t    Damage        = 0;     // 마지막으로 입힌 데미지를 저장하기 위한 변수

		// AR이나 SMG일 경우에는 2부터 시작해서 4까지의 splash 데미지를 입힌다.
		int Splash = 1 + pSkillSlot->getExpLevel()/30 + 1;

		if (bManaCheck && bTimeCheck && bRangeCheck && bBulletCheck)
		{
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			SkillInput input(pSlayer, pSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			// 음수 값이 돌아온다.
			ToHitPenalty  = getPercentValue(pSlayer->getToHit(), output.ToHit);

			list<Creature*> cList;
			list<Creature*> creatureList;
			getSplashVictims(pZone, X, Y, Creature::CREATURE_CLASS_MAX, creatureList, Splash);

			Level_t maxEnemyLevel = 0;
			uint EnemyNum = 0;

			list<Creature*>::iterator itr = creatureList.begin();
			for (; itr != creatureList.end(); itr++)
			{
				Creature* pTargetCreature = (*itr);
				Assert(pTargetCreature != NULL);

				ToHitBonus  = computeArmsWeaponToHitBonus(pWeapon, myX, myY, pTargetCreature->getX(), pTargetCreature->getY());
				DamageBonus = computeArmsWeaponDamageBonus(pWeapon, myX, myY, pTargetCreature->getX(), pTargetCreature->getY());

				bool bInvokerCheck   = (pTargetCreature->getObjectID() == pSlayer->getObjectID()) ? true : false;
				bool bRaceCheck      = pTargetCreature->isSlayer() || pTargetCreature->isNPC();
				bool bHitRoll        = HitRoll::isSuccess(pSlayer, pTargetCreature, ToHitPenalty + ToHitBonus);
				bool bPK             = verifyPK(pSlayer, pTargetCreature);
				bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);

				if ( !canAttack( pSlayer, pTargetCreature )
					|| pTargetCreature->isFlag( Effect::EFFECT_CLASS_COMA )
				)
				{
					bHitRoll = false;
				}

				if (!bInvokerCheck && !bRaceCheck && bHitRoll && bPK && bZoneLevelCheck)
				{
					bool bCriticalHit = false;

					// 데미지를 계산해서 페널티를 가한다.
					// 보너스는 멀티샷 페널티 때문에 음수가 될 수도 있다.
					Damage        = computeDamage(pSlayer, pTargetCreature, SkillLevel/5, bCriticalHit);
					DamagePenalty = getPercentValue(Damage, output.Damage);
					Damage        = max(0, Damage + DamagePenalty + DamageBonus);

					// 메인 타겟을 제외하고는, 스플래시 데미지를 입는데,
					// 스플래시 데미지는 일반 데미지의 50%다.
					if (pTargetCreature->getX() != X || pTargetCreature->getY() != Y)
					{
						Damage = Damage/2;
					}

					// 소드웨이브와는 달리 크로스 카운터 체크는 하지 않는다.
					ObjectID_t targetObjectID = pTargetCreature->getObjectID();
					cList.push_back(pTargetCreature);
					_GCSkillToTileOK1.addCListElement(targetObjectID);
					_GCSkillToTileOK2.addCListElement(targetObjectID);
					_GCSkillToTileOK5.addCListElement(targetObjectID);
							
					setDamage(pTargetCreature, Damage, pSlayer, getSkillType(), NULL, &_GCSkillToTileOK1);
					computeAlignmentChange(pTargetCreature, Damage, pSlayer, NULL, &_GCSkillToTileOK1);

					// 크리티컬 히트라면 상대방을 뒤로 물러나게 한다.
					if (bCriticalHit)
					{
						knockbackCreature(pZone, pTargetCreature, pSlayer->getX(), pSlayer->getY());
					}

					// 슬레이어가 아닐 경우에만 맞춘 걸로 간주한다.
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
				if (bIncreaseExp)
				{
					increaseDomainExp(pSlayer, DomainType , pSkillInfo->getPoint(), _GCSkillToTileOK1, maxEnemyLevel, EnemyNum);
					shareAttrExp(pSlayer, Damage , 1, 8, 1, _GCSkillToTileOK1);
				}
				increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToTileOK1);
			}

			_GCSkillToTileOK1.addShortData(MODIFY_BULLET, RemainBullet);

			decreaseDurability(pSlayer, NULL, pSkillInfo, &_GCSkillToTileOK1, NULL);

			_GCSkillToTileOK1.setSkillType(getSkillType());
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setRange(dir);
			_GCSkillToTileOK1.setDuration(0);
		
			_GCSkillToTileOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK2.setSkillType(getSkillType());
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setRange(dir);
			_GCSkillToTileOK2.setDuration(0);

			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(getSkillType());
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			_GCSkillToTileOK4.setSkillType(getSkillType());
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setDuration(0);
			_GCSkillToTileOK4.setRange(dir);
		
			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(getSkillType());
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(dir);
			_GCSkillToTileOK5.setDuration(0);
			
			pPlayer->sendPacket(&_GCSkillToTileOK1);
		
			// 이 기술에 의해 영향을 받는 놈들에게 패킷을 보내줘야 한다.
			for(list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
			{
				Creature* pTargetCreature = *itr;
				Assert(pTargetCreature != NULL);

				if (pTargetCreature->isPC())
				{
					_GCSkillToTileOK2.clearList();

					HP_t targetHP = 0;
					if (pTargetCreature->isSlayer())
					{
						targetHP = (dynamic_cast<Slayer*>(pTargetCreature))->getHP();
					}
					else if (pTargetCreature->isVampire())
					{
						targetHP = (dynamic_cast<Vampire*>(pTargetCreature))->getHP();
					}
					else if (pTargetCreature->isOusters())
					{
						targetHP = (dynamic_cast<Ousters*>(pTargetCreature))->getHP();
					}

					_GCSkillToTileOK2.addShortData(MODIFY_CURRENT_HP, targetHP);

					// 아이템의 내구력을 떨어뜨린다.
					decreaseDurability(NULL, pTargetCreature, pSkillInfo, NULL, &_GCSkillToTileOK2);

					// 패킷을 보내준다.
					Player* pPlayer = pTargetCreature->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&_GCSkillToTileOK2);
				}
				else if (pTargetCreature->isMonster())
				{
					// 당근 적으로 인식한다.
					Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
					pMonster->addEnemy(pSlayer);
				}
			}

			cList.push_back(pSlayer);

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

			pSkillSlot->setRunTime(output.Delay);
		} 
		else 
		{
			executeSkillFailNormalWithGun(pSlayer, getSkillType(), NULL, RemainBullet);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, getSkillType());
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " SGexecute End" << endl;

	__END_CATCH
}

MultiShot g_MultiShot;
