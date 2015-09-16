//////////////////////////////////////////////////////////////////////////////
// Filename    : DarkBluePoison.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DARKBLUE_POISON_HANDLER_H__
#define __SKILL_DARKBLUE_POISON_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DarkBluePoison;
//////////////////////////////////////////////////////////////////////////////

class DarkBluePoison : public SkillHandler 
{
public:
	DarkBluePoison() throw() {}
	~DarkBluePoison() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "DarkBluePoison"; }
	SkillType_t getSkillType() const throw() { return SKILL_DARKBLUE_POISON; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern DarkBluePoison g_DarkBluePoison;

#endif // __SKILL_DARKBLUE_POISON_HANDLER_H__
