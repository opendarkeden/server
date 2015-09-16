//////////////////////////////////////////////////////////////////////////////
// Filename    : MultiAmputate.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MULTI_AMPUTATE_HANDLER_H__
#define __SKILL_MULTI_AMPUTATE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MultiAmputate;
//////////////////////////////////////////////////////////////////////////////

class MultiAmputate : public SkillHandler 
{
public:
	MultiAmputate() throw() {}
	~MultiAmputate() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "MultiAmputate"; }

	SkillType_t getSkillType() const throw() { return SKILL_MULTI_AMPUTATE; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MultiAmputate g_MultiAmputate;

#endif // __SKILL_MULTI_AMPUTATE_HANDLER_H__
