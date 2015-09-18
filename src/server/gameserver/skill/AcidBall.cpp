//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidBall.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "AcidBall.h"
#include "SimpleMissileSkill.h"
#include "RankBonus.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void AcidBall::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(vampire)" << endl;

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
	param.bMagicHitRoll = true;
	param.bMagicDamage  = true;
	param.bAdd          = false;

	SIMPLE_SKILL_OUTPUT result;

	// Knowledge of Acid 가 있다면 hit bonus 10
	int HitBonus = 0;
	if (pVampire->hasRankBonus(RankBonus::RANK_BONUS_KNOWLEDGE_OF_ACID ) )
	{
		RankBonus* pRankBonus = pVampire->getRankBonus(RankBonus::RANK_BONUS_KNOWLEDGE_OF_ACID);
		Assert(pRankBonus != NULL);

		HitBonus = pRankBonus->getPoint();
	}

	g_SimpleMissileSkill.execute(pVampire, TargetObjectID, pVampireSkillSlot, param, result, CEffectID, HitBonus);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(vampire)" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void AcidBall::execute(Monster* pMonster, Creature* pEnemy)
	throw(Error)
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(monster)" << endl;

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
	param.bMagicHitRoll = true;
	param.bMagicDamage  = true;
	param.bAdd          = false;

	SIMPLE_SKILL_OUTPUT result;

	// 마스터는 여러마리 공격한다.
	if (0)//pMonster->isMaster())
	{
		int x = pMonster->getX();
		int y = pMonster->getY();

		int Splash = 3 + rand()%5; // 3~7 마리
		int range = 2;	// 5x5
		list<Creature*> creatureList;
		getSplashVictims(pMonster->getZone(), x, y, Creature::CREATURE_CLASS_MAX, creatureList, Splash, range);

		list<Creature*>::iterator itr = creatureList.begin();
		int i=0;
		for (; itr != creatureList.end(); itr++)
		{
			Creature* pTargetCreature = (*itr);
			Assert(pTargetCreature != NULL);
		
			if (pMonster!=pTargetCreature)
			{
				//cout << "Master's AcidBall: " << i << endl;
				i++;
				g_SimpleMissileSkill.execute(pMonster, pTargetCreature, param, result);
			}
		}
	}
	else
	{
		g_SimpleMissileSkill.execute(pMonster, pEnemy, param, result);
	}

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(monster)" << endl;

	__END_CATCH
}

AcidBall g_AcidBall;
