//////////////////////////////////////////////////////////////////////////////
// Filename    : PoisonStrike.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_POISON_STRIKE_HANDLER_H__
#define __SKILL_POISON_STRIKE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class PoisonStrike;
//////////////////////////////////////////////////////////////////////////////

class PoisonStrike : public SkillHandler 
{
public:
	PoisonStrike() throw() {}
	~PoisonStrike() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "PoisonStrike"; }
	SkillType_t getSkillType() const throw() { return SKILL_POISON_STRIKE; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern PoisonStrike g_PoisonStrike;

#endif // __SKILL_POISON_STRIKE_HANDLER_H__
