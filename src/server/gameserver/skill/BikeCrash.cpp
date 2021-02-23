//////////////////////////////////////////////////////////////////////////////
// Filename    : BikeCrash.cpp
// Written by  : elca@ewestsoft.com
// Description :
//////////////////////////////////////////////////////////////////////////////

#include "BikeCrash.h"
#include "SimpleMeleeSkill.h"
#include "SimpleTileMissileSkill.h"
#include <list>

void BikeCrash::execute(Slayer* pSlayer, ObjectID_t targetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error)
{
	__BEGIN_TRY

	Zone* pZone = pSlayer->getZone();
	Assert(pZone != NULL);
	
	Creature* pTargetCreature = pZone->getCreature(targetObjectID);
	if ( pTargetCreature == NULL )
	{
		executeSkillFailException(pSlayer, getSkillType());
		return;
	}

	ZoneCoord_t X = pTargetCreature->getX();
	ZoneCoord_t Y = pTargetCreature->getY();

	SkillInfo*        pSkillInfo = g_pSkillInfoManager->getSkillInfo(getSkillType());
	bool bRangeCheck = verifyDistance(pSlayer, pTargetCreature, pSkillInfo->getRange());

	if ( !bRangeCheck || !pZone->moveFastPC( pSlayer, pSlayer->getX(), pSlayer->getY(), X, Y, getSkillType()) )
	{
		executeSkillFailNormal(pSlayer, getSkillType(), pTargetCreature);
		return;
	}

	X = pSlayer->getX();
	Y = pSlayer->getY();

	SkillInput input(pSlayer, pSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_SWORD;
	param.STRMultiplier = 8;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 1;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = false;
	param.bAdd          = true;
	param.bExpForTotalDamage = false;

	for ( int i=-2; i<=2; ++i )
	for ( int j=-2; j<=2; ++j )
	{
		param.addMask(i, j, 100);
	}

	SIMPLE_SKILL_OUTPUT result;

	g_SimpleTileMissileSkill.execute(pSlayer, X, Y, pSkillSlot, param, result);

	__END_CATCH
}

BikeCrash g_BikeCrash;

