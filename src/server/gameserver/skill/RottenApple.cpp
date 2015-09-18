//////////////////////////////////////////////////////////////////////////////
// Filename	: RottenApple.cpp
// Written by	: 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "RottenApple.h"
#include "SimpleTileMissileSkill.h"

//////////////////////////////////////////////////////////////////////////////
// 슬레이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void RottenApple::execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(slayerobject)" << endl;

	Zone* pZone = pSlayer->getZone();
	Assert(pZone != NULL);

	Creature* pTargetCreature = pZone->getCreature(TargetObjectID);
	//Assert(pTargetCreature != NULL);

	// NoSuch제거. by sigi. 2002.5.2
	if (pTargetCreature == NULL || pTargetCreature->isFlag(Effect::EFFECT_CLASS_IMMUNE_TO_ROTTEN_APPLE)) {
		executeSkillFailException(pSlayer, getSkillType());
		return;
	}

	ZoneCoord_t X = pTargetCreature->getX();
	ZoneCoord_t Y = pTargetCreature->getY();

	SkillInput input(pSlayer, pSkillSlot);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_MAX;
	param.STRMultiplier = 1;
	param.DEXMultiplier = 1;
	param.INTMultiplier = 8;
	param.bMagicHitRoll = true;
	param.bMagicDamage  = false;
	param.bAdd          = false;
	param.bExpForTotalDamage = false;

	SIMPLE_SKILL_OUTPUT result;

	for (int i =- 2; i <= 2; ++i) {
        for (int j =- 2; j <= 2; ++j)
            param.addMask(i, j, 100);
    }

    if (pTargetCreature->isPC())
        param.SkillDamage = param.SkillDamage / 3;

	g_SimpleTileMissileSkill.execute(pSlayer, X, Y, pSkillSlot, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(slayerobject)" << endl;

	__END_CATCH
}

RottenApple g_RottenApple;
