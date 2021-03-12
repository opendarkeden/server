//////////////////////////////////////////////////////////////////////////////
// Filename    : DestructionSpear.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "DestructionSpear.h"
#include "SimpleTileMissileSkill.h"
#include "RankBonus.h"
#include "Gpackets/GCAddEffect.h"
#include "Gpackets/GCModifyInformation.h"
#include "Player.h"
#include "EffectDestructionSpear.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void DestructionSpear::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

    try
    {
		Zone* pZone = pOusters->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);

		// NoSuch제거. by sigi. 2002.5.2
		if (pTargetCreature==NULL)
		{
			executeSkillFailException(pOusters, getSkillType());

			return;
		}

		execute(pOusters, pTargetCreature->getX(), pTargetCreature->getY(), pOustersSkillSlot, CEffectID);
    } 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType());
        //cout << t.toString() << endl;
    }

	__END_CATCH
}

void DestructionSpear::execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	Zone* pZone = pOusters->getZone();
	Assert( pZone != NULL );

/*	Creature* pTargetCreature = pZone->getCreature( TargetObjectID );

	if (pTargetCreature==NULL
		|| !canAttack( pOusters, pTargetCreature )
		|| pTargetCreature->isNPC())
	{
		executeSkillFailException(pOusters, getSkillType());
		return;
	}*/

/*	if ( pTargetCreature->isSlayer() )
	{
		Slayer* pSlayer = dynamic_cast<Slayer*>(pTargetCreature);
		targetLevel = pSlayer->getHighestSkillDomainLevel();
	}
	else
	{
		targetLevel = pTargetCreature->getLevel();
	}*/

	SkillInput input(pOusters, pOustersSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	Item* pWeapon = pOusters->getWearItem( Ousters::WEAR_RIGHTHAND );
	if ( pWeapon == NULL )
	{
		executeSkillFailException( pOusters, getSkillType() );
		return;
	}

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;

	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_OUSTERS_CHAKRAM;
	param.STRMultiplier = 0;
	param.DEXMultiplier = 0;
	param.INTMultiplier = 0;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd = true;

	SIMPLE_SKILL_OUTPUT result;

	int offset = 0;

	OustersSkillSlot* pMastery = pOusters->hasSkill( SKILL_DESTRUCTION_SPEAR_MASTERY );
	if ( pMastery != NULL )
	{
		offset = 1;
		if ( pMastery->getExpLevel() <= 15 )
			param.SkillDamage = min(70,param.SkillDamage + 10 + pMastery->getExpLevel()/3);
		else
			param.SkillDamage = min(90,param.SkillDamage + 10 + pMastery->getExpLevel()/2);
		param.Grade=4;
	}

	for ( int i=-offset; i<=offset; ++i )
	for ( int j=-offset; j<=offset; ++j )
		param.addMask( i, j, 100 );

	g_SimpleTileMissileSkill.execute(pOusters, X, Y, pOustersSkillSlot, param, result, CEffectID );

	list<Creature*>::iterator itr = result.targetCreatures.begin();
	for ( ; itr != result.targetCreatures.end() ; ++itr )
	{
		Creature* pTargetCreature = *itr;
		if ( pTargetCreature->getX() == X && pTargetCreature->getY() == Y )
		{
			GCModifyInformation gcMI, gcAttackerMI;
			Damage_t damage = computeElementalCombatSkill( pOusters, pTargetCreature, gcAttackerMI );
			if ( damage != 0 )
			{
				::setDamage( pTargetCreature, damage, pOusters, SKILL_DESTRUCTION_SPEAR, &gcMI, &gcAttackerMI );
				if ( pTargetCreature->isPC() ) pTargetCreature->getPlayer()->sendPacket( &gcMI );

				if (pTargetCreature->isDead())
				{
					int exp = computeCreatureExp(pTargetCreature, 70, pOusters);
					shareOustersExp(pOusters, exp, gcAttackerMI);
				}

				pOusters->getPlayer()->sendPacket( &gcAttackerMI );
			}
		}

		if ( !pTargetCreature->isFlag( Effect::EFFECT_CLASS_DESTRUCTION_SPEAR ) && result.bSuccess )
		{
			int targetLevel = pTargetCreature->getLevel();
			int ratio = 0;

			if ( input.SkillLevel <= 15 )
			{
				ratio = max(20, min(80, (int)( pOusters->getLevel() + (input.SkillLevel * 8.0 / 3.0) - targetLevel ) ));
			}
			else
			{
				ratio = max(20, min(80, (int)( pOusters->getLevel() + 20.0 + (input.SkillLevel * 4.0 / 3.0) - targetLevel ) ));
			}

			if ( rand() % 100 < ratio )
			{

				EffectDestructionSpear* pEffect = new EffectDestructionSpear( pTargetCreature );
				Assert( pEffect != NULL );

				pEffect->setDamage( 2 + ( input.SkillLevel/3 ) );
				pEffect->setNextTime(20);
				pEffect->setCasterID( pOusters->getObjectID() );
				pEffect->setDeadline( output.Duration );

				if ( pTargetCreature->getX() == X && pTargetCreature->getY() == Y )
					pEffect->setSteal(true);

				pTargetCreature->setFlag( Effect::EFFECT_CLASS_DESTRUCTION_SPEAR );
				pTargetCreature->addEffect( pEffect );

				GCAddEffect gcAddEffect;
				gcAddEffect.setObjectID( pTargetCreature->getObjectID() );
				gcAddEffect.setEffectID( pEffect->getSendEffectClass() );
				gcAddEffect.setDuration( output.Duration );

				pZone->broadcastPacket( pTargetCreature->getX(), pTargetCreature->getY(), &gcAddEffect );
			}
		}
	}

	__END_CATCH
}

DestructionSpear g_DestructionSpear;
