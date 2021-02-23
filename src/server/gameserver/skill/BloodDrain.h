//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodDrain.h 
// Written By  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOOD_DRAIN_HANDLER_H__
#define __SKILL_BLOOD_DRAIN_HANDLER_H__

#include "SkillHandler.h"

#define BLOODDRAIN_DURATION		(3*4*3600*10)	//3 ¿œ

//////////////////////////////////////////////////////////////////////
// class BloodDrain;
//////////////////////////////////////////////////////////////////////

class BloodDrain : public SkillHandler 
{
public:
	BloodDrain() throw() {}
	~BloodDrain() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BloodDrain"; }
	SkillType_t getSkillType() const throw() { return SKILL_BLOOD_DRAIN; }

	void execute(Vampire* pCreature, ObjectID_t ObjectID) throw(Error);
	void execute(Monster* pMonster, Creature* pTargetCreature) throw(Error);
	bool executeMonster(Monster* pMonster, Creature* pTargetCreature) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output) {}
};

// global variable declaration
extern BloodDrain g_BloodDrain;

#endif // __SKILL_BLOOD_DRAIN_HANDLER_H__
