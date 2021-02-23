//////////////////////////////////////////////////////////////////////////////
// Filename    : CrossGuard.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CROSS_GUARD_HANDLER_H__
#define __SKILL_CROSS_GUARD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class CrossGuard;
//////////////////////////////////////////////////////////////////////////////

class CrossGuard : public SkillHandler 
{
public:
	CrossGuard() throw() {}
	~CrossGuard() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "CrossGuard"; }
	SkillType_t getSkillType() const throw() { return SKILL_CROSS_GUARD; }

	void execute(Ousters* pOusters,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern CrossGuard g_CrossGuard;

#endif // __SKILL_CROSS_GUARD_HANDLER_H__
