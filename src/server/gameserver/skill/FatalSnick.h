//////////////////////////////////////////////////////////////////////////////
// Filename    : FatalSnick.h 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_FATAL_SNICK_HANDLER_H__
#define __SKILL_FATAL_SNICK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class FatalSnick;
//////////////////////////////////////////////////////////////////////////////

class FatalSnick: public SkillHandler 
{
public:
	FatalSnick() throw() {}
	~FatalSnick() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "FatalSnick"; }

	SkillType_t getSkillType() const throw() { return SKILL_FATAL_SNICK; }

	void execute(Ousters* pOusters, ObjectID_t targetObject, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern FatalSnick g_FatalSnick;

#endif // __SKILL_FATAL_SNICK_HANDLER_H__
