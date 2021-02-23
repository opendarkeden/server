//////////////////////////////////////////////////////////////////////////////
// Filename    : SharpRound.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SharpRound.h"
#include "SimpleMeleeSkill.h"
#include "RankBonus.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void SharpRound::execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	SkillInput input(pOusters, pOustersSkillSlot);
	SIMPLE_SKILL_INPUT param;

	if ( input.SkillLevel < 15 ) param.Grade = 0;
	else if ( input.SkillLevel < 30 ) param.Grade = 1;
	else param.Grade = 2;

	Zone* pZone = pOusters->getZone();
	Assert( pZone != NULL );

	Creature* pTargetCreature = pZone->getCreature( TargetObjectID );
	if ( pTargetCreature == NULL )
	{
		executeSkillFailException( pOusters, getSkillType(), param.Grade );
		return;
	}

	SkillOutput output;
	computeOutput(input, output);

	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage + ( computeDamage( pOusters, pTargetCreature ) / 2 );
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_OUSTERS_CHAKRAM;
	param.STRMultiplier = 0;
	param.DEXMultiplier = 0;
	param.INTMultiplier = 0;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;

	SIMPLE_SKILL_OUTPUT result;

	g_SimpleMeleeSkill.execute(pOusters, TargetObjectID, pOustersSkillSlot, param, result, CEffectID );

	__END_CATCH
}


SharpRound g_SharpRound;
