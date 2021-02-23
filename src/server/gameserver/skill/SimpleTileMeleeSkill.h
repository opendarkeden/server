//////////////////////////////////////////////////////////////////////////////
// Filename    : SimpleTileMeleeSkill.h
// Written by  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SIMPLETILEMELEESKILL__
#define __SIMPLETILEMELEESKILL__

#include "SimpleSkill.h"

class SimpleTileMeleeSkill
{
public:
	void execute(Slayer* pSlayer, int X, int Y, SkillSlot* pSkillSlot,
		const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
		CEffectID_t CEffectID=0, bool bForceKnockback=false) throw (Error);
	void execute(Vampire* pVampire, int X, int Y, VampireSkillSlot* pVampireSkillSlot, 
		const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
		CEffectID_t CEffectID=0, bool bForceKnockback=false) throw (Error);
	void execute(Ousters* pOusters, int X, int Y, OustersSkillSlot* pOustersSkillSlot,
		const SIMPLE_SKILL_INPUT& param, SIMPLE_SKILL_OUTPUT& result,
		CEffectID_t CEffectID=0, bool bForceKnockback=false) throw (Error);
	void execute(Monster* pMonster, int X, int Y,
		const SIMPLE_SKILL_INPUT& param,  SIMPLE_SKILL_OUTPUT& result,
		CEffectID_t CEffectID=0, bool bForceKnockback=false) throw (Error);
};

extern SimpleTileMeleeSkill g_SimpleTileMeleeSkill;

#endif
