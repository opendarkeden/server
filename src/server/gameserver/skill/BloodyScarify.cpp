//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyScarify.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "BloodyScarify.h"
#include "RankBonus.h"
#include "Vampire.h"
#include "SkillUtil.h"
#include "Zone.h"
#include "HitRoll.h"
#include "CrossCounter.h"
#include "EffectSetAfire.h"
#include "EffectHPRecovery.h"
#include "Corpse.h"
#include "MonsterCorpse.h"

#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCHPRecoveryStartToOthers.h"
#include "Gpackets/GCHPRecoveryStartToSelf.h"
#include "Gpackets/GCDeleteObject.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void BloodyScarify::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	Assert( pVampire != NULL );
	Assert( pVampireSkillSlot != NULL );

	try
	{
		Player* pPlayer = pVampire->getPlayer();
		Zone* pZone = pVampire->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);
		if ( pTargetCreature==NULL )
		{
			Item* pTargetItem = pZone->getItem( TargetObjectID );
			if ( pTargetItem == NULL || pTargetItem->getItemClass() != Item::ITEM_CLASS_CORPSE )
			{
				executeSkillFailException(pVampire, getSkillType());
				return;
			}

			eatCorpse( pVampire, pTargetItem, pVampireSkillSlot );
			return;
		}

		// NPC는 공격할 수가 없다.
		// NoSuch제거. by sigi. 2002.5.2
		if ( !canAttack( pVampire, pTargetCreature )
			|| pTargetCreature->isNPC() )
		{
			executeSkillFailException(pVampire, getSkillType());
			return;
		}

		if ( pTargetCreature->isFlag( Effect::EFFECT_CLASS_COMA ) )
		{
			eatComaCreature( pVampire, pTargetCreature );
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;

		SkillType_t       SkillType  = pVampireSkillSlot->getSkillType();
		SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
		Range_t			  Range		 = pSkillInfo->getRange();

		int  RequiredMP         = decreaseConsumeMP(pVampire, pSkillInfo);
		bool bManaCheck         = hasEnoughMana(pVampire, RequiredMP);
		bool bTimeCheck         = verifyRunTime(pVampireSkillSlot);
		bool bRangeCheck        = verifyDistance(pVampire, pTargetCreature, Range);
		bool bHitRoll           = HitRoll::isSuccess( pVampire, pTargetCreature );
		bool bCanHit            = canHit(pVampire, pTargetCreature, getSkillType());
		bool bPK                = verifyPK(pVampire, pTargetCreature);
		// add by Coffee 2007-6-9  藤속왱뇜세콘엥
		//bool bUseSkillCrad		= useSkillCrad(pVampire);
		/*
		bool bFastMove			= false;
		if ( getDistance( pVampire->getX(), pVampire->getY(), pTargetCreature->getX(), pTargetCreature->getY() ) > 1 )
		{
			bFastMove = true;
		//	pZone->moveFastPC(pVampire, pVampire->getX(), pVampire->getY(), pTargetCreature->getX(), pTargetCreature->getY(), getSkillType());
		}
		*/
		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bCanHit && bPK )//&& bUseSkillCrad)
				/*&&	( !bFastMove || pZone->moveFastPC(pVampire, pVampire->getX(), pVampire->getY(), pTargetCreature->getX(), pTargetCreature->getY(), getSkillType()) ))*/
		{
			SkillInput input(pVampire);
			SkillOutput output;
			computeOutput(input, output);

			Damage_t Damage = output.Damage;
			bool bCriticalHit = false;
			Damage += computeDamage(pVampire, pTargetCreature, 0, bCriticalHit);

			// 마나를 깍는다.
			decreaseMana(pVampire, RequiredMP, _GCSkillToObjectOK1);
		
			EffectSetAfire* pEffect = new EffectSetAfire(pTargetCreature);
			pEffect->setDamage(Damage);
			pEffect->setTick(3);
			pEffect->setNextTime(3);
			pEffect->setTimes(3);
			pEffect->setCasterOID( pVampire->getObjectID() );
			pTargetCreature->addEffect( pEffect );

			increaseAlignment(pVampire, pTargetCreature, _GCSkillToObjectOK1);

			// 패킷을 보낸다.
			_GCSkillToObjectOK1.setSkillType(getSkillType());
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(0);

			_GCSkillToObjectOK2.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK2.setSkillType(getSkillType());
			_GCSkillToObjectOK2.setDuration(0);

			_GCSkillToObjectOK5.setObjectID(pVampire->getObjectID());
			_GCSkillToObjectOK5.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK5.setSkillType(getSkillType());

			pPlayer->sendPacket(&_GCSkillToObjectOK1);

			Player* pTargetPlayer = NULL;

			if (pTargetCreature->isPC()) 
			{
				pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);
				pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
			} 
			else 
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				pMonster->addEnemy(pVampire);
			}

			list<Creature*> cList;
			cList.push_back(pVampire);
			cList.push_back(pTargetCreature);

			cList = pZone->broadcastSkillPacket(pVampire->getX(), pVampire->getY(),
				pTargetCreature->getX(), pTargetCreature->getY(), &_GCSkillToObjectOK5, cList);

			pVampireSkillSlot->setRunTime(output.Delay);
		} 
		else
		{
			executeSkillFailNormal(pVampire, getSkillType(), pTargetCreature );
		}
	}
	catch(Throwable & t)
	{
		executeSkillFailException( pVampire, getSkillType() );
	}

	__END_CATCH
}

void BloodyScarify::eatCorpse(Vampire* pVampire, Item* pCorpse, VampireSkillSlot* pVampireSkillSlot)
{
	__BEGIN_TRY

	if ( pCorpse->getItemClass() != Item::ITEM_CLASS_CORPSE || pCorpse->getItemType() == VAMPIRE_CORPSE )
	{
		executeSkillFailException( pVampire, getSkillType() );
		return;
	}

	if ( pCorpse != NULL
		&& pCorpse->getItemClass() == Item::ITEM_CLASS_CORPSE
		&& pCorpse->getItemType() == MONSTER_CORPSE )
	{
		MonsterCorpse* pMonsterCorpse = dynamic_cast<MonsterCorpse*>(pCorpse);
		Assert( pMonsterCorpse != NULL );

		if ( pMonsterCorpse->isFlag( Effect::EFFECT_CLASS_SLAYER_RELIC_TABLE )
			|| pMonsterCorpse->isFlag( Effect::EFFECT_CLASS_VAMPIRE_RELIC_TABLE )
			|| pMonsterCorpse->getMonsterType() == 482
			|| pMonsterCorpse->getMonsterType() == 650
			|| pMonsterCorpse->isShrine() )
		{
			executeSkillFailException( pVampire, getSkillType() );
			return;
		}
	}

	Corpse* pTargetCorpse = dynamic_cast<Corpse*>(pCorpse);
	Assert( pTargetCorpse != NULL );

	Zone* pZone = pVampire->getZone();

	GCSkillToObjectOK1 _GCSkillToObjectOK1;
	GCSkillToObjectOK5 _GCSkillToObjectOK5;

	SkillType_t       SkillType  = pVampireSkillSlot->getSkillType();
	SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);
	Range_t			  Range		 = pSkillInfo->getRange();

	int  RequiredMP         = decreaseConsumeMP(pVampire, pSkillInfo);
	bool bManaCheck         = hasEnoughMana(pVampire, RequiredMP);
	bool bTimeCheck         = verifyRunTime(pVampireSkillSlot);
	bool bRangeCheck        = getDistance( pVampire->getX(), pVampire->getY(), pTargetCorpse->getX(), pTargetCorpse->getY() ) <= Range;

	if ( bManaCheck && bTimeCheck && bRangeCheck )
	{
		SkillInput input(pVampire);
		SkillOutput output;
		computeOutput(input, output);

		int RegenPeriod = 100;
		int Period = 15;
		int RegenHPUnit = 30;
		int Deadline = RegenPeriod * Period;

		if (pVampire->isFlag(Effect::EFFECT_CLASS_HP_RECOVERY))
		{
			Effect*     pEffect           = pVampire->findEffect(Effect::EFFECT_CLASS_HP_RECOVERY);
			EffectHPRecovery* pEffectHPRecoveryEffect = dynamic_cast<EffectHPRecovery*>(pEffect);

			// 몇번 더 해야 한다는 것을 갱신해 준다.
			Turn_t OldCount  = pEffectHPRecoveryEffect->getPeriod();
			Turn_t NewPeriod = OldCount + Period;
			pEffectHPRecoveryEffect->setPeriod(NewPeriod);
			pEffectHPRecoveryEffect->setDeadline(NewPeriod* RegenPeriod);

			// 회복 시작하라는 패킷을 자신에게 보낸다.
			GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
			gcHPRecoveryStartToSelf.setPeriod(NewPeriod); // 몇번 회복하나?
			gcHPRecoveryStartToSelf.setDelay(RegenPeriod); // 몇 초 단위로 하나?
			gcHPRecoveryStartToSelf.setQuantity(RegenHPUnit); // 한번에 얼마나 회복하나?

			pVampire->getPlayer()->sendPacket(&gcHPRecoveryStartToSelf);

			// 회복 시작하라는 패킷을 다른이들에게 보낸다.
			// 회복 갱신 패킷, 시작과 똑 같은 패킷을 보낸다.
			GCHPRecoveryStartToOthers gcHPRecoveryStartToOthers;
			gcHPRecoveryStartToOthers.setObjectID(pVampire->getObjectID());
			gcHPRecoveryStartToOthers.setPeriod(NewPeriod);
			gcHPRecoveryStartToOthers.setDelay(RegenPeriod );
			gcHPRecoveryStartToOthers.setQuantity(RegenHPUnit);

			pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcHPRecoveryStartToOthers, pVampire);
		}
		else
		{
			EffectHPRecovery* pEffectHPRecovery = new EffectHPRecovery();

			pEffectHPRecovery->setTarget(pVampire);
			pEffectHPRecovery->setDeadline(Deadline);
			pEffectHPRecovery->setDelay(RegenPeriod);
			pEffectHPRecovery->setNextTime(0);
			pEffectHPRecovery->setHPQuantity(RegenHPUnit);
			pEffectHPRecovery->setPeriod(Period);

			pVampire->addEffect(pEffectHPRecovery);

			// 회복 시작하라는 패킷을 자신에게 보낸다.
			GCHPRecoveryStartToSelf gcHPRecoveryStartToSelf;
			gcHPRecoveryStartToSelf.setPeriod(Period);
			gcHPRecoveryStartToSelf.setDelay(RegenPeriod);
			gcHPRecoveryStartToSelf.setQuantity(RegenHPUnit);

			pVampire->getPlayer()->sendPacket(&gcHPRecoveryStartToSelf);

			// 회복 시작하라는 패킷을 보는이들에게 보낸다.
			GCHPRecoveryStartToOthers gcHPRecoveryStartToOthers;
			gcHPRecoveryStartToOthers.setObjectID(pVampire->getObjectID());
			gcHPRecoveryStartToOthers.setPeriod(Period);
			gcHPRecoveryStartToOthers.setDelay(RegenPeriod);
			gcHPRecoveryStartToOthers.setQuantity(RegenHPUnit);

			pZone->broadcastPacket(pVampire->getX(), pVampire->getY(), &gcHPRecoveryStartToOthers, pVampire);
		}

		// 패킷을 보낸다.
		_GCSkillToObjectOK1.setSkillType(getSkillType());
		_GCSkillToObjectOK1.setCEffectID(0);
		_GCSkillToObjectOK1.setTargetObjectID(pTargetCorpse->getObjectID());
		_GCSkillToObjectOK1.setDuration(0);
		_GCSkillToObjectOK1.setGrade(1);

		_GCSkillToObjectOK5.setObjectID(pVampire->getObjectID());
		_GCSkillToObjectOK5.setTargetObjectID(pTargetCorpse->getObjectID());
		_GCSkillToObjectOK5.setSkillType(getSkillType());
		_GCSkillToObjectOK5.setGrade(1);

		pVampire->getPlayer()->sendPacket(&_GCSkillToObjectOK1);

		list<Creature*> cList;
		cList.push_back(pVampire);

		cList = pZone->broadcastSkillPacket(pVampire->getX(), pVampire->getY(),
			pTargetCorpse->getX(), pTargetCorpse->getY(), &_GCSkillToObjectOK5, cList);

		pVampireSkillSlot->setRunTime(output.Delay);

		// 사라지는 패킷을 날린다.
		GCDeleteObject gcDO;
		gcDO.setObjectID(pTargetCorpse->getObjectID());
		pZone->broadcastPacket(pTargetCorpse->getX(), pTargetCorpse->getY(),  &gcDO);
		// 존에서 지운다.
		pZone->deleteItem(pTargetCorpse , pTargetCorpse->getX() , pTargetCorpse->getY());
		// 존안에서 실제적으로 포인터를 없애지는 않으므로 포인터를 삭제 시켜 줘야 한다.
		SAFE_DELETE(pTargetCorpse);
	}

	__END_CATCH
}

void BloodyScarify::eatComaCreature(Vampire* pVampire, Creature* pComaCreature)
{
	executeSkillFailNormal(pVampire, getSkillType(), pComaCreature );
}

BloodyScarify g_BloodyScarify;
