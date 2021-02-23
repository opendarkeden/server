//////////////////////////////////////////////////////////////////////////////
// Filename    : Death.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DEATH_HANDLER_H__
#define __SKILL_DEATH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Death;
//////////////////////////////////////////////////////////////////////////////

class Death : public SkillHandler 
{
public:
	Death() throw() {}
	~Death() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Death"; }
	SkillType_t getSkillType() const throw() { return SKILL_DEATH; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void executeMonster(Zone* pZone, Monster* pMonster, Creature* pEnemy) throw (Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Death g_Death;

#endif // __SKILL_DEATH_HANDLER_H__
