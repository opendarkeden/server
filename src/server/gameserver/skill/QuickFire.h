//////////////////////////////////////////////////////////////////////////////
// Filename    : QuickFire.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_QUICK_FIRE_HANDLER_H__
#define __SKILL_QUICK_FIRE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class QuickFire;
//////////////////////////////////////////////////////////////////////////////

class QuickFire : public SkillHandler 
{
public:
	QuickFire() throw() {}
	~QuickFire() throw() {}

public:
    string getSkillHandlerName() const throw() { return "QuickFire"; }
	SkillType_t getSkillType() const throw() { return SKILL_QUICK_FIRE; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern QuickFire g_QuickFire;

#endif // __SKILL_QUICK_FIRE_HANDLER_H__
