//////////////////////////////////////////////////////////////////////////////
// Filename    : RainbowSlasher.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_RAINBOW_SLASHER_HANDLER_H__
#define __SKILL_RAINBOW_SLASHER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class RainbowSlasher;
//////////////////////////////////////////////////////////////////////////////

class RainbowSlasher : public SkillHandler 
{
public:
	RainbowSlasher() throw() {}
	~RainbowSlasher() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "RainbowSlasher"; }
	SkillType_t getSkillType() const throw() { return SKILL_RAINBOW_SLASHER; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern RainbowSlasher g_RainbowSlasher;

#endif // __SKILL_RAINBOW_SLASHER_HANDLER_H__
