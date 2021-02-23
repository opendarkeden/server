//////////////////////////////////////////////////////////////////////////////
// Filename    : GroundBless.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GROUND_BLESS_HANDLER_H__
#define __SKILL_GROUND_BLESS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class GroundBless;
//////////////////////////////////////////////////////////////////////////////

class GroundBless : public SkillHandler 
{
public:
	GroundBless() throw() {}
	~GroundBless() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "GroundBless"; }
	SkillType_t getSkillType() const throw() { return SKILL_GROUND_BLESS; }

	void execute(Ousters* pOusters,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern GroundBless g_GroundBless;

#endif // __SKILL_GROUND_BLESS_HANDLER_H__
