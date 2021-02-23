//////////////////////////////////////////////////////////////////////////////
// Filename    : SpiralSlay.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SPIRAL_SLAY_HANDLER_H__
#define __SKILL_SPIRAL_SLAY_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SpiralSlay;
//////////////////////////////////////////////////////////////////////////////

class SpiralSlay : public SkillHandler 
{
public:
	SpiralSlay() throw() {}
	~SpiralSlay() throw() {}

public:
    string getSkillHandlerName() const throw() { return "SpiralSlay"; }
	SkillType_t getSkillType() const throw() { return SKILL_SPIRAL_SLAY; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SpiralSlay g_SpiralSlay;

#endif // __SKILL_SPIRAL_SLAY_HANDLER_H__
