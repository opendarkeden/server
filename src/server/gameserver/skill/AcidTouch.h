//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidTouch.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ACID_TOUCH_HANDLER_H__
#define __SKILL_ACID_TOUCH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidTouch;
//////////////////////////////////////////////////////////////////////////////

class AcidTouch: public SkillHandler 
{
public:
	AcidTouch() throw() {}
	~AcidTouch() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "AcidTouch"; }

	SkillType_t getSkillType() const throw() { return SKILL_ACID_TOUCH; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern AcidTouch g_AcidTouch;

#endif // __SKILL_ACID_TOUCH_HANDLER_H__
