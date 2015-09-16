//////////////////////////////////////////////////////////////////////////////
// Filename    : FlashSliding.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_FLASH_SLIDING_HANDLER_H__
#define __SKILL_FLASH_SLIDING_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class FlashSliding;
//////////////////////////////////////////////////////////////////////////////

class FlashSliding : public SkillHandler 
{
public:
	FlashSliding() throw() {}
	~FlashSliding() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "FlashSliding"; }
	SkillType_t getSkillType() const throw() { return SKILL_FLASH_SLIDING; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern FlashSliding g_FlashSliding;

#endif // __SKILL_FLASH_SLIDING_HANDLER_H__
