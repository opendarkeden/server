//////////////////////////////////////////////////////////////////////////////
// Filename    : GreatHeal.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GREAT_HEAL_HANDLER_H__
#define __SKILL_GREAT_HEAL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class GreatHeal;
//////////////////////////////////////////////////////////////////////////////

class GreatHeal: public SkillHandler 
{
public:
	GreatHeal() throw() {}
	~GreatHeal() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "GreatHeal"; }
	SkillType_t getSkillType() const throw() { return SKILL_GREAT_HEAL; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern GreatHeal g_GreatHeal;

#endif // __SKILL_GREAT_HEAL_HANDLER_H__
