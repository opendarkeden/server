//////////////////////////////////////////////////////////////////////////////
// Filename    : SimpleTileCureSkill.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SimpleTileCureSkill.h"
#include "EffectBloodDrain.h"
#include "EffectAftermath.h"

#include "GCSkillToObjectOK1.h"
#include "GCSkillToObjectOK2.h"
#include "GCSkillToObjectOK3.h"
#include "GCSkillToObjectOK4.h"
#include "GCSkillToObjectOK5.h"
#include "GCSkillToTileOK1.h"
#include "GCSkillToTileOK2.h"
#include "GCSkillToTileOK3.h"
#include "GCSkillToTileOK4.h"
#include "GCSkillToTileOK5.h"
#include "GCSkillToSelfOK1.h"
#include "GCSkillToSelfOK2.h"
#include "GCStatusCurrentHP.h"
#include "GCRemoveEffect.h"

SimpleTileCureSkill g_SimpleTileCureSkill;

//////////////////////////////////////////////////////////////////////////////
// class SimpleTileCureSkill member methods
//////////////////////////////////////////////////////////////////////////////

void SimpleTileCureSkill::execute(Slayer* pSlayer, SkillSlot* pSkillSlot, 
	const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;
		GCSkillToSelfOK1 _GCSkillToSelfOK1;
		GCSkillToSelfOK2 _GCSkillToSelfOK2;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bHPCheck    = false;
		bool bheal       = false;
		uint HealPoint   = param.SkillDamage;
		uint RealHealPoint   = 0;

		ZoneCoord_t myX = pSlayer->getX();
		ZoneCoord_t myY = pSlayer->getY();

		ZoneCoord_t X = pSlayer->getX();
		ZoneCoord_t Y = pSlayer->getY();

		if (bManaCheck && bTimeCheck && bRangeCheck ) {

			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			int Splash = 3 + pSkillSlot->getExpLevel()/10 + 1;

			list<Creature*> cList;
			list<Creature*> creatureList;
			getSplashVictims(pZone, X, Y, Creature::CREATURE_CLASS_MAX, creatureList, Splash);
			//cout << "Create Size : " << (int)creatureList.size() << endl;

			list<Creature*>::iterator itr = creatureList.begin();
			for (; itr != creatureList.end(); itr++)
			{
                Creature* pTargetCreature = (*itr);
				Assert(pTargetCreature != NULL);
//				bool bSlayer	 = false;		// unused variable warninig clear by bezz 2002.05.13

				EffectBloodDrain* pEffectBloodDrain = NULL;

				bHPCheck = false;		// ũ���ĸ� üũ�Ҷ� ���� ���� �����ؾ����� ������? 2002.05.31 by bezz
				
				if (pTargetCreature->isSlayer() && !pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA) ) {

					HP_t CurrentHP = dynamic_cast<Slayer*>(pTargetCreature)->getHP(ATTR_CURRENT);
					HP_t MaxHP = dynamic_cast<Slayer*>(pTargetCreature)->getHP(ATTR_MAX);

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
							bheal = true;
						}
					}

					bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);

					if ( bHitRoll && bHPCheck && pTargetCreature->isAlive())
					{
						Slayer * pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);

						// �� ȿ�� broadcast
						// by sigi. 2002.6.1
						///*
						_GCSkillToSelfOK1.setSkillType(SKILL_CURE_EFFECT);
						_GCSkillToSelfOK1.setDuration(0);
						pTargetSlayer->getPlayer()->sendPacket(&_GCSkillToSelfOK1);

						_GCSkillToSelfOK2.setObjectID(pSlayer->getObjectID());
						_GCSkillToSelfOK2.setSkillType(SKILL_CURE_EFFECT);
						_GCSkillToSelfOK2.setDuration(0);
						pZone->broadcastPacket( pTargetSlayer->getX(), pTargetSlayer->getY(), &_GCSkillToSelfOK2, pTargetSlayer);
						//*/


						// �������� ���¶�� ���� ���¸� �����ش�.
						if (pEffectBloodDrain != NULL && pEffectBloodDrain->getLevel() < param.Level)
						{

							// ���� �Ƹ�����Ʈ�� �����ϱ� ���� ������ ����Ʈ�� �ٿ��ش�.
							if (pTargetSlayer->isFlag(Effect::EFFECT_CLASS_AFTERMATH))
							{
								Effect* pEffect = pTargetSlayer->findEffect(Effect::EFFECT_CLASS_AFTERMATH);
								EffectAftermath* pEffectAftermath = dynamic_cast<EffectAftermath*>(pEffect);
								pEffectAftermath->setDeadline(5*600); // 5�� ���� ���ӵȴ�.
							}
							else
							{
								EffectAftermath* pEffectAftermath = new EffectAftermath(pTargetSlayer);
								pEffectAftermath->setDeadline(5*600); // 5�� ���� ���ӵȴ�.
								pTargetSlayer->addEffect(pEffectAftermath);
								pTargetSlayer->setFlag(Effect::EFFECT_CLASS_AFTERMATH);
								pEffectAftermath->create(pTargetSlayer->getName());
							}

							pEffectBloodDrain->destroy(pTargetSlayer->getName());
							pTargetSlayer->deleteEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);

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

						// HP�� �����Ѵ�.
						HP_t CurrentHP = pTargetSlayer->getHP(ATTR_CURRENT);
						HP_t MaxHP     = pTargetSlayer->getHP(ATTR_MAX);

						// ���� ȸ�� ��ġ�� ����Ѵ�.
						if( CurrentHP + HealPoint <= MaxHP ) {
							RealHealPoint = max( (unsigned int)0, HealPoint );
						} else {
							RealHealPoint = max( 0, MaxHP - CurrentHP );
						}

						CurrentHP = min((int)MaxHP, (int)(CurrentHP + HealPoint));
						pTargetSlayer->setHP(CurrentHP , ATTR_CURRENT);
						bheal = true;

						cList.push_back(pTargetSlayer);

					}
				} 
			}

			if( bheal ) {
				// ����ġ�� �÷��ش�.
				shareAttrExp(pSlayer, RealHealPoint, param.STRMultiplier, param.DEXMultiplier, param.INTMultiplier, _GCSkillToTileOK1);
				increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1);
				increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToTileOK1);
			}

			Dir_t dir = calcDirection ( myX, myY, X, Y );

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
			_GCSkillToTileOK4.setDuration(0);
			_GCSkillToTileOK4.setRange(dir);

			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(param.SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(dir);
			_GCSkillToTileOK5.setDuration(0);

			pPlayer->sendPacket(&_GCSkillToTileOK1);

			//cout << "Healed Creature Size : " << (int)cList.size() << endl;
    	    cList.push_back(pSlayer);
			// �� ����� ���� ������ �޴� ��鿡�� ��Ŷ�� ������� �Ѵ�.
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

					// ��Ŷ�� �����ش�.
					Player* pPlayer = pTargetCreature->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&_GCSkillToTileOK2);

					// HP�� ��ε�ĳ�����Ѵ�.
					GCStatusCurrentHP gcStatusCurrentHP;
					gcStatusCurrentHP.setObjectID(pTargetCreature->getObjectID());
					gcStatusCurrentHP.setCurrentHP (targetHP);
					pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcStatusCurrentHP);

				}

			    cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

				pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
				pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

				pSkillSlot->setRunTime(param.Delay);
				result.bSuccess = true;
			} 

		}
		else 
		{
			executeSkillFailNormal(pSlayer, param.SkillType, NULL);
		}
	} 
	catch(Throwable & t)  
	{
		executeSkillFailException(pSlayer, param.SkillType);
	}

	__END_CATCH
}

void SimpleTileCureSkill::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, 
	const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID) 
	
{
	__BEGIN_TRY

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch����. by sigi. 2002.5.2
		if (pTargetCreature==NULL)
		{
			executeSkillFailException(pSlayer, param.SkillType);
			return;
		}

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bHPCheck    = false;
		bool bheal       = false;
		uint HealPoint   = param.SkillDamage;
		uint RealHealPoint = 0;

		ZoneCoord_t myX = pSlayer->getX();
		ZoneCoord_t myY = pSlayer->getY();

		ZoneCoord_t X = pTargetCreature->getX();
		ZoneCoord_t Y = pTargetCreature->getY();

		if (bManaCheck && bTimeCheck && bRangeCheck ) {

			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			int Splash = 3 + pSkillSlot->getExpLevel()/10 + 1;

			list<Creature*> cList;
			list<Creature*> creatureList;
			getSplashVictims(pZone, X, Y, Creature::CREATURE_CLASS_MAX, creatureList, Splash);
			//cout << "Create Size : " << (int)creatureList.size() << endl;

			list<Creature*>::iterator itr = creatureList.begin();
			for (; itr != creatureList.end(); itr++)
			{
                Creature* pTargetCreature = (*itr);
				Assert(pTargetCreature != NULL);

				EffectBloodDrain* pEffectBloodDrain = NULL;
				bool bSlayer	 = false;
				
				bHPCheck = false;		// ũ���ĸ� üũ�Ҷ� ���� ���� �����ؾ����� ������? 2002.05.31 by bezz

				if (pTargetCreature->isSlayer() && !pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA)) {

					HP_t CurrentHP = dynamic_cast<Slayer*>(pTargetCreature)->getHP(ATTR_CURRENT);
					HP_t MaxHP = dynamic_cast<Slayer*>(pTargetCreature)->getHP(ATTR_MAX);

					if ( CurrentHP < MaxHP )
					{
						bHPCheck = true;
					}
					bSlayer = true;
				} 

				if ( bSlayer && pTargetCreature->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN))
				{
					Effect* pEffect = pTargetCreature->findEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);
					pEffectBloodDrain = dynamic_cast<EffectBloodDrain*>(pEffect);
					Assert(pEffectBloodDrain != NULL);
						
					if (pEffectBloodDrain->getLevel() < param.Level) {
						bHPCheck = true;
						bheal = true;
					}
				}

				bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);

				if ( bSlayer && bHitRoll && bHPCheck && pTargetCreature->isAlive())
				{
					Slayer * pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);
					Assert(pTargetSlayer!= NULL);

					// �������� ���¶�� ���� ���¸� �����ش�.
					if (pEffectBloodDrain != NULL && pEffectBloodDrain->getLevel() < param.Level)
					{

						// ���� �Ƹ�����Ʈ�� �����ϱ� ���� ������ ����Ʈ�� �ٿ��ش�.
						if (pTargetSlayer->isFlag(Effect::EFFECT_CLASS_AFTERMATH))
						{
							Effect* pEffect = pTargetSlayer->findEffect(Effect::EFFECT_CLASS_AFTERMATH);
							EffectAftermath* pEffectAftermath = dynamic_cast<EffectAftermath*>(pEffect);
							pEffectAftermath->setDeadline(5*600); // 5�� ���� ���ӵȴ�.
						}
						else
						{
							EffectAftermath* pEffectAftermath = new EffectAftermath(pTargetSlayer);
							pEffectAftermath->setDeadline(5*600); // 5�� ���� ���ӵȴ�.
							pTargetSlayer->addEffect(pEffectAftermath);
							pTargetSlayer->setFlag(Effect::EFFECT_CLASS_AFTERMATH);
							pEffectAftermath->create(pTargetSlayer->getName());
						}

						pEffectBloodDrain->destroy(pTargetSlayer->getName());
						pTargetSlayer->deleteEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);

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

					// HP�� �����Ѵ�.
					HP_t CurrentHP = pTargetSlayer->getHP(ATTR_CURRENT);
					HP_t MaxHP     = pTargetSlayer->getHP(ATTR_MAX);

					// ���� ȸ�� ��ġ�� ����Ѵ�.
					if( CurrentHP + HealPoint <= MaxHP ) {
						RealHealPoint = max( (unsigned int)0, HealPoint );
					} else {
						RealHealPoint = max( 0, MaxHP - CurrentHP );
					}

					CurrentHP = min((int)MaxHP, (int)(CurrentHP + HealPoint));
					pTargetSlayer->setHP(CurrentHP , ATTR_CURRENT);
					bheal = true;

					cList.push_back(pTargetSlayer);

				}
			}

			if( bheal ) {
				// ����ġ�� �÷��ش�.
				shareAttrExp(pSlayer, RealHealPoint, param.STRMultiplier, param.DEXMultiplier, param.INTMultiplier, _GCSkillToTileOK1);
				increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1);
				increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToTileOK1);
			}

			Dir_t dir = calcDirection ( myX, myY, X, Y );

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
			_GCSkillToTileOK4.setDuration(0);
			_GCSkillToTileOK4.setRange(dir);

			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(param.SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(dir);
			_GCSkillToTileOK5.setDuration(0);

			pPlayer->sendPacket(&_GCSkillToTileOK1);

			//cout << "Healed Creature Size : " << (int)cList.size() << endl;
    	    cList.push_back(pSlayer);
			// �� ����� ���� ������ �޴� ��鿡�� ��Ŷ�� ������� �Ѵ�.
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

					// ��Ŷ�� �����ش�.
					Player* pPlayer = pTargetCreature->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&_GCSkillToTileOK2);

					// HP�� ��ε�ĳ�����Ѵ�.
					GCStatusCurrentHP gcStatusCurrentHP;
					gcStatusCurrentHP.setObjectID(pTargetCreature->getObjectID());
					gcStatusCurrentHP.setCurrentHP (targetHP);
					pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcStatusCurrentHP);

				}

			    cList = pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

				pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
				pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

				pSkillSlot->setRunTime(param.Delay);
				result.bSuccess = true;
			} 

		}
		else 
		{
			executeSkillFailNormal(pSlayer, param.SkillType, NULL);
		}
	} 
	catch(Throwable & t)  
	{
		executeSkillFailException(pSlayer, param.SkillType);
	}

	__END_CATCH
}
	


void SimpleTileCureSkill::execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, 
	const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
	CEffectID_t CEffectID) 
	
{
	__BEGIN_TRY

	Assert(pSlayer != NULL);
	Assert(pSkillSlot != NULL);

	try 
	{
		Player* pPlayer = pSlayer->getPlayer();
		Zone* pZone = pSlayer->getZone();

		GCSkillToTileOK1 _GCSkillToTileOK1;
		GCSkillToTileOK2 _GCSkillToTileOK2;
		GCSkillToTileOK3 _GCSkillToTileOK3;
		GCSkillToTileOK4 _GCSkillToTileOK4;
		GCSkillToTileOK5 _GCSkillToTileOK5;

		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(param.SkillType);
		SkillDomainType_t DomainType = pSkillInfo->getDomainType();

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pSlayer, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = checkZoneLevelToUseSkill(pSlayer);
		bool bHPCheck    = false;
		bool bheal       = false;
		uint HealPoint   = param.SkillDamage;
		uint RealHealPoint   = 0;

		ZoneCoord_t myX = pSlayer->getX();
		ZoneCoord_t myY = pSlayer->getY();

		if (bManaCheck && bTimeCheck && bRangeCheck ) {

			decreaseMana(pSlayer, RequiredMP, _GCSkillToTileOK1);

			int Splash = 3 + pSkillSlot->getExpLevel()/10 + 1;

			list<Creature*> cList;
			list<Creature*> creatureList;
			getSplashVictims(pZone, X, Y, Creature::CREATURE_CLASS_MAX, creatureList, Splash);
			//cout << "Create Size : " << (int)creatureList.size() << endl;

			list<Creature*>::iterator itr = creatureList.begin();
			for (; itr != creatureList.end(); itr++)
			{
                Creature* pTargetCreature = (*itr);
				Assert(pTargetCreature != NULL);

				EffectBloodDrain* pEffectBloodDrain = NULL;
				
				bool bSlayer	 = false;
				bHPCheck = false;		// ũ���ĸ� üũ�Ҷ� ���� ���� �����ؾ����� ������? 2002.05.31 by bezz
				if (pTargetCreature->isSlayer() && !pTargetCreature->isFlag(Effect::EFFECT_CLASS_COMA) ) {

					HP_t CurrentHP = dynamic_cast<Slayer*>(pTargetCreature)->getHP(ATTR_CURRENT);
					HP_t MaxHP = dynamic_cast<Slayer*>(pTargetCreature)->getHP(ATTR_MAX);

					if ( CurrentHP < MaxHP )
					{
						bHPCheck = true;
					}
					bSlayer = true;
				} 

				if ( bSlayer && pTargetCreature->isFlag(Effect::EFFECT_CLASS_BLOOD_DRAIN))
				{
					Effect* pEffect = pTargetCreature->findEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);
					pEffectBloodDrain = dynamic_cast<EffectBloodDrain*>(pEffect);
					Assert(pEffectBloodDrain != NULL);
						
					if (pEffectBloodDrain->getLevel() < param.Level) {
						bHPCheck = true;
						bheal = true;
					}
				}

				bool bHitRoll    = HitRoll::isSuccessMagic(pSlayer, pSkillInfo, pSkillSlot);

				if ( bSlayer && bHitRoll && bHPCheck && pTargetCreature->isAlive())
				{
					Slayer * pTargetSlayer = dynamic_cast<Slayer*>(pTargetCreature);
					Assert( pTargetSlayer != NULL );

					// �������� ���¶�� ���� ���¸� �����ش�.
					if (pEffectBloodDrain != NULL && pEffectBloodDrain->getLevel() < param.Level)
					{
						// ���� �Ƹ�����Ʈ�� �����ϱ� ���� ������ ����Ʈ�� �ٿ��ش�.
						if (pTargetSlayer->isFlag(Effect::EFFECT_CLASS_AFTERMATH))
						{
							Effect* pEffect = pTargetSlayer->findEffect(Effect::EFFECT_CLASS_AFTERMATH);
							EffectAftermath* pEffectAftermath = dynamic_cast<EffectAftermath*>(pEffect);
							pEffectAftermath->setDeadline(5*600); // 5�� ���� ���ӵȴ�.
						}
						else
						{
							EffectAftermath* pEffectAftermath = new EffectAftermath(pTargetSlayer);
							pEffectAftermath->setDeadline(5*600); // 5�� ���� ���ӵȴ�.
							pTargetSlayer->addEffect(pEffectAftermath);
							pTargetSlayer->setFlag(Effect::EFFECT_CLASS_AFTERMATH);
							pEffectAftermath->create(pTargetSlayer->getName());
						}


						pEffectBloodDrain->destroy(pTargetSlayer->getName());
						pTargetSlayer->deleteEffect(Effect::EFFECT_CLASS_BLOOD_DRAIN);

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

					// HP�� �����Ѵ�.
					HP_t CurrentHP = pTargetSlayer->getHP(ATTR_CURRENT);
					HP_t MaxHP     = pTargetSlayer->getHP(ATTR_MAX);

					// ���� ȸ�� ��ġ�� ����Ѵ�.
					if( CurrentHP + HealPoint <= MaxHP ) {
						RealHealPoint = max( (unsigned int)0, HealPoint );
					} else {
						RealHealPoint = max( 0, MaxHP - CurrentHP );
					}

					CurrentHP = min((int)MaxHP, (int)(CurrentHP + HealPoint));
					pTargetSlayer->setHP(CurrentHP , ATTR_CURRENT);
					bheal = true;

					cList.push_back(pTargetSlayer);

				}
			}

			if( bheal ) {
				// ����ġ�� �÷��ش�.
				shareAttrExp(pSlayer, RealHealPoint, param.STRMultiplier, param.DEXMultiplier, param.INTMultiplier, _GCSkillToTileOK1);
				increaseDomainExp(pSlayer, DomainType, pSkillInfo->getPoint(), _GCSkillToTileOK1);
				increaseSkillExp(pSlayer, DomainType, pSkillSlot, pSkillInfo, _GCSkillToTileOK1);
			}

			Dir_t dir = calcDirection ( myX, myY, X, Y );

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
			_GCSkillToTileOK4.setDuration(0);
			_GCSkillToTileOK4.setRange(dir);

			_GCSkillToTileOK5.setObjectID(pSlayer->getObjectID());
			_GCSkillToTileOK5.setSkillType(param.SkillType);
			_GCSkillToTileOK5.setX(X);
			_GCSkillToTileOK5.setY(Y);
			_GCSkillToTileOK5.setRange(dir);
			_GCSkillToTileOK5.setDuration(0);

			pPlayer->sendPacket(&_GCSkillToTileOK1);

			//cout << "Healed Creature Size : " << (int)cList.size() << endl;
    	    cList.push_back(pSlayer);
			// �� ����� ���� ������ �޴� ��鿡�� ��Ŷ�� ������� �Ѵ�.
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

					// ��Ŷ�� �����ش�.
					Player* pPlayer = pTargetCreature->getPlayer();
					Assert(pPlayer != NULL);
					pPlayer->sendPacket(&_GCSkillToTileOK2);

					// HP�� ��ε�ĳ�����Ѵ�.
					GCStatusCurrentHP gcStatusCurrentHP;
					gcStatusCurrentHP.setObjectID(pTargetCreature->getObjectID());
					gcStatusCurrentHP.setCurrentHP (targetHP);
					pZone->broadcastPacket(pTargetCreature->getX(), pTargetCreature->getY(), &gcStatusCurrentHP);

				}

				pZone->broadcastSkillPacket(myX, myY, X, Y, &_GCSkillToTileOK5, cList);

				pZone->broadcastPacket(myX, myY,  &_GCSkillToTileOK3 , cList);
				pZone->broadcastPacket(X, Y,  &_GCSkillToTileOK4 , cList);

				pSkillSlot->setRunTime(param.Delay);
				result.bSuccess = true;
			} 

		}
		else 
		{
			executeSkillFailNormal(pSlayer, param.SkillType, NULL);
		}
	} 
	catch(Throwable & t)  
	{
		executeSkillFailException(pSlayer, param.SkillType);
	}

	__END_CATCH
}
	
