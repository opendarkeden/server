//////////////////////////////////////////////////////////////////////////////
// Filename    : SimpleLinearMeleeSkill.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SimpleLinearMeleeSkill.h"
#include "Geometry.h"

#include "GCSkillToTileOK1.h"
#include "GCSkillToTileOK2.h"
#include "GCSkillToTileOK3.h"
#include "GCSkillToTileOK4.h"
#include "GCSkillToTileOK5.h"

SimpleLinearMeleeSkill g_SimpleLinearMeleeSkill;

//////////////////////////////////////////////////////////////////////////////
// class SimpleLinearMeleeSkill member methods
//////////////////////////////////////////////////////////////////////////////

void SimpleLinearMeleeSkill::execute(Slayer* pSlayer, int X, int Y, SkillSlot* pSkillSlot,
	const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID) throw(Error)
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
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		Level_t           SkillLevel = pSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange());

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

			list<POINT> ptList;
			getPointsFromLineEx(myX, myY, X, Y, pSkillInfo->getRange(), ptList);

			VSRect rect(1, 1, pZone->getWidth()-2, pZone->getHeight()-2);

			list<Creature*> cList;

			Level_t maxEnemyLevel = 0;
			uint EnemyNum = 0;

			bool bHit = false;

			list<POINT>::iterator ptitr = ptList.begin();
			for (; ptitr != ptList.end(); ptitr++)
			{
				int tileX   = (*ptitr).x;
				int tileY   = (*ptitr).y;

				// 존 내부이고, 안전지대가 아니라면 맞을 확률이 있다.
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

						bool bMoveModeCheck  = (pTargetCreature->getMoveMode() == Creature::MOVE_MODE_WALKING) ? true : false;

						bool bCanHit         = canHit(pSlayer, pTargetCreature, param.SkillType);
						if((pTargetCreature->getMoveMode() == Creature::MOVE_MODE_FLYING ) &&  param.Level == 1 ) {
							bMoveModeCheck = true;
							bCanHit = true;
						}
						if((pTargetCreature->getMoveMode() == Creature::MOVE_MODE_BURROWING) &&  param.Level == 2 ) {
							bMoveModeCheck = true;
							bCanHit = true;
						}

						bool bRaceCheck      = pTargetCreature->isOusters() || pTargetCreature->isVampire() || pTargetCreature->isMonster();
						bool bHitRoll        = false;
						bool bPK             = verifyPK(pSlayer, pTargetCreature);
						bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);
						bool bSetMinDamage   = false;

						if (param.SkillType == SKILL_SPIT_STREAM && tileX == X && tileY == Y )
						{
							bRaceCheck = !pTargetCreature->isNPC();
						}

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
							|| pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA) )
						{
							bHitRoll = false; 
						}

						if (bMoveModeCheck && bRaceCheck && bHitRoll && bCanHit && bPK && bZoneLevelCheck)
						{
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
							if (bCriticalHit)
							{
								knockbackCreature(pZone, pTargetCreature, pSlayer->getX(), pSlayer->getY());
							}

							// 타겟이 슬레이어가 아닌 경우에만 맞춘 걸로 간주한다.
							if (!pTargetCreature->isSlayer())
							{
								bHit = true;
								if (maxEnemyLevel < pTargetCreature->getLevel() ) maxEnemyLevel = pTargetCreature->getLevel();
								EnemyNum++;
							}
						}
					} 
				} 
			}

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

			_GCSkillToTileOK3.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK3.setSkillType(param.SkillType);
			_GCSkillToTileOK3.setX(X);
			_GCSkillToTileOK3.setY(Y);

			_GCSkillToTileOK4.setSkillType(param.SkillType);
			_GCSkillToTileOK4.setX(X);
			_GCSkillToTileOK4.setY(Y);
			_GCSkillToTileOK4.setRange(dir);
			_GCSkillToTileOK4.setDuration(0);

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
					if (pTargetCreature->isSlayer())
					{
						targetHP = (dynamic_cast<Slayer*>(pTargetCreature))->getHP(ATTR_CURRENT);
					}
					else if (pTargetCreature->isVampire())
					{
						targetHP = (dynamic_cast<Vampire*>(pTargetCreature))->getHP(ATTR_CURRENT);
					}
					else if (pTargetCreature->isOusters())
					{
						targetHP = (dynamic_cast<Ousters*>(pTargetCreature))->getHP(ATTR_CURRENT);
					}
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

			cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5 , cList);

			pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
			pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

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

/*
void SimpleLinearMeleeSkill::execute(Vampire* pVampire, int X, int Y, VampireSkillSlot* pVampireSkillSlot, 
	const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID=0) throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}

void SimpleLinearMeleeSkill::execute(Monster* pMonster, int X, int Y,
	const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID=0) throw(Error)
{
	__BEGIN_TRY
	__END_CATCH
}
*/



