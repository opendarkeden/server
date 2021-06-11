//////////////////////////////////////////////////////////////////////////////
// Filename    : HandsOfWisdom.cpp
// Written by  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "HandsOfWisdom.h"
#include "SimpleMeleeSkill.h"
#include "RankBonus.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void HandsOfWisdom::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(vampireobject)" << endl;

	SkillInput input(pVampire);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_MAX;
	param.STRMultiplier = 0;
	param.DEXMultiplier = 0;
	param.INTMultiplier = 0;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = true;
	param.bAdd          = true;

	SIMPLE_SKILL_OUTPUT result;

	// Tiger Nail 이 있다면 데미지 10% 증가
	if ( pVampire->hasRankBonus( RankBonus::RANK_BONUS_TIGER_NAIL ) )
	{
		RankBonus* pRankBonus = pVampire->getRankBonus( RankBonus::RANK_BONUS_TIGER_NAIL );
		Assert( pRankBonus != NULL );

		param.SkillDamage += getPercentValue( param.SkillDamage, pRankBonus->getPoint() );
	}

	// Knowledge of Innate 가 있다면 hit bonus 가 있다.
	int HitBonus = 0;
	if ( pVampire->hasRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_INNATE ) )
	{
		RankBonus* pRankBonus = pVampire->getRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_INNATE );
		Assert( pRankBonus != NULL );

		HitBonus = pRankBonus->getPoint();
	}
	
	g_SimpleMeleeSkill.execute(pVampire, TargetObjectID, pVampireSkillSlot, param, result, CEffectID, HitBonus);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(vampireobject)" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void HandsOfWisdom::execute(Monster* pMonster, Creature* pEnemy)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(monsterobject)" << endl;

	SkillInput input(pMonster);
	SkillOutput output;
	computeOutput(input, output);

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = output.Damage;
	param.Delay         = output.Delay;
	param.ItemClass     = Item::ITEM_CLASS_MAX;
	param.STRMultiplier = 0;
	param.DEXMultiplier = 0;
	param.INTMultiplier = 0;
	param.bMagicHitRoll = false;
	param.bMagicDamage  = true;
	param.bAdd          = true;

	SIMPLE_SKILL_OUTPUT result;

	g_SimpleMeleeSkill.execute(pMonster, pEnemy, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(monsterobject)" << endl;

	__END_CATCH
}

HandsOfWisdom g_HandsOfWisdom;
