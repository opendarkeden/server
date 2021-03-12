//////////////////////////////////////////////////////////////////////////////
// Filename    : SummonMonsters.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SUMMON_MONSTERS_HANDLER_H__
#define __SKILL_SUMMON_MONSTERS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SummonMonsters;
//////////////////////////////////////////////////////////////////////////////

class SummonMonsters: public SkillHandler 
{
public:
	SummonMonsters() throw();
	~SummonMonsters() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SummonMonsters"; }
	SkillType_t getSkillType() const throw() { return SKILL_SUMMON_MONSTERS; }

	//void execute(Slayer* pSlayer, SlayerSkillSlot* pSlayerSkillSlot, CEffectID_t CEffectID) ;
	//void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) ;
	void execute(Monster* pMonster) ;

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SummonMonsters g_SummonMonsters;

#endif // __SKILL_HIDE_HANDLER_H__
