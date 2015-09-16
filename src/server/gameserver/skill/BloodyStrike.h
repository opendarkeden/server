//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyStrike.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_STRIKE_HANDLER_H__
#define __SKILL_BLOODY_STRIKE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodyStrike;
//////////////////////////////////////////////////////////////////////////////

class BloodyStrike : public SkillHandler 
{
public:
	BloodyStrike() throw() {}
	~BloodyStrike() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BloodyStrike"; }
	SkillType_t getSkillType() const throw() { return SKILL_BLOODY_STRIKE; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BloodyStrike g_BloodyStrike;

#endif // __SKILL_BLOODY_STRIKE_HANDLER_H__
