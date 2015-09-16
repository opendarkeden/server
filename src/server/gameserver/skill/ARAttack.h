//////////////////////////////////////////////////////////////////////////////
// Filename    : ARAttack.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_AR_ATTACK_HANDLER_H__
#define __SKILL_AR_ATTACK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ARAttack;
//////////////////////////////////////////////////////////////////////////////

class ARAttack : public SkillHandler 
{
public:
	ARAttack() throw() {}
	~ARAttack() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "ARAttack"; }
	SkillType_t getSkillType() const throw() { return SKILL_AR_ATTACK; }

	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ARAttack g_ARAttack;

#endif // __SKILL_AR_ATTACK_HANDLER_H__
