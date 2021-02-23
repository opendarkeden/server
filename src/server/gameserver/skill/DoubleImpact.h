//////////////////////////////////////////////////////////////////////////////
// Filename    : DoubleImpact.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DOUBLE_IMPACT_HANDLER_H__
#define __SKILL_DOUBLE_IMPACT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DoubleImpact;
//////////////////////////////////////////////////////////////////////////////

class DoubleImpact : public SkillHandler 
{
public:
	DoubleImpact() throw() {}
	~DoubleImpact() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "DoubleImpact"; }
	SkillType_t getSkillType() const throw() { return SKILL_DOUBLE_IMPACT; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern DoubleImpact g_DoubleImpact;

#endif // __SKILL_DOUBLE_IMPACT_HANDLER_H__
