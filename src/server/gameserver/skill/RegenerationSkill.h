//////////////////////////////////////////////////////////////////////////////
// Filename    : Regeneration.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_REGENERATION_SKILL_HANDLER_H__
#define __SKILL_REGENERATION_SKILL_HANDLER_H__

#include "SkillHandler.h"

#define REGENERATION_DELAY      30  // 3초 마다 회복..

//////////////////////////////////////////////////////////////////////////////
// class Regeneration;
//////////////////////////////////////////////////////////////////////////////

class RegenerationSkill: public SkillHandler 
{
public:
	RegenerationSkill() throw() {}
	~RegenerationSkill() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Regeneration"; }
	SkillType_t getSkillType() const throw() { return SKILL_REGENERATION; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern RegenerationSkill g_RegenerationSkill;

#endif // __SKILL_REGENERATION_SKILL_HANDLER_H__
