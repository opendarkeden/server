//////////////////////////////////////////////////////////////////////////////
// Filename    : AttackMelee.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ATTACK_MELEE_HANDLER_H__
#define __SKILL_ATTACK_MELEE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AttackMelee;
//////////////////////////////////////////////////////////////////////////////

class AttackMelee : public SkillHandler 
{
public:
	AttackMelee() throw() {}
	~AttackMelee() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "AttackMelee"; }

	SkillType_t getSkillType() const throw() { return SKILL_ATTACK_MELEE; }

	void execute(Slayer* pPlayer, ObjectID_t ObjectID) throw(Error);
	void execute(Vampire* pCreature, ObjectID_t ObjectID) throw(Error);
	void execute(Monster* pCreature, Creature* pEnemy) throw(Error);
	void execute(Ousters* pCreature, ObjectID_t ObjectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output) {}
};

// global variable declaration
extern AttackMelee g_AttackMelee;

#endif // __SKILL_ATTACK_MELEE_HANDLER_H__
