//////////////////////////////////////////////////////////////////////////////
// Filename    : MagnumSpear.cpp
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "MagnumSpear.h"
#include "RankBonus.h"
#include "EffectMagnumSpear.h"
#include "SkillUtil.h"
#include "Gpackets/GCSkillToObjectOK1.h"
#include "Gpackets/GCSkillToObjectOK2.h"
#include "Gpackets/GCSkillToObjectOK3.h"
#include "Gpackets/GCSkillToObjectOK4.h"
#include "Gpackets/GCSkillToObjectOK5.h"
#include "Gpackets/GCSkillToObjectOK6.h"

//////////////////////////////////////////////////////////////////////////////
// 아우스터즈 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void MagnumSpear::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
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

		Item* pWeapon = pOusters->getWearItem( Ousters::WEAR_RIGHTHAND );
		if (pWeapon == NULL || pWeapon->getItemClass() != Item::ITEM_CLASS_OUSTERS_WRISTLET || !pOusters->isRealWearingEx(Ousters::WEAR_RIGHTHAND))
		{
			executeSkillFailException(pOusters, pOustersSkillSlot->getSkillType());
			return;
		}

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		SkillType_t SkillType = pOustersSkillSlot->getSkillType();

		// NPC는 공격할 수가 없다.
		if (pTargetCreature==NULL
			|| !canAttack( pOusters, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pOusters, SkillType);
			return;
		}

		GCSkillToObjectOK1 _GCSkillToObjectOK1;
		GCSkillToObjectOK2 _GCSkillToObjectOK2;
		GCSkillToObjectOK3 _GCSkillToObjectOK3;
		GCSkillToObjectOK4 _GCSkillToObjectOK4;
		GCSkillToObjectOK5 _GCSkillToObjectOK5;
		GCSkillToObjectOK6 _GCSkillToObjectOK6;

		SkillInfo* pSkillInfo = g_pSkillInfoManager->getSkillInfo(SkillType);

		
		int HitBonus = 0;
		/*
		if ( pOusters->hasRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_ACID ) )
		{
			RankBonus* pRankBonus = pOusters->getRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_ACID );
			Assert( pRankBonus != NULL );

			HitBonus = pRankBonus->getPoint();
		}
		*/


		int  RequiredMP  = (int)(pSkillInfo->getConsumeMP() + pOustersSkillSlot->getExpLevel()/3);
		bool bManaCheck  = hasEnoughMana(pOusters, RequiredMP);
		bool bTimeCheck  = verifyRunTime(pOustersSkillSlot);
		bool bRangeCheck = verifyDistance(pOusters, pTargetCreature, pSkillInfo->getRange());
		bool bHitRoll    = HitRoll::isSuccessMagic(pOusters, pSkillInfo, pOustersSkillSlot, HitBonus);
		bool bCanHit     = canHit(pOusters, pTargetCreature, SkillType);
		bool bPK         = verifyPK(pOusters, pTargetCreature);
		bool bEffect	 = pTargetCreature->isFlag( Effect::EFFECT_CLASS_MAGNUM_SPEAR );

		if (bManaCheck && bTimeCheck && bRangeCheck && bHitRoll && bCanHit && bPK && !bEffect)
		{
			ZoneCoord_t oustX   = pOusters->getX();
			ZoneCoord_t oustY   = pOusters->getY();
			ZoneCoord_t targetX = pTargetCreature->getX();
			ZoneCoord_t targetY = pTargetCreature->getY();

			decreaseMana(pOusters, RequiredMP, _GCSkillToObjectOK1);
			bool bCanSeeCaster = canSee(pTargetCreature, pOusters);

			SkillInput input(pOusters, pOustersSkillSlot);
			SkillOutput output;
			computeOutput(input, output);

			Damage_t Damage = output.Damage;

			OustersSkillSlot* pMastery = pOusters->hasSkill( SKILL_MAGNUM_SPEAR_MASTERY );
			if ( pMastery != NULL )
			{
				Damage += ( pMastery->getExpLevel() * 5 / 3 ) + 15;
			}
			else
			{
				bool dummy;
				computeCriticalBonus(pOusters, getSkillType(), Damage, dummy);
			}

			EffectMagnumSpear* pEffect = new EffectMagnumSpear( pTargetCreature );
			pEffect->setDamage( computeOustersMagicDamage( pOusters, pTargetCreature, Damage, SKILL_MAGNUM_SPEAR ) );

			int spearNum = 2;

			if ( pOustersSkillSlot->getExpLevel() <= 15 )
				spearNum = 2;
			else if ( pOustersSkillSlot->getExpLevel() < 30 )
				spearNum = 4;
			else if ( pOustersSkillSlot->getExpLevel() == 30 )
				spearNum = 6;

			int Grade = spearNum/2 - 1;

			if ( pMastery != NULL ) 
			{
				spearNum = 1;
				Grade = 4;
				output.Delay = 20;
			}

			pEffect->setTimes(spearNum);
			pEffect->setTick(5);
			pEffect->setNextTime(5);
			pEffect->setCasterOID( pOusters->getObjectID() );

			pTargetCreature->addEffect( pEffect );
			pTargetCreature->setFlag( pEffect->getEffectClass() );

			_GCSkillToObjectOK1.setSkillType(SkillType);
			_GCSkillToObjectOK1.setCEffectID(CEffectID);
			_GCSkillToObjectOK1.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK1.setDuration(0);
			_GCSkillToObjectOK1.setGrade(Grade);
		
			_GCSkillToObjectOK2.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK2.setSkillType(SkillType);
			_GCSkillToObjectOK2.setDuration(0);
			_GCSkillToObjectOK2.setGrade(Grade);
			
			_GCSkillToObjectOK3.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK3.setSkillType(SkillType);
			_GCSkillToObjectOK3.setTargetXY(targetX, targetY);
			_GCSkillToObjectOK3.setGrade(Grade);
		
			_GCSkillToObjectOK4.setSkillType(SkillType);
			_GCSkillToObjectOK4.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK4.setGrade(Grade);

			_GCSkillToObjectOK5.setObjectID(pOusters->getObjectID());
			_GCSkillToObjectOK5.setTargetObjectID(TargetObjectID);
			_GCSkillToObjectOK5.setSkillType(SkillType);
			_GCSkillToObjectOK5.setGrade(Grade);
			
			_GCSkillToObjectOK6.setXY(oustX, oustY);
			_GCSkillToObjectOK6.setSkillType(SkillType);
			_GCSkillToObjectOK6.setDuration(0);
			_GCSkillToObjectOK6.setGrade(Grade);

			pPlayer->sendPacket(&_GCSkillToObjectOK1);
		
			Player* pTargetPlayer = NULL;
			if (pTargetCreature->isPC()) 
			{
				pTargetPlayer = pTargetCreature->getPlayer();
				Assert(pTargetPlayer != NULL);
				if (bCanSeeCaster) pTargetPlayer->sendPacket(&_GCSkillToObjectOK2);
				else pTargetPlayer->sendPacket(&_GCSkillToObjectOK6);
			} 
			else 
			{
				Monster* pMonster = dynamic_cast<Monster*>(pTargetCreature);
				pMonster->addEnemy(pOusters);
			}

			list<Creature*> cList;
			cList.push_back(pOusters);
			cList.push_back(pTargetCreature);

			cList = pZone->broadcastSkillPacket(oustX, oustY, targetX, targetY, &_GCSkillToObjectOK5, cList);
			
			pZone->broadcastPacket(oustX, oustY,  &_GCSkillToObjectOK3 , cList);
			pZone->broadcastPacket(targetX, targetY,  &_GCSkillToObjectOK4 , cList);

			pOustersSkillSlot->setRunTime(output.Delay);

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

	__END_CATCH
}

MagnumSpear g_MagnumSpear;
