//////////////////////////////////////////////////////////////////////////////
// Filename    : BackStab.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "BackStab.h"
#include "SimpleMeleeSkill.h"
#include "RankBonus.h"
#include "Gpackets/GCAddEffect.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void BackStab::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

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
//	param.SkillDamage   = output.Damage;

	bool bCritical = false;
	if ( HitRoll::isSuccessBackStab( pOusters ) )
	{
		double ratio = ( 1.0 + ( 2 * input.SkillLevel / 30.0 ) );
		param.SkillDamage = max( 1, Random( pWeapon->getMinDamage(), pWeapon->getMaxDamage() ) ) * ratio;
		if ( input.SkillLevel == 30 ) param.SkillDamage *= 1.1;
		bCritical = true;
	}
	else
	{
		param.SkillDamage = 0;
	}

	param.Delay         = 0;
	param.ItemClass     = Item::ITEM_CLASS_OUSTERS_CHAKRAM;
	param.STRMultiplier = 0;
	param.DEXMultiplier = 0;
	param.INTMultiplier = 0;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd = true;

	if ( input.SkillLevel < 15 ) param.Grade = 0;
	else if ( input.SkillLevel < 30 ) param.Grade = 1;
	else param.Grade = 2;

	SIMPLE_SKILL_OUTPUT result;

	g_SimpleMeleeSkill.execute(pOusters, TargetObjectID, pOustersSkillSlot, param, result, CEffectID );

	if ( bCritical && result.bSuccess )
	{
		GCAddEffect gcAddEffect;
		gcAddEffect.setObjectID( TargetObjectID );
		if ( param.Grade == 0 ) gcAddEffect.setEffectID( Effect::EFFECT_CLASS_BACK_STAB );
		else if ( param.Grade == 1 ) gcAddEffect.setEffectID( Effect::EFFECT_CLASS_BACK_STAB_2 );
		else gcAddEffect.setEffectID( Effect::EFFECT_CLASS_BACK_STAB_3 );

		gcAddEffect.setDuration( 0 );

		Zone* pZone = pOusters->getZone();
		if ( pZone != NULL ) 
		{
			Creature* pCreature = pZone->getCreature( TargetObjectID );
			if ( pCreature != NULL )
			{
				pZone->broadcastPacket( pCreature->getX(), pCreature->getY(), &gcAddEffect );
			}
		}
	}

	__END_CATCH
}

BackStab g_BackStab;
