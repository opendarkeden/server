//////////////////////////////////////////////////////////////////////////////
// Filename    : SimpleLinearMeleeSkill.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SIMPLELINEARMELEESKILL__
#define __SIMPLELINEARMELEESKILL__

#include "SimpleSkill.h"

class SimpleLinearMeleeSkill
{
public:
	void execute(Slayer* pSlayer, int X, int Y, SkillSlot* pSkillSlot,
		const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
		CEffectID_t CEffectID=0) throw(Error);
	/*
	void execute(Vampire* pVampire, int X, int Y, VampireSkillSlot* pVampireSkillSlot, 
		const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
		CEffectID_t CEffectID=0) throw(Error);
	void execute(Monster* pMonster, int X, int Y,
		const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
		CEffectID_t CEffectID=0) throw(Error);
	*/
};

extern SimpleLinearMeleeSkill g_SimpleLinearMeleeSkill;

#endif
