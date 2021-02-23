//////////////////////////////////////////////////////////////////////////////
// Filename    : DetectInvisibility.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DETECT_INVISIBILITY_HANDLER_H__
#define __SKILL_DETECT_INVISIBILITY_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DetectInvisibility
//////////////////////////////////////////////////////////////////////////////

class DetectInvisibility: public SkillHandler 
{
public:
	DetectInvisibility() throw() {}
	~DetectInvisibility() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "DetectInvisibility"; }

	SkillType_t getSkillType() const throw() { return SKILL_DETECT_INVISIBILITY; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern DetectInvisibility g_DetectInvisibility;

#endif // __SKILL_DETECT_INVISIBILITY_HANDLER_H__
