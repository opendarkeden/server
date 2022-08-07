//////////////////////////////////////////////////////////////////////////////
// Filename    : PenetrateWheel.cpp
// Written by  : rallser
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "PenetrateWheel.h"
#include "SimpleTileMissileSkill.h"
#include "EffectPenetrateWheel.h"
#include "GCAddEffect.h"
#include "RankBonus.h"

#include "GCSkillToTileOK1.h"
#include "GCSkillToTileOK2.h"
#include "GCSkillToTileOK3.h"
#include "GCSkillToTileOK4.h"
#include "GCSkillToTileOK5.h"
#include "GCSkillToTileOK6.h"
#include "GCAddEffectToTile.h"

//////////////////////////////////////////////////////////////////////////////
// 아우스터즈 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void PenetrateWheel::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
    
{
    __BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << "begin " << endl;

	Assert(pOusters != NULL);
	Assert(pOustersSkillSlot != NULL);

    try
    {
		Zone* pZone = pOusters->getZone();
		Assert(pZone != NULL);

		Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
		//Assert(pTargetCreature != NULL);


		// NPC는 공격할 수가 없다.
		if (pTargetCreature==NULL	// NoSuch제거 때문에.. by sigi. 2002.5.2
			|| !canAttack( pOusters, pTargetCreature )
			|| pTargetCreature->isNPC())
		{
			executeSkillFailException(pOusters, getSkillType(), 0 );
			//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;
			return;
		}

		execute(pOusters, pTargetCreature->getX(), pTargetCreature->getY(), pOustersSkillSlot, CEffectID);
    } 
	catch (Throwable & t) 
	{
		executeSkillFailException(pOusters, getSkillType(), 0 );
        //cout << t.toString() << endl;
    }

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " end " << endl;

    __END_CATCH
}

void PenetrateWheel::execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
{
	__BEGIN_TRY

	Zone* pZone = pOusters->getZone();
	Assert( pZone != NULL );

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

	int offset = 1;
	param.Grade=4;

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
				::setDamage( pTargetCreature, damage, pOusters, SKILL_Penetrate_Wheel, &gcMI, &gcAttackerMI );
				if ( pTargetCreature->isPC() ) pTargetCreature->getPlayer()->sendPacket( &gcMI );

				if (pTargetCreature->isDead())
				{
					int exp = computeCreatureExp(pTargetCreature, 70, pOusters);
					shareOustersExp(pOusters, exp, gcAttackerMI);
				}

				pOusters->getPlayer()->sendPacket( &gcAttackerMI );
			}
		}

		if ( !pTargetCreature->isFlag( Effect::EFFECT_CLASS_Penetrate_Wheel ) && result.bSuccess )
		{
			int targetLevel = pTargetCreature->getLevel();
			int ratio = 0;

			ratio = max(20, min(80, (int)( pOusters->getLevel() + 60.0 ) - targetLevel ) );
			
			if ( rand() % 100 < ratio )
			{

			  EffectPenetrateWheel* pEffect = new EffectPenetrateWheel( pTargetCreature );
				Assert( pEffect != NULL );

				pEffect->setDamage( 15 ); // 
				pEffect->setNextTime(20);
				// pEffect->setCasterID( pOusters->getObjectID() );
				pEffect->setDeadline( output.Duration );

				// if ( pTargetCreature->getX() == X && pTargetCreature->getY() == Y )
				// 	pEffect->setSteal(true);

				pTargetCreature->setFlag( Effect::EFFECT_CLASS_Penetrate_Wheel );
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

PenetrateWheel g_PenetrateWheel;
