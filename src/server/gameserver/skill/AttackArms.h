//////////////////////////////////////////////////////////////////////////////
// Filename    : AttackArms.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ATTACK_ARMS_HANDLER_H__
#define __SKILL_ATTACK_ARMS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AttackArms;
//////////////////////////////////////////////////////////////////////////////

class AttackArms : public SkillHandler 
{
public:
	AttackArms() throw() {}
	~AttackArms() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "AttackArms"; }
	SkillType_t getSkillType() const throw() { return SKILL_ATTACK_ARMS; }

	void execute(Slayer* pPlayer, ObjectID_t ObjectID) throw(Error);
	void execute(Monster* pPlayer, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output) {}
};

// global variable declaration
extern AttackArms g_AttackArms;

#endif // __SKILL_ATTACK_ARMS_HANDLER_H__
