//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodySpear.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "BloodySpear.h"
#include "SimpleMissileSkill.h"
#include "RankBonus.h"

//////////////////////////////////////////////////////////////////////////////
// 뱀파이어 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void BloodySpear::execute(Vampire* pVampire, ObjectID_t TargetObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID)
	
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

	// Knowledge of Blood 가 있다면 hit bonus 10
	int HitBonus = 0;
	if ( pVampire->hasRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_BLOOD ) )
	{
		RankBonus* pRankBonus = pVampire->getRankBonus( RankBonus::RANK_BONUS_KNOWLEDGE_OF_BLOOD );
		Assert( pRankBonus != NULL );

		HitBonus = pRankBonus->getPoint();
	}

	g_SimpleMissileSkill.execute(pVampire, TargetObjectID, pVampireSkillSlot, param, result, CEffectID, HitBonus);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(vampire)" << endl;

	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
// 몬스터 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void BloodySpear::execute(Monster* pMonster, Creature* pEnemy)
	
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

	if (pMonster->isMaster())
	{
		if (pEnemy==NULL) return;

		int X = pEnemy->getX();
		int Y = pEnemy->getY();
		int oX, oY;

		Zone* pZone = pEnemy->getZone();
		Assert(pZone!=NULL);

		VSRect rect(0, 0, pZone->getWidth()-1, pZone->getHeight()-1);

		for(oX = -3; oX <= 3; oX++)
		for(oY = -3; oY <= 3; oY++)
		{
			int tileX = X+oX;
			int tileY = Y+oY;
			if (!rect.ptInRect(tileX, tileY)) continue;

			checkMine( pZone, tileX, tileY );

			Tile& tile = pZone->getTile(tileX, tileY);

			Creature* pTargetCreature = NULL;
			if (tile.hasCreature(Creature::MOVE_MODE_WALKING))
				pTargetCreature = tile.getCreature(Creature::MOVE_MODE_WALKING);

			if (pTargetCreature != NULL 
				// NPC도 아니어야 한다.
				&& !pTargetCreature->isNPC()
				// 공격 대상이 맞는지 확인
				&& pMonster->isEnemyToAttack( pTargetCreature ))
			{
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

BloodySpear g_BloodySpear;
