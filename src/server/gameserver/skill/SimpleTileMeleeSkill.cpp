//////////////////////////////////////////////////////////////////////////////
// Filename    : SimpleTileMeleeSkill.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SimpleTileMeleeSkill.h"
#include "CrossCounter.h"
#include "ZoneUtil.h"

#include "GCSkillToTileOK1.h"
#include "GCSkillToTileOK2.h"
#include "GCSkillToTileOK5.h"

SimpleTileMeleeSkill g_SimpleTileMeleeSkill;

//////////////////////////////////////////////////////////////////////////////
// class SimpleTileMeleeSkill member methods
//////////////////////////////////////////////////////////////////////////////

void SimpleTileMeleeSkill::execute(Slayer* pSlayer, int X, int Y, SkillSlot* pSkillSlot,
	const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID, bool bForceKnockback) throw(Error)
{
	__BEGIN_TRY

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		// 만일 이 기술이 특별한 무기가 있어야 시전할 수 있는 기술이라면...
		// 그 계열의 무기를 들고 있는지를 체크해서 아니라면 실패다.
		bool bIncreaseExp = true;
		if (param.ItemClass != Item::ITEM_CLASS_MAX)
		{
			Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
			if (pItem == NULL || pItem->getItemClass() != param.ItemClass)
			{
				executeSkillFailException(pSlayer, param.SkillType);
				return;
			}

			bIncreaseExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);
		}

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		SkillLevel_t      SkillLevel = pSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange());

		// 마나가 있어야 하고, 시간과 거리 체크에 성공하고,
		if (bManaCheck && bTimeCheck && bRangeCheck)
		{
			// MP를 떨어뜨린다.
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			// 좌표와 방향을 구한다.
			ZoneCoord_t myX          = pSlayer->getX();
			ZoneCoord_t myY          = pSlayer->getY();	
			Dir_t       dir          = calcDirection(myX, myY, X, Y);
			Damage_t    Damage       = 0;
			Damage_t    MaxDamage    = 0;
			bool        bCriticalHit = false;
			bool        bHit         = false;

			Level_t maxEnemyLevel = 0;
			uint EnemyNum = 0;

			VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

			list<Creature*> cList;

			list<TILE_MASK>::const_iterator itr = param.MaskList.begin();
			for (; itr != param.MaskList.end(); itr++)
			{
				TILE_MASK mask = (*itr);

				int tileX   = X + mask.x;
				int tileY   = Y + mask.y;
				int penalty = mask.penalty;

				// 현재 타일이 존 내부이고, 안전지대가 아니라면, 맞을 확률이 있다.
				if (rect.ptInRect(tileX, tileY))
				{
					// 타일을 받아온다.
					Tile& tile = pZone->getTile(tileX, tileY);

					list<Creature*> targetList;
					if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
					{
						Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
						targetList.push_back(pCreature);
					}
					if (tile.hasCreature(Creature::MOVE_MODE_FLYING))
					{
						Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
						targetList.push_back(pCreature);
					}
					if (tile.hasCreature(Creature::MOVE_MODE_BURROWING))
					{
						Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_BURROWING);
						targetList.push_back(pCreature);
					}

					list<Creature*>::iterator itr = targetList.begin();
					for(; itr != targetList.end(); itr++)
					{
						Creature* pTargetCreature = (*itr);
						Assert(pTargetCreature != NULL);

						if (pTargetCreature->getObjectID() != pSlayer->getObjectID())
						{
							bool bMoveModeCheck  = (pTargetCreature->getMoveMode() == Creature::MOVE_MODE_WALKING) ? true : false;
							bool bRaceCheck      = pTargetCreature->isNPC() || pTargetCreature->isSlayer();
							bool bHitRoll        = false;
							bool bCanHit         = canHit(pSlayer, pTargetCreature, param.SkillType);
							bool bPK             = verifyPK(pSlayer, pTargetCreature);
							bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);
							bool bSetMinDamage	 = false;

							if (param.bMagicHitRoll)
							{
								bHitRoll = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);
							}
							else
							{
								bHitRoll = HitRoll::isSuccess(pSlayer, pTargetCreature, SkillLevel/2);
							}

							// 도 계열의 기술은 맞지 않더라도 7%의 데미지를 가진다 - by bezz
							if (param.ItemClass == Item::ITEM_CLASS_BLADE && !bHitRoll )
							{
								bHitRoll = true;
								bSetMinDamage = true;
							}

							if (!canAttack(pSlayer, pTargetCreature )
							||	pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA)) // 2003.3.14
							{
								bHitRoll = false; 
							}

							if (bMoveModeCheck && !bRaceCheck && bHitRoll && bCanHit && bPK && bZoneLevelCheck)
							{
								CheckCrossCounter(pSlayer, pTargetCreature, Damage, pSkillInfo->getRange());

								bCriticalHit = false;
								Damage       = 0;

								if (param.bAdd)
								{
									Damage += computeDamage(pSlayer, pTargetCreature, SkillLevel/5, bCriticalHit);
								}

								if (param.bMagicDamage)
								{
									Damage += computeMagicDamage(pTargetCreature, param.SkillDamage, param.SkillType);
								}
								else
								{
									Damage += param.SkillDamage;
								}

								// HitRoll 에서 실패한 도 계열의 기술의 경우 7%의 데미지를 갖도록 한다 - by bezz
								if (bSetMinDamage )
								{
									Damage = getPercentValue(Damage, 7);
								}

								MaxDamage = max(Damage, MaxDamage);

								// 페널티는 기본적으로 100이다.
								Damage = getPercentValue(Damage, penalty);

								ObjectID_t targetObjectID = pTargetCreature->getObjectID();
								cList.push_back(pTargetCreature);

								_GCSkillToTileOK1.addCListElement(targetObjectID);
								_GCSkillToTileOK2.addCListElement(targetObjectID);
								_GCSkillToTileOK5.addCListElement(targetObjectID);

								// 일단 맞는 놈이 받을 패킷은 널 상태로 한 채로, 데미지를 준다.
								setDamage(pTargetCreature, Damage, pSlayer, param.SkillType, NULL, &_GCSkillToTileOK1);
								computeAlignmentChange(pTargetCreature, Damage, pSlayer, NULL, &_GCSkillToTileOK1);

								increaseAlignment(pSlayer, pTargetCreature, _GCSkillToTileOK1);

								// 크리티컬 히트라면 상대방을 뒤로 물러나게 한다.
								if (bCriticalHit || bForceKnockback)
								{
									knockbackCreature(pZone, pTargetCreature, pSlayer->getX(), pSlayer->getY());
								}

								// 상대방이 슬레이어가 아닐 경우에만 맞춘 걸로 간주한다. 
								if (!pTargetCreature->isSlayer())
								{
									bHit = true;
									if (maxEnemyLevel < pTargetCreature->getLevel() ) maxEnemyLevel = pTargetCreature->getLevel();
									EnemyNum++;
								}
							}
						}
					} //for (; itr != objectList.end(); itr++) 
				} // if (rect.ptInRect(tileX, tileY) && ...
			} // for (int count=0; count<3; count++)


			if (bHit)
			{
				if (bIncreaseExp)
				{
					shareAttrExp(pSlayer, MaxDamage, param.STRMultiplier, param.DEXMultiplier, param.INTMultiplier, _GCSkillToTileOK1);
					increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1, maxEnemyLevel, EnemyNum);
					increaseSkillExp(pSlayer, DomainType,  pSkillSlot, pSkillInfo, _GCSkillToTileOK1);
				}
			}

			decreaseDurability(pSlayer, NULL, pSkillInfo, &_GCSkillToTileOK1, NULL);

			_GCSkillToTileOK1.setSkillType(param.SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setRange(dir);
			_GCSkillToTileOK1.setDuration(0);
		
			_GCSkillToTileOK2.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK2.setSkillType(param.SkillType);
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setRange(dir);
			_GCSkillToTileOK2.setDuration(0);
		
			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(param.SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(dir);
			_GCSkillToTileOK5.setDuration(0);
		
			pPlayer->sendPacket(&_GCSkillToTileOK1);
		
			// 이 기술에 의해 영향을 받는 놈들에게 패킷을 보내줘야 한다.
			for (list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
			{
				Creature * pTargetCreature = *itr;
				Assert(pTargetCreature != NULL);

				if (pTargetCreature->isPC())
				{
					_GCSkillToTileOK2.clearList();

					// HP의 변경사항을 패킷에다 기록한다.
					HP_t targetHP = 0;
					if (pTargetCreature->isSlayer()) targetHP = (dynamic_cast<Slayer*>(pTargetCreature))->getHP(ATTR_CURRENT);
					else if (pTargetCreature->isVampire()) targetHP = (dynamic_cast<Vampire*>(pTargetCreature))->getHP(ATTR_CURRENT);
					else if (pTargetCreature->isOusters()) targetHP = (dynamic_cast<Ousters*>(pTargetCreature))->getHP(ATTR_CURRENT);
					_GCSkillToTileOK2.addShortData(MODIFY_CURRENT_HP, targetHP);

					// 아이템의 내구력을 떨어뜨린다.
					decreaseDurability(NULL, pTargetCreature, pSkillInfo, NULL, &_GCSkillToTileOK2);

					// 패킷을 보내준다.
					pTargetCreature->getPlayer()->sendPacket(&_GCSkillToTileOK2);
				}
				else if (pTargetCreature->isMonster())
				{
					// 당근 적으로 인식한다.
					Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
					pMonster->addEnemy(pSlayer);
				}
			}

			cList.push_back(pSlayer);

			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK5 , cList);

			// set Next Run Time
			pSkillSlot->setRunTime(param.Delay);

			result.bSuccess = true;
		} 
		else 
		{
			executeSkillFailNormal(pSlayer, param.SkillType, NULL);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pSlayer, param.SkillType);
	}

	__END_CATCH
}

void SimpleTileMeleeSkill::execute(Vampire* pVampire, int X, int Y, VampireSkillSlot* pVampireSkillSlot, 
	const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID, bool bForceKnockback) throw(Error)
{
	__BEGIN_TRY

	Assert(pVampire != NULL);
	Assert(pVampireSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck = verifyDistance(pVampire, X, Y, pSkillInfo->getRange());

		// 마나가 있어야 하고, 시간과 거리 체크에 성공하고,
		if (bManaCheck && bTimeCheck && bRangeCheck)
		{
			// MP를 떨어뜨린다.
			decreaseMana(pVampire, RequiredMP, _GCSkillToTileOK1);

			// 좌표와 방향을 구한다.
			ZoneCoord_t myX          = pVampire->getX();
			ZoneCoord_t myY          = pVampire->getY();	
			Dir_t       dir          = calcDirection(myX, myY, X, Y);
			Damage_t    Damage       = 0;
			Damage_t    MaxDamage    = 0;
			bool        bCriticalHit = false;

			VSRect rect(0, 0, pZone->getWidth()-2, pZone->getHeight()-2);

			list<Creature*> cList;

			list<TILE_MASK>::const_iterator itr = param.MaskList.begin();
			for (; itr != param.MaskList.end(); itr++)
			{
				TILE_MASK mask = (*itr);

				int tileX   = X + mask.x;
				int tileY   = Y + mask.y;
				int penalty = mask.penalty;

				// 현재 타일이 존 내부이고, 안전지대가 아니라면, 맞을 확률이 있다.
				if (rect.ptInRect(tileX, tileY))
				{
					// 타일을 받아온다.
					Tile& tile = pZone->getTile(tileX, tileY);

					list<Creature*> targetList;
					if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
					{
						Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
						targetList.push_back(pCreature);
					}
					if (tile.hasCreature(Creature::MOVE_MODE_FLYING))
					{
						Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
						targetList.push_back(pCreature);
					}
					if (tile.hasCreature(Creature::MOVE_MODE_BURROWING))
					{
						Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_BURROWING);
						targetList.push_back(pCreature);
					}

					list<Creature*>::iterator itr = targetList.begin();
					for(; itr != targetList.end(); itr++)
					{
						Creature* pTargetCreature = (*itr);
						Assert(pTargetCreature != NULL);

						if (pTargetCreature->getObjectID() != pVampire->getObjectID())
						{
							bool bMoveModeCheck  = (pTargetCreature->getMoveMode() == Creature::MOVE_MODE_WALKING) ? true : false;
							bool bRaceCheck      = pTargetCreature->isNPC() || pTargetCreature->isVampire();
							bool bHitRoll        = false;
							bool bCanHit         = canHit(pVampire, pTargetCreature, param.SkillType);
							bool bPK             = verifyPK(pVampire, pTargetCreature);
							bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);

							if (param.SkillType == SKILL_VIOLENT_PHANTOM && mask.x == 0 && mask.y == 0 )
							{
								bRaceCheck = pTargetCreature->isNPC();
							}

							if (param.bMagicHitRoll)
							{
								bHitRoll = HitRoll::isSuccessMagic(pVampire, pSkillInfo, pVampireSkillSlot);
							}
							else
							{
								bHitRoll = HitRoll::isSuccess(pVampire, pTargetCreature, 0);
							}

							if (!canAttack(pVampire, pTargetCreature ) 
								||	pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA)) // 2003.3.14
							{
								bHitRoll = false; 
							}

							if (bMoveModeCheck && !bRaceCheck && bHitRoll && bCanHit && bPK && bZoneLevelCheck)
							{
								CheckCrossCounter(pVampire, pTargetCreature, Damage, pSkillInfo->getRange());

								bCriticalHit = false;
								Damage       = 0;

								if (param.bAdd)
								{
									Damage += computeDamage(pVampire, pTargetCreature, 0, bCriticalHit);
								}

								if (param.bMagicDamage)
								{
									Damage += computeMagicDamage(pTargetCreature, param.SkillDamage, param.SkillType, true, pVampire);
								}
								else
								{
									Damage += param.SkillDamage;
								}

								MaxDamage = max(Damage, MaxDamage);

								// 페널티는 기본적으로 100이다.
								Damage = getPercentValue(Damage, penalty);

								ObjectID_t targetObjectID = pTargetCreature->getObjectID();
								cList.push_back(pTargetCreature);

								_GCSkillToTileOK1.addCListElement(targetObjectID);
								_GCSkillToTileOK2.addCListElement(targetObjectID);
								_GCSkillToTileOK5.addCListElement(targetObjectID);

								// 일단 맞는 놈이 받을 패킷은 널 상태로 한 채로, 데미지를 준다.
								setDamage(pTargetCreature, Damage, pVampire, param.SkillType, NULL, &_GCSkillToTileOK1);
								computeAlignmentChange(pTargetCreature, Damage, pVampire, NULL, &_GCSkillToTileOK1);

								increaseAlignment(pVampire, pTargetCreature, _GCSkillToTileOK1);

								// 크리티컬 히트라면 상대방을 뒤로 물러나게 한다.
								if (bCriticalHit || bForceKnockback)
								{
									knockbackCreature(pZone, pTargetCreature, pVampire->getX(), pVampire->getY());
								}

								if (pTargetCreature->isDead())
								{
									int exp = computeCreatureExp(pTargetCreature, KILL_EXP);
									shareVampExp(pVampire, exp, _GCSkillToTileOK1);
								}
							}
						}
					} //for (; itr != objectList.end(); itr++) 
				} // if (rect.ptInRect(tileX, tileY) && ...
			} // for (int count=0; count<3; count++)

			decreaseDurability(pVampire, NULL, pSkillInfo, &_GCSkillToTileOK1, NULL);

			_GCSkillToTileOK1.setSkillType(param.SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setRange(dir);
			_GCSkillToTileOK1.setDuration(0);
		
			_GCSkillToTileOK2.setObjectID(pVampire->getObjectID());
			_GCSkillToTileOK2.setSkillType(param.SkillType);
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setRange(dir);
			_GCSkillToTileOK2.setDuration(0);
		
			_GCSkillToTileOK5.setObjectID(pVampire->getObjectID());
			_GCSkillToTileOK5.setSkillType(param.SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(dir);
			_GCSkillToTileOK5.setDuration(0);
		
			pPlayer->sendPacket(&_GCSkillToTileOK1);
		
			// 이 기술에 의해 영향을 받는 놈들에게 패킷을 보내줘야 한다.
			for (list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
			{
				Creature * pTargetCreature = *itr;
				Assert(pTargetCreature != NULL);

				if (pTargetCreature->isPC())
				{
					_GCSkillToTileOK2.clearList();

					// HP의 변경사항을 패킷에다 기록한다.
					HP_t targetHP = 0;
					if (pTargetCreature->isVampire()) targetHP = (dynamic_cast<Vampire*>(pTargetCreature))->getHP(ATTR_CURRENT);
					else if (pTargetCreature->isSlayer()) targetHP = (dynamic_cast<Slayer*>(pTargetCreature))->getHP(ATTR_CURRENT);
					else if (pTargetCreature->isOusters()) targetHP = (dynamic_cast<Ousters*>(pTargetCreature))->getHP(ATTR_CURRENT);

					_GCSkillToTileOK2.addShortData(MODIFY_CURRENT_HP, targetHP);

					// 아이템의 내구력을 떨어뜨린다.
					decreaseDurability(NULL, pTargetCreature, pSkillInfo, NULL, &_GCSkillToTileOK2);

					// 패킷을 보내준다.
					pTargetCreature->getPlayer()->sendPacket(&_GCSkillToTileOK2);
				}
				else if (pTargetCreature->isMonster())
				{
					// 당근 적으로 인식한다.
					Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
					pMonster->addEnemy(pVampire);
				}
			}

			cList.push_back(pVampire);

			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK5 , cList);

			// set Next Run Time
			pVampireSkillSlot->setRunTime(param.Delay);

			result.bSuccess = true;
		} 
		else 
		{
			executeSkillFailNormal(pVampire, param.SkillType, NULL);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pVampire, param.SkillType);
	}

	__END_CATCH
}

void SimpleTileMeleeSkill::execute(Ousters* pOusters, int X, int Y, OustersSkillSlot* pOustersSkillSlot,
	const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID, bool bForceKnockback) throw(Error)
{
	__BEGIN_TRY

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		// 만일 이 기술이 특별한 무기가 있어야 시전할 수 있는 기술이라면...
		// 그 계열의 무기를 들고 있는지를 체크해서 아니라면 실패다.
		if (param.ItemClass != Item::ITEM_CLASS_MAX)
		{
			Item* pItem = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
			if (pItem == NULL || pItem->getItemClass() != param.ItemClass)
			{
				executeSkillFailException(pOusters, param.SkillType);
				return;
			}

		}

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		SkillLevel_t      SkillLevel = pOustersSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, X, Y, pSkillInfo->getRange());

		// 마나가 있어야 하고, 시간과 거리 체크에 성공하고,
		if (bManaCheck && bTimeCheck && bRangeCheck)
		{
			// MP를 떨어뜨린다.
			decreaseMana(pOusters, RequiredMP, _GCSkillToTileOK1);

			// 좌표와 방향을 구한다.
			ZoneCoord_t myX          = pOusters->getX();
			ZoneCoord_t myY          = pOusters->getY();	
			Dir_t       dir          = calcDirection(myX, myY, X, Y);
			Damage_t    Damage       = 0;
			Damage_t    MaxDamage    = 0;
			bool        bCriticalHit = false;
			bool        bHit         = false;

			VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

			list<Creature*> cList;

			list<TILE_MASK>::const_iterator itr = param.MaskList.begin();
			for (; itr != param.MaskList.end(); itr++)
			{
				TILE_MASK mask = (*itr);

				int tileX   = X + mask.x;
				int tileY   = Y + mask.y;
				int penalty = mask.penalty;

				// 현재 타일이 존 내부이고, 안전지대가 아니라면, 맞을 확률이 있다.
				if (rect.ptInRect(tileX, tileY))
				{
					// 타일을 받아온다.
					Tile& tile = pZone->getTile(tileX, tileY);

					list<Creature*> targetList;
					if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
					{
						Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
						targetList.push_back(pCreature);
					}
					if (tile.hasCreature(Creature::MOVE_MODE_FLYING))
					{
						Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
						targetList.push_back(pCreature);
					}
					if (tile.hasCreature(Creature::MOVE_MODE_BURROWING))
					{
						Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_BURROWING);
						targetList.push_back(pCreature);
					}

					list<Creature*>::iterator itr = targetList.begin();
					for(; itr != targetList.end(); itr++)
					{
						Creature* pTargetCreature = (*itr);
						Assert(pTargetCreature != NULL);

						if (pTargetCreature->getObjectID() != pOusters->getObjectID())
						{
							bool bMoveModeCheck  = (pTargetCreature->getMoveMode() == Creature::MOVE_MODE_WALKING) ? true : false;
							bool bRaceCheck      = pTargetCreature->isNPC() || pTargetCreature->isOusters();
							bool bHitRoll        = false;
							bool bCanHit         = canHit(pOusters, pTargetCreature, param.SkillType);
							bool bPK             = verifyPK(pOusters, pTargetCreature);
							bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);
							bool bSetMinDamage	 = false;

							if (param.bMagicHitRoll)
							{
								bHitRoll = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot);
							}
							else
							{
								bHitRoll = HitRoll::isSuccess(pOusters, pTargetCreature, SkillLevel/2);
							}

							if (!canAttack(pOusters, pTargetCreature )
							||	pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA)) // 2003.3.14
							{
								bHitRoll = false; 
							}

							if (bMoveModeCheck && !bRaceCheck && bHitRoll && bCanHit && bPK && bZoneLevelCheck)
							{
								CheckCrossCounter(pOusters, pTargetCreature, Damage, pSkillInfo->getRange());

								bCriticalHit = false;
								Damage       = 0;

								if (param.bAdd)
								{
									Damage += computeDamage(pOusters, pTargetCreature, SkillLevel/5, bCriticalHit);
								}

								if (param.bMagicDamage)
								{
									Damage += computeMagicDamage(pTargetCreature, param.SkillDamage, param.SkillType);
								}
								else
								{
									Damage += param.SkillDamage;
								}

								// HitRoll 에서 실패한 도 계열의 기술의 경우 7%의 데미지를 갖도록 한다 - by bezz
								if (bSetMinDamage )
								{
									Damage = getPercentValue(Damage, 7);
								}

								MaxDamage = max(Damage, MaxDamage);

								// 페널티는 기본적으로 100이다.
								Damage = getPercentValue(Damage, penalty);

								ObjectID_t targetObjectID = pTargetCreature->getObjectID();
								cList.push_back(pTargetCreature);

								_GCSkillToTileOK1.addCListElement(targetObjectID);
								_GCSkillToTileOK2.addCListElement(targetObjectID);
								_GCSkillToTileOK5.addCListElement(targetObjectID);

								// 일단 맞는 놈이 받을 패킷은 널 상태로 한 채로, 데미지를 준다.
								setDamage(pTargetCreature, Damage, pOusters, param.SkillType, NULL, &_GCSkillToTileOK1);
								computeAlignmentChange(pTargetCreature, Damage, pOusters, NULL, &_GCSkillToTileOK1);

								increaseAlignment(pOusters, pTargetCreature, _GCSkillToTileOK1);

								// 크리티컬 히트라면 상대방을 뒤로 물러나게 한다.
								if (bCriticalHit || bForceKnockback)
								{
									knockbackCreature(pZone, pTargetCreature, pOusters->getX(), pOusters->getY());
								}

								// 상대방이 아우스터즈가 아닐 경우에만 맞춘 걸로 간주한다. 
								if (!pTargetCreature->isOusters())
								{
									bHit = true;
								}

								if (pTargetCreature->isDead())
								{
//									int exp = computeCreatureExp(pTargetCreature, 100, pOusters);
									int exp = computeCreatureExp(pTargetCreature, 70, pOusters);
									shareOustersExp(pOusters, exp, _GCSkillToTileOK1);
								}
							}
						}
					} //for (; itr != objectList.end(); itr++) 
				} // if (rect.ptInRect(tileX, tileY) && ...
			} // for (int count=0; count<3; count++)


			decreaseDurability(pOusters, NULL, pSkillInfo, &_GCSkillToTileOK1, NULL);

			_GCSkillToTileOK1.setSkillType(param.SkillType);
			_GCSkillToTileOK1.setCEffectID(CEffectID);
			_GCSkillToTileOK1.setX(X);
			_GCSkillToTileOK1.setY(Y);
			_GCSkillToTileOK1.setRange(dir);
			_GCSkillToTileOK1.setDuration(0);
		
			_GCSkillToTileOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK2.setSkillType(param.SkillType);
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setRange(dir);
			_GCSkillToTileOK2.setDuration(0);
		
			_GCSkillToTileOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToTileOK5.setSkillType(param.SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(dir);
			_GCSkillToTileOK5.setDuration(0);
		
			pPlayer->sendPacket(&_GCSkillToTileOK1);
		
			// 이 기술에 의해 영향을 받는 놈들에게 패킷을 보내줘야 한다.
			for (list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
			{
				Creature * pTargetCreature = *itr;
				Assert(pTargetCreature != NULL);

				if (pTargetCreature->isPC())
				{
					_GCSkillToTileOK2.clearList();

					// HP의 변경사항을 패킷에다 기록한다.
					HP_t targetHP = 0;
					if (pTargetCreature->isSlayer()) targetHP = (dynamic_cast<Slayer*>(pTargetCreature))->getHP(ATTR_CURRENT);
					else if (pTargetCreature->isVampire()) targetHP = (dynamic_cast<Vampire*>(pTargetCreature))->getHP(ATTR_CURRENT);
					else if (pTargetCreature->isOusters()) targetHP = (dynamic_cast<Ousters*>(pTargetCreature))->getHP(ATTR_CURRENT);
					_GCSkillToTileOK2.addShortData(MODIFY_CURRENT_HP, targetHP);

					// 아이템의 내구력을 떨어뜨린다.
					decreaseDurability(NULL, pTargetCreature, pSkillInfo, NULL, &_GCSkillToTileOK2);

					// 패킷을 보내준다.
					pTargetCreature->getPlayer()->sendPacket(&_GCSkillToTileOK2);
				}
				else if (pTargetCreature->isMonster())
				{
					// 당근 적으로 인식한다.
					Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
					pMonster->addEnemy(pOusters);
				}
			}

			cList.push_back(pOusters);

			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK5 , cList);

			// set Next Run Time
			pOustersSkillSlot->setRunTime(param.Delay);

			result.bSuccess = true;
		} 
		else 
		{
			executeSkillFailNormal(pOusters, param.SkillType, NULL);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, param.SkillType);
	}

	__END_CATCH
}

void SimpleTileMeleeSkill::execute(Monster* pMonster, int X, int Y,
	const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID, bool bForceKnockback) throw(Error)
{
	__BEGIN_TRY

	Assert(pMonster != NULL);

	try 
	{
		Zone* pZone = pMonster->getZone();
		Assert(pZone != NULL);

		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);

		bool bRangeCheck = verifyDistance(pMonster, X, Y, pSkillInfo->getRange());

		// 마나가 있어야 하고, 시간과 거리 체크에 성공하고,
		if (bRangeCheck)
		{
			// 좌표와 방향을 구한다.
			ZoneCoord_t myX          = pMonster->getX();
			ZoneCoord_t myY          = pMonster->getY();	
			Dir_t       dir          = calcDirection(myX, myY, X, Y);
			Damage_t    Damage       = 0;
			Damage_t    MaxDamage    = 0;
			bool        bCriticalHit = false;

			VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

			list<Creature*> cList;

			list<TILE_MASK>::const_iterator itr = param.MaskList.begin();
			for (; itr != param.MaskList.end(); itr++)
			{
				TILE_MASK mask = (*itr);

				int tileX   = X + mask.x;
				int tileY   = Y + mask.y;
				int penalty = mask.penalty;

				// 현재 타일이 존 내부이고, 안전지대가 아니라면, 맞을 확률이 있다.
				if (rect.ptInRect(tileX, tileY))
				{
					// 타일을 받아온다.
					Tile& tile = pZone->getTile(tileX, tileY);

					list<Creature*> targetList;
					if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
					{
						Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);
						targetList.push_back(pCreature);
					}
					if (tile.hasCreature(Creature::MOVE_MODE_FLYING))
					{
						Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_FLYING);
						targetList.push_back(pCreature);
					}
					if (tile.hasCreature(Creature::MOVE_MODE_BURROWING))
					{
						Creature* pCreature = tile.getCreature(Creature::MOVE_MODE_BURROWING);
						targetList.push_back(pCreature);
					}

					list<Creature*>::iterator itr = targetList.begin();
					for(; itr != targetList.end(); itr++)
					{
						Creature* pTargetCreature = (*itr);
						Assert(pTargetCreature != NULL);

						// 공격 대상이 맞는지 확인한다.
						if (pMonster->isEnemyToAttack(pTargetCreature ))
						{
							bool bMoveModeCheck  = (pTargetCreature->getMoveMode() == Creature::MOVE_MODE_WALKING) ? true : false;
							bool bRaceCheck      = pTargetCreature->isNPC();// || pTargetCreature->isMonster();
							bool bHitRoll        = 0;
							bool bCanHit         = canHit(pMonster, pTargetCreature, param.SkillType) && canAttack(pMonster, pTargetCreature);
							bool bPK             = verifyPK(pMonster, pTargetCreature);
							bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);

							if (param.bMagicHitRoll)
							{
								bHitRoll = HitRoll::isSuccessMagic(pMonster, pSkillInfo);
							}
							else
							{
								bHitRoll = HitRoll::isSuccess(pMonster, pTargetCreature, 0);
							}

							// bMoveModeCheck 하는거 여기서는 뺐다. 지하에 있는 놈들도 맞으라고. 2003.10.27
							if (!bRaceCheck && bHitRoll && bCanHit && bPK && bZoneLevelCheck)
							{
								CheckCrossCounter(pMonster, pTargetCreature, Damage, pSkillInfo->getRange());

								bCriticalHit = false;
								Damage       = 0;

								if (param.bAdd)
								{
									Damage += computeDamage(pMonster, pTargetCreature, 0, bCriticalHit);
								}

								if (param.bMagicDamage)
								{
									Damage += computeMagicDamage(pTargetCreature, param.SkillDamage, param.SkillType);
								}
								else
								{
									Damage += param.SkillDamage;
								}

								MaxDamage = max(Damage, MaxDamage);

								// 페널티는 기본적으로 100이다.
								Damage = getPercentValue(Damage, penalty);

								ObjectID_t targetObjectID = pTargetCreature->getObjectID();
								cList.push_back(pTargetCreature);

								_GCSkillToTileOK2.addCListElement(targetObjectID);
								_GCSkillToTileOK5.addCListElement(targetObjectID);

								// 일단 맞는 놈이 받을 패킷은 널 상태로 한 채로, 데미지를 준다.
								setDamage(pTargetCreature, Damage, pMonster, param.SkillType, NULL, NULL);

								// 크리티컬 히트라면 상대방을 뒤로 물러나게 한다.
								// 걸어다니는 놈들만 knockback시킨다.
								if (bMoveModeCheck && (bCriticalHit || bForceKnockback) )
								{
									knockbackCreature(pZone, pTargetCreature, pMonster->getX(), pMonster->getY());
								}
							}
						}
					} //for (; itr != objectList.end(); itr++) 
				} // if (rect.ptInRect(tileX, tileY) && ...
			} // for (int count=0; count<3; count++)

			_GCSkillToTileOK2.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK2.setSkillType(param.SkillType);
			_GCSkillToTileOK2.setX(X);
			_GCSkillToTileOK2.setY(Y);
			_GCSkillToTileOK2.setRange(dir);
			_GCSkillToTileOK2.setDuration(0);
		
			_GCSkillToTileOK5.setObjectID(pMonster->getObjectID());
			_GCSkillToTileOK5.setSkillType(param.SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(dir);
			_GCSkillToTileOK5.setDuration(0);
		
			// 이 기술에 의해 영향을 받는 놈들에게 패킷을 보내줘야 한다.
			for (list<Creature*>::const_iterator itr = cList.begin(); itr != cList.end(); itr++)
			{
				Creature * pTargetCreature = *itr;
				Assert(pTargetCreature != NULL);

				if (pTargetCreature->isPC())
				{
					_GCSkillToTileOK2.clearList();

					// HP의 변경사항을 패킷에다 기록한다.
					HP_t targetHP = 0;
					if (pTargetCreature->isSlayer()) targetHP = (dynamic_cast<Slayer*>(pTargetCreature))->getHP(ATTR_CURRENT);
					else if (pTargetCreature->isVampire()) targetHP = (dynamic_cast<Vampire*>(pTargetCreature))->getHP(ATTR_CURRENT);
					else if (pTargetCreature->isOusters()) targetHP = (dynamic_cast<Ousters*>(pTargetCreature))->getHP(ATTR_CURRENT);
					_GCSkillToTileOK2.addShortData(MODIFY_CURRENT_HP, targetHP);

					// 아이템의 내구력을 떨어뜨린다.
					decreaseDurability(NULL, pTargetCreature, pSkillInfo, NULL, &_GCSkillToTileOK2);

					// 패킷을 보내준다.
					pTargetCreature->getPlayer()->sendPacket(&_GCSkillToTileOK2);
				}
				else if (pTargetCreature->isMonster())
				{
					// 당근 적으로 인식한다.
					Monster* pTargetMonster = dynamic_cast<Monster*>(pTargetCreature);
					pTargetMonster->addEnemy(pMonster);
				}
			}

			cList.push_back(pMonster);

			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK5 , cList);

			result.bSuccess = true;
		} 
		else 
		{
			executeSkillFailNormal(pMonster, param.SkillType, NULL);
		}
	} 
	catch (Throwable & t) 
	{
		executeSkillFailException(pMonster, param.SkillType);
	}

	__END_CATCH
}
