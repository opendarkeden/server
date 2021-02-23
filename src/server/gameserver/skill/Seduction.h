//////////////////////////////////////////////////////////////////////////////
// Filename    : Seduction.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SEDUCTION_HANDLER_H__
#define __SKILL_SEDUCTION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Seduction;
//////////////////////////////////////////////////////////////////////////////

class Seduction : public SkillHandler 
{
public:
	Seduction() throw() {}
	~Seduction() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Seduction"; }
	SkillType_t getSkillType() const throw() { return SKILL_SEDUCTION; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void executeMonster(Zone* pZone, Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Seduction g_Seduction;

#endif // __SKILL_SEDUCTION_HANDLER_H__
