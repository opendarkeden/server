//////////////////////////////////////////////////////////////////////////////
// Filename    : DeleoEfficio.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "DeleoEfficio.h"
#include "Effect.h"

#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToObjectOK6.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void DeleoEfficio::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY
		
	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pOusters != NULL);
	Assert(pSkillSlot != NULL);
	
	try 
	{
		Player* pPlayer = pOusters->getPlayer();
		Zone* pZone = pOusters->getZone();
		Assert(pPlayer != NULL);
		Assert(pZone != NULL);

/*		Item* pWeapon = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
		if (pWeapon == NULL || pWeapon->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
		{
			executeSkillFailException(pOusters, pSkillSlot->getSkillType());
			return;
		}*/

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NPC는 공격할 수 없다.
		// 저주 면역. by sigi. 2002.9.13
		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pOusters, getSkillType());
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;
		GCSkillToObjectOK6 _GCSkillToObjectOK6;

		SkillType_t SkillType  = pSkillSlot->getSkillType();
		SkillInfo*  pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		SkillInput input(pOusters, pSkillSlot);
		SkillOutput output;
		computeOutput(input, output);

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP();
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, pTargetCreature, pSkillInfo->getRange());

		int Ratio = 50 + pOusters->getLevel() - pTargetCreature->getLevel();
		cout << "Deleo Efficio Ratio : " << Ratio << endl;

		bool bHitRoll	 = (rand()%100) < Ratio;
		bool bHitRoll2   = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pSkillSlot);
		bool bCanHit     = canHit(pOusters, pTargetCreature, SkillType);
		bool bPK         = verifyPK(pOusters, pTargetCreature);

		ZoneCoord_t targetX = pTargetCreature->getX();
		ZoneCoord_t targetY = pTargetCreature->getY();
		ZoneCoord_t myX     = pOusters->getX();
		ZoneCoord_t myY     = pOusters->getY();

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bHitRoll2 && bCanHit && bPK)
		{
			decreaseMana(pOusters, RequiredMP, _GCSkillToObjectOK1);
			cout << pTargetCreature->getName() << " deleo efficio" << endl;

        	bool bCanSeeCaster = canSee(pTargetCreature, pOusters);

			static Effect::EffectClass targetEffects[] =
			{
				Effect::EFFECT_CLASS_HIDE,
				Effect::EFFECT_CLASS_TRANSFORM_TO_BAT,
				Effect::EFFECT_CLASS_TRANSFORM_TO_WOLF,
				Effect::EFFECT_CLASS_INVISIBILITY,
				Effect::EFFECT_CLASS_EXTREME,
				Effect::EFFECT_CLASS_PARALYZE,
				Effect::EFFECT_CLASS_DOOM,
				Effect::EFFECT_CLASS_SEDUCTION,
				Effect::EFFECT_CLASS_DEATH,
				Effect::EFFECT_CLASS_HALLUCINATION,
				Effect::EFFECT_CLASS_MEPHISTO,
				Effect::EFFECT_CLASS_GREEN_POISON,
				Effect::EFFECT_CLASS_POISON,
				Effect::EFFECT_CLASS_YELLOW_POISON_TO_CREATURE,
				Effect::EFFECT_CLASS_GREEN_STALKER,
				Effect::EFFECT_CLASS_DARKBLUE_POISON_TO_CREATURE,
				Effect::EFFECT_CLASS_RING_OF_FLARE,
				Effect::EFFECT_CLASS_HANDS_OF_FIRE,
				Effect::EFFECT_CLASS_EVADE,
				Effect::EFFECT_CLASS_CROSS_GUARD,
				Effect::EFFECT_CLASS_DIVINE_SPIRITS,
				Effect::EFFECT_CLASS_SHARP_CHAKRAM,
				Effect::EFFECT_CLASS_WATER_BARRIER,
				Effect::EFFECT_CLASS_FIRE_ELEMENTAL,
				Effect::EFFECT_CLASS_WATER_ELEMENTAL,
				Effect::EFFECT_CLASS_FROZEN_ARMOR,
				Effect::EFFECT_CLASS_FROZEN_ARMOR_TO_ENEMY,
				Effect::EFFECT_CLASS_SUMMON_SYLPH,
				Effect::EFFECT_CLASS_TENDRIL,
				Effect::EFFECT_CLASS_GNOMES_WHISPER,
				Effect::EFFECT_CLASS_REACTIVE_ARMOR,
				Effect::EFFECT_CLASS_GROUND_BLESS,
				Effect::EFFECT_CLASS_CROSS_COUNTER,
				Effect::EFFECT_CLASS_SHARP_SHIELD_1,
				Effect::EFFECT_CLASS_POTENTIAL_EXPLOSION,
				Effect::EFFECT_CLASS_CHARGING_POWER,
				Effect::EFFECT_CLASS_BERSERKER,
				Effect::EFFECT_CLASS_AIR_SHIELD_1,
				Effect::EFFECT_CLASS_CONCEALMENT,
				Effect::EFFECT_CLASS_REVEALER,
				Effect::EFFECT_CLASS_PROTECTION_FROM_POISON,
				Effect::EFFECT_CLASS_PROTECTION_FROM_CURSE,
				Effect::EFFECT_CLASS_PROTECTION_FROM_BLOOD,
				Effect::EFFECT_CLASS_PROTECTION_FROM_ACID,
				Effect::EFFECT_CLASS_DENIAL_MAGIC,
				Effect::EFFECT_CLASS_ACTIVATION,
				Effect::EFFECT_CLASS_LIGHT,
				Effect::EFFECT_CLASS_DETECT_HIDDEN,
				Effect::EFFECT_CLASS_DETECT_INVISIBILITY,
				Effect::EFFECT_CLASS_BLESS,
				Effect::EFFECT_CLASS_HEART_CATALYST,
				Effect::EFFECT_CLASS_GHOST_BLADE,
				Effect::EFFECT_CLASS_STRIKING,
				Effect::EFFECT_CLASS_REQUITAL,
				Effect::EFFECT_CLASS_AURA_SHIELD,
				Effect::EFFECT_CLASS_SLEEP,
				Effect::EFFECT_CLASS_SPIRIT_GUARD_1,
				Effect::EFFECT_CLASS_SPIRIT_GUARD_2,
				Effect::EFFECT_CLASS_SPIRIT_GUARD_3,
				Effect::EFFECT_CLASS_SPIRIT_GUARD_4,
				Effect::EFFECT_CLASS_DIVINE_GUIDANCE,
				Effect::EFFECT_CLASS_LIGHTNESS,
				Effect::EFFECT_CLASS_HOLY_ARMOR,
				Effect::EFFECT_CLASS_OBSERVING_EYE,
				Effect::EFFECT_CLASS_EXPANSION,
				Effect::EFFECT_CLASS_SACRIFICE,
				Effect::EFFECT_CLASS_TRANSFORM_TO_WERWOLF,
				Effect::EFFECT_CLASS_DARKBLUE_POISON,
				Effect::EFFECT_CLASS_CASKET,
				Effect::EFFECT_CLASS_STONE_SKIN,
				Effect::EFFECT_CLASS_DANCING_SWORD,
				Effect::EFFECT_CLASS_SNIPING_MODE,
				Effect::EFFECT_CLASS_REDIANCE,
				Effect::EFFECT_CLASS_MAX
			};

			for ( int i=0; targetEffects[i] != Effect::EFFECT_CLASS_MAX; ++i )
			{
				if ( pTargetCreature->isFlag( targetEffects[i] ) )
				{
					Effect* pEffect = pTargetCreature->findEffect( targetEffects[i] );
					if ( pEffect != NULL ) pEffect->setDeadline(0);
				}
			}

			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(output.Duration);
		
			_GCSkillToObjectOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
			_GCSkillToObjectOK2.setDuration(output.Duration);
		
			_GCSkillToObjectOK3.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK3.setSkillType(SkillType);
			_GCSkillToObjectOK3.setTargetXY (targetX, targetY);
			
			_GCSkillToObjectOK4.setSkillType(SkillType);
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK4.setDuration(output.Duration);
			
			_GCSkillToObjectOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setTargetObjectID (TargetObjectID);
			_GCSkillToObjectOK5.setDuration(output.Duration);
			
			_GCSkillToObjectOK6.setXY(myX, myY);
			_GCSkillToObjectOK6.setSkillType(SkillType);
			_GCSkillToObjectOK6.setDuration(output.Duration);

			list<Creature *> cList;
			cList.push_back(pTargetCreature);
			cList.push_back(pOusters);
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
				pTargetMonster->addEnemy(pOusters);
			}
		
			pSkillSlot->setRunTime(output.Delay);
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

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

	__END_CATCH
}

DeleoEfficio g_DeleoEfficio;
