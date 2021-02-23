//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidStrike.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ACID_STRIKE_HANDLER_H__
#define __SKILL_ACID_STRIKE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidStrike;
//////////////////////////////////////////////////////////////////////////////

class AcidStrike : public SkillHandler 
{
public:
	AcidStrike() throw() {}
	~AcidStrike() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "AcidStrike"; }
	SkillType_t getSkillType() const throw() { return SKILL_ACID_STRIKE; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern AcidStrike g_AcidStrike;

#endif // __SKILL_ACID_STRIKE_HANDLER_H__
