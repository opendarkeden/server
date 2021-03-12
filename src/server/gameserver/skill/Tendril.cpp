//////////////////////////////////////////////////////////////////////////////
// Filename    : Tendril.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "Tendril.h"
#include "EffectTendril.h"
#include "EffectProtectionFromCurse.h"
#include "RankBonus.h"

#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToObjectOK6.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCRemoveEffect.h"
#include "Reflection.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void Tendril::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID)
	
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

		Item* pWeapon = pOusters->getWearItem(Ousters::WEAR_RIGHTHAND);
		if (pWeapon == NULL || pWeapon->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
		{
			executeSkillFailException(pOusters, pSkillSlot->getSkillType());
			return;
		}

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NPC는 공격할 수 없다.
		// 저주 면역. by sigi. 2002.9.13
		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL
			|| pTargetCreature->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_CURSE)
			|| !canAttack( pOusters, pTargetCreature )
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

		Tile& rTile = pZone->getTile( pTargetCreature->getX(), pTargetCreature->getY() );

		int  RequiredMP  = (int)pSkillInfo->getConsumeMP() + pSkillSlot->getExpLevel();
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, pTargetCreature, output.Range);

		int Ratio = 0;

		if ( input.SkillLevel <= 15 )
		{
			Ratio = pOusters->getLevel() + input.SkillLevel * 8 / 3 - pTargetCreature->getLevel();
		}
		else
		{
			Ratio = pOusters->getLevel() + 20 + input.SkillLevel * 4 / 3 - pTargetCreature->getLevel();
			if ( input.SkillLevel == 30 ) Ratio *= 1.1;
		}

		Ratio = min( 80, max( 20, Ratio ) );

		bool bHitRoll	 = (rand()%100) < Ratio;
		bool bHitRoll2   = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pSkillSlot);
		bool bCanHit     = canHit(pOusters, pTargetCreature, SkillType);
		bool bEffected   = pTargetCreature->isFlag(Effect::EFFECT_CLASS_TENDRIL) || rTile.getEffect(Effect::EFFECT_CLASS_TRYING_POSITION)!=NULL;
		bool bPK         = verifyPK(pOusters, pTargetCreature);
		bool bSatisfyRequire = pOusters->satisfySkillRequire( pSkillInfo );

		ZoneCoord_t targetX = pTargetCreature->getX();
		ZoneCoord_t targetY = pTargetCreature->getY();
		ZoneCoord_t myX     = pOusters->getX();
		ZoneCoord_t myY     = pOusters->getY();

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bHitRoll2 && bCanHit && !bEffected && bPK && bSatisfyRequire)
		{
			decreaseMana(pOusters, RequiredMP, _GCSkillToObjectOK1);

        	bool bCanSeeCaster = canSee(pTargetCreature, pOusters);

			// 이펙트 오브젝트를 생성해 붙인다.
			EffectTendril* pEffect = new EffectTendril(pTargetCreature);
			pEffect->setDeadline(output.Duration);
			//pEffect->setLevel(pSkillSlot->getExpLevel());
			pTargetCreature->addEffect(pEffect);
			pTargetCreature->setFlag(Effect::EFFECT_CLASS_TENDRIL);
			pTargetCreature->setFlag(Effect::EFFECT_CLASS_NO_DAMAGE);

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

			GCAddEffect gcAddEffect;
			gcAddEffect.setObjectID(TargetObjectID);
			gcAddEffect.setEffectID(Effect::EFFECT_CLASS_TENDRIL);
			gcAddEffect.setDuration(output.Duration);
			pZone->broadcastPacket(targetX, targetY, &gcAddEffect);
			
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

Tendril g_Tendril;
