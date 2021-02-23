//////////////////////////////////////////////////////////////////////////////
// Filename    : BurningSolLaunch.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "BurningSolLaunch.h"
#include "EffectBurningSolCharging.h"
#include "SimpleMeleeSkill.h"
#include "SimpleTileMissileSkill.h"

void BurningSolLaunch::execute(Slayer * pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin" << endl;

	if ( !pSlayer->isFlag( Effect::EFFECT_CLASS_BURNING_SOL_CHARGE_1 ) )
	{
		executeSkillFailException( pSlayer, getSkillType() );
		return;
	}

	EffectBurningSolCharging* pEffect = dynamic_cast<EffectBurningSolCharging*>(pSlayer->findEffect(Effect::EFFECT_CLASS_BURNING_SOL_CHARGE_1));
	if ( pEffect == NULL )
	{
		executeSkillFailException( pSlayer, getSkillType() );
		return;
	}

	cout << "Launching burning sol..." << (int)pEffect->getLevel() << endl;

	pEffect->setDeadline(0);

	SkillInput input(pSlayer, pSkillSlot);
	input.Range = pEffect->getLevel();
	SkillOutput output;
	computeOutput(input, output);

	cout << "Damage bonus : " << output.Damage << endl;

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_BLADE;
	param.STRMultiplier = 8;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 1;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;
	param.bExpForTotalDamage = true;
	param.Level = pEffect->getLevel();

	SIMPLE_SKILL_OUTPUT result;

	int offset = 2;
//	if ( pEffect->getLevel() >= 2 ) offset = 2;

	// 목표위치+4방향
	for ( int i=-offset; i<=offset; ++i )
	for ( int j=-offset; j<=offset; ++j )
		param.addMask( i, j, 100 );

	param.Grade = pEffect->getLevel();
	
/*	param.addMask( 0,  0, 100);
	param.addMask(-1, -1, 100);
	param.addMask( 0, -1, 100);
	param.addMask( 1, -1, 100);
	param.addMask(-1,  0, 100);
	param.addMask( 1,  0, 100);
	param.addMask(-1,  1, 100);
	param.addMask( 0,  1, 100);
	param.addMask( 1,  1, 100);*/

	g_SimpleTileMissileSkill.execute(pSlayer, X, Y, pSkillSlot, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void BurningSolLaunch::execute(Slayer * pSlayer, ObjectID_t TargetObjectID, SkillSlot * pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	Zone* pZone = pSlayer->getZone();
	Assert(pZone!=NULL);

	Creature* pTargetCreature = pZone->getCreature( TargetObjectID );

	if (pTargetCreature!=NULL)
	{
		execute(pSlayer, pTargetCreature->getX(), pTargetCreature->getY(), pSkillSlot, CEffectID);
	}
	else
	{
		executeSkillFailException(pSlayer, getSkillType());
	}


	__END_CATCH
}

BurningSolLaunch g_BurningSolLaunch;
