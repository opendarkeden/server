//////////////////////////////////////////////////////////////////////////////
// Filename    : DivineGuidance.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DIVINE_GUIDANCE_HANDLER_H__
#define __SKILL_DIVINE_GUIDANCE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DivineGuidance;
//////////////////////////////////////////////////////////////////////////////

class DivineGuidance: public SkillHandler 
{
public:
	DivineGuidance() throw() {}
	~DivineGuidance() throw() {}

public:
    string getSkillHandlerName() const throw() { return "DivineGuidance"; }
	SkillType_t getSkillType() const throw() { return SKILL_DIVINE_GUIDANCE; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern DivineGuidance g_DivineGuidance;

#endif // __SKILL_DIVINE_GUIDANCE_HANDLER_H__
