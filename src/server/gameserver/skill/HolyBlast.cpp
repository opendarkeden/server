//////////////////////////////////////////////////////////////////////////////
// Filename    : HolyBlast.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "HolyBlast.h"
#include "ZoneUtil.h"
#include "SimpleTileCureSkill.h"
#include "EffectBloodDrain.h"
#include "EffectAftermath.h"

#include "Gpackets/GCSkillToTileOK1.h"
#include "Gpackets/GCSkillToTileOK2.h"
#include "Gpackets/GCSkillToTileOK3.h"
#include "Gpackets/GCSkillToTileOK4.h"
#include "Gpackets/GCSkillToTileOK5.h"
#include "Gpackets/GCSkillToTileOK6.h"
#include "Gpackets/GCSkillToSelfOK1.h"
#include "Gpackets/GCSkillToSelfOK2.h"
#include "Gpackets/GCRemoveEffect.h"



//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void HolyBlast::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	SkillInput input(pSlayer, pSkillSlot);
	SkillOutput output;
	input.TargetType = SkillInput::TARGET_OTHER;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.STRMultiplier = 1;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 8;
	param.Level         = input.SkillLevel;

	SIMPLE_SKILL_OUTPUT result;

	g_SimpleTileCureSkill.execute(pSlayer, TargetObjectID, pSkillSlot, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 셀프 핸들러
//////////////////////////////////////////////////////////////////////////////
void HolyBlast::execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	SkillInput input(pSlayer, pSkillSlot);
	SkillOutput output;
	input.TargetType = SkillInput::TARGET_SELF;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.STRMultiplier = 1;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 8;
	param.Level         = input.SkillLevel;

	SIMPLE_SKILL_OUTPUT result;

	g_SimpleTileCureSkill.execute(pSlayer, pSkillSlot, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

void HolyBlast::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	SkillInput input(pSlayer, pSkillSlot);
	SkillOutput output;
	input.TargetType = SkillInput::TARGET_SELF;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.STRMultiplier = 1;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 8;
	param.Level         = input.SkillLevel;

	SIMPLE_SKILL_OUTPUT result;

	cout << "Tile X :" << (int)X << "Tile Y : " << (int)Y << endl;
	g_SimpleTileCureSkill.execute(pSlayer, X, Y, pSkillSlot, param, result);

	__END_CATCH
}


//////////////////////////////////////////////////////////////////////////////
// class SimpleTileMissileSkill member methods
//////////////////////////////////////////////////////////////////////////////

void HolyBlast::execute(Slayer* pSlayer, int X, int Y, SkillSlot* pSkillSlot,
	const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID) throw (Error)
{
	__BEGIN_TRY

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		// 만일 이 기술이 특별한 무기가 있어야 시전할 수 있는 기술이라면...
		// 그 계열의 무기를 들고 있는지를 체크해서 아니라면 실패다.
		if (param.ItemClass != Item::ITEM_CLASS_MAX)
		{
			Item* pItem = pSlayer->getWearItem(Slayer::WEAR_RIGHTHAND);
			if (pItem == NULL || pItem->getItemClass() != param.ItemClass)
			{
				executeSkillFailException(pSlayer, param.SkillType);
				return;
			}
		}

		bool bIncreaseDomainExp = pSlayer->isRealWearingEx(Slayer::WEAR_RIGHTHAND);

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToTileOK6 _GCSkillToTileOK6;

		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();
		SkillLevel_t      SkillLevel = pSkillSlot->getExpLevel();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pSlayer, X, Y, pSkillInfo->getRange());

		if (bManaCheck && bTimeCheck && bRangeCheck )
		{
			// 마나를 떨어뜨린다.
			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			// 좌표와 방향을 구한다.
			ZoneCoord_t myX          = pSlayer->getX();
			ZoneCoord_t myY          = pSlayer->getY();
			Dir_t       dir          = calcDirection(myX, myY, X, Y);
			Damage_t    Damage       = 0;
			Damage_t    MaxDamage    = 0;
			Damage_t    TotalDamage  = 0;
			// SkillFomula에서 구해지는건 공격damage다. - -;
			// 그래서 임시로...
			uint HealPoint   		 = 30 + param.Level/8; //param.SkillDamage;
	        uint RealHealPoint       = 0;
			bool        bCriticalHit = false;
			bool        bHit         = false;
			bool		bHeal		 = false;

			//VSRect rect(1, 1, pZone->getWidth()-2, pZone->getHeight()-2);

			int Splash = 3 + pSkillSlot->getExpLevel()/10 + 1;

			list<Creature*> cList;
            list<Creature*> creatureList;
            getSplashVictims(pZone, X, Y, Creature::CREATURE_CLASS_MAX, creatureList, Splash);

			list<Creature*>::iterator itr = creatureList.begin();
			for (; itr != creatureList.end(); itr++)
			{
				Creature* pTargetCreature = (*itr);
				Assert(pTargetCreature != NULL);

				if (pTargetCreature != pSlayer) 	// 본인이 아닌 경우
				{
					bool bSameRaceCheck  = pTargetCreature->isSlayer();
					bool bZoneLevelCheck = checkZoneLevelToHitTarget(pTargetCreature);

					// 같은 종족이면 치료한다.
					if (bSameRaceCheck && bZoneLevelCheck)
					{
						// 힐받은 애는 cList에 추가하지 않는다.
						// cList에는 맞는 애덜만 넣어주고
						// 얘네들은 CURE_EFFECT를 보여준다.

						EffectBloodDrain* pEffectBloodDrain = NULL;

						bool bHPCheck = false;		// 크리쳐를 체크할때 마다 새로 세팅해야하지 않을까? 2002.05.31 by bezz
						
						if (!pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA) ) 
						{
							Slayer* pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);
							Assert(pTargetSlayer!=NULL);

							HP_t CurrentHP = pTargetSlayer->getHP(ATTR_CURRENT);
							HP_t MaxHP = pTargetSlayer->getHP(ATTR_MAX);

							if ( CurrentHP < MaxHP )
							{
								bHPCheck = true;
							}

							if ( pTargetCreature->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN))
							{
								Effect* pEffect = pTargetCreature->findEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);
								pEffectBloodDrain = dynamic_cast<EffectBloodDrain*>(pEffect);
								Assert(pEffectBloodDrain != NULL);
									
								if (pEffectBloodDrain->getLevel() < param.Level) {
									bHPCheck = true;
									bHeal = true;
								}
							}

							bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);

							if ( bHitRoll && bHPCheck && pTargetCreature->isAlive())
							{
								// 힐 효과 broadcast
								_GCSkillToSelfOK1.setSkillType(SKILL_CURE_EFFECT);
								_GCSkillToSelfOK1.setDuration(0);
								pTargetSlayer->getPlayer()->sendPacket(&_GCSkillToSelfOK1);

								_GCSkillToSelfOK2.setObjectID(pTargetSlayer->getObjectID());
								_GCSkillToSelfOK2.setSkillType(SKILL_CURE_EFFECT);
								_GCSkillToSelfOK2.setDuration(0);
								pZone->broadcastPacket( pTargetSlayer->getX(), pTargetSlayer->getY(), &_GCSkillToSelfOK2, pTargetSlayer);


								// 흡혈당한 상태라면 흡혈 상태를 날려준다.
								if (pEffectBloodDrain != NULL && pEffectBloodDrain->getLevel() < param.Level)
								{

									// 흡혈 아르바이트를 방지하기 위한 후유증 이펙트를 붙여준다.
									if (pTargetSlayer->isFlag(Effect::EFFECT_CLASS_AFTERMATH))
									{
										Effect* pEffect = pTargetSlayer->findEffect(Effect::EFFECT_CLASS_AFTERMATH);
										EffectAftermath* pEffectAftermath = dynamic_cast<EffectAftermath*>(pEffect);
										pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
									}
									else
									{
										EffectAftermath* pEffectAftermath = new EffectAftermath(pTargetSlayer);
										pEffectAftermath->setDeadline(5*600); // 5분 동안 지속된다.
										pTargetSlayer->addEffect(pEffectAftermath);
										pTargetSlayer->setFlag(Effect::EFFECT_CLASS_AFTERMATH);
										pEffectAftermath->create(pTargetSlayer->getName());
									}

									pEffectBloodDrain->destroy(pTargetSlayer->getName());
									pTargetSlayer->deleteEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);
									pTargetSlayer->removeFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN);

									SLAYER_RECORD prev;
									pTargetSlayer->getSlayerRecord(prev);
									pTargetSlayer->initAllStat();
									pTargetSlayer->sendRealWearingInfo();

									if( pTargetSlayer == pSlayer ) {
										pTargetSlayer->addModifyInfo(prev, _GCSkillToTileOK1);
									} else {
										pTargetSlayer->addModifyInfo(prev, _GCSkillToTileOK2);
									}

									GCRemoveEffect gcRemoveEffect;
									gcRemoveEffect.setObjectID(pTargetSlayer->getObjectID());
									gcRemoveEffect.addEffectList((EffectID_t)Effect::EFFECT_CLASS_BLOOD_DRAIN);
									pZone->broadcastPacket(pTargetSlayer->getX(), pTargetSlayer->getY(), &gcRemoveEffect);

								}

								// HP를 세팅한다.
								HP_t CurrentHP = pTargetSlayer->getHP(ATTR_CURRENT);
								HP_t MaxHP     = pTargetSlayer->getHP(ATTR_MAX);

								// 실제 회복 수치를 계산한다.
								if( CurrentHP + HealPoint <= MaxHP ) {
									RealHealPoint = max( 0, (int)HealPoint );
								} else {
									RealHealPoint = max( 0, (MaxHP - CurrentHP) );
								}

								CurrentHP = min((int)MaxHP, (int)(CurrentHP + HealPoint));
								pTargetSlayer->setHP(CurrentHP , ATTR_CURRENT);
								bHeal = true;
							}
						}

					}
					// 다른 종족이면 공격한다.
					else
					{
						bool bPK             = verifyPK(pSlayer, pTargetCreature);
						bool bRaceCheck      = pTargetCreature->isVampire() || pTargetCreature->isMonster();
						bool bHitRoll        = HitRoll::isSuccess( pSlayer, pTargetCreature, SkillLevel );
						
						if (bPK && bRaceCheck && bZoneLevelCheck && bHitRoll )
						{
							Damage       = 0;
							bCriticalHit = false;

							if (param.bAdd)
							{
								Damage += computeDamage(pSlayer, pTargetCreature, SkillLevel/2, bCriticalHit);
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
							TotalDamage += Damage;

							// 페널티는 기본적으로 100이다.
							Damage = getPercentValue(Damage, 100);//penalty);

							// 맞은 애들 지정
							ObjectID_t targetObjectID = pTargetCreature->getObjectID();
							cList.push_back(pTargetCreature);

							_GCSkillToTileOK1.addCListElement(targetObjectID);
							_GCSkillToTileOK2.addCListElement(targetObjectID);
							_GCSkillToTileOK5.addCListElement(targetObjectID);

							// 일단 맞는 놈이 받을 패킷은 널 상태로 한 채로, 데미지를 준다.
							setDamage(pTargetCreature, Damage, pSlayer, param.SkillType, NULL, &_GCSkillToTileOK1);
							computeAlignmentChange(pTargetCreature, Damage, pSlayer, NULL, &_GCSkillToTileOK1);

							increaseAlignment(pSlayer, pTargetCreature, _GCSkillToTileOK1);

							bHit = true;
						}
					}
				}
			}

			if (bHit)
			{
				if ( bIncreaseDomainExp )
				{
					if (param.bExpForTotalDamage)
					{
						int ExpUp = max((unsigned int)TotalDamage, RealHealPoint);
						shareAttrExp(pSlayer, ExpUp, param.STRMultiplier, param.DEXMultiplier, param.INTMultiplier, _GCSkillToTileOK1);
					}
					else
					{
						int ExpUp = max((unsigned int)MaxDamage, RealHealPoint);
						shareAttrExp(pSlayer, ExpUp, param.STRMultiplier, param.DEXMultiplier, param.INTMultiplier, _GCSkillToTileOK1);
					}

					increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1);
					increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToTileOK1);
				}
			}

			// 공격자의 아이템 내구성을 떨어뜨린다.
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

			pZone->broadcastPacket(myX, myY, &_GCSkillToTileOK5 , cList);

			// set Next Run Time
			pSkillSlot->setRunTime(param.Delay);
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


HolyBlast g_HolyBlast;

