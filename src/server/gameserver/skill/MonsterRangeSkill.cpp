//////////////////////////////////////////////////////////////////////////////
// Filename    : MonsterRangeSkill.cpp
// Written by  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "MonsterRangeSkill.h"
#include "SimpleMissileSkill.h"
#include "RankBonus.h"

//////////////////////////////////////////////////////////////////////////////
// 몬스터 오브젝트 핸들러
//////////////////////////////////////////////////////////////////////////////
void MonsterRangeSkill::execute(Monster* pMonster, Creature* pEnemy)
	
{
	__BEGIN_TRY

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " Begin(monster)" << endl;

	SIMPLE_SKILL_INPUT param;
	param.SkillType     = getSkillType();
	param.SkillDamage   = m_Damage;
	param.Delay         = 0;
	param.ItemClass     = Item::ITEM_CLASS_MAX;
	param.STRMultiplier = 0;
	param.DEXMultiplier = 0;
	param.INTMultiplier = 0;
	param.bMagicHitRoll = m_bMagic;
	param.bMagicDamage  = m_bMagic;
	param.bAdd          = m_bAdd;

	SIMPLE_SKILL_OUTPUT result;

	g_SimpleMissileSkill.execute(pMonster, pEnemy, param, result);

	//cout << "TID[" << Thread::self() << "]" << getSkillHandlerName() << " End(monster)" << endl;

	__END_CATCH
}
