//////////////////////////////////////////////////////////////////////////////
// Filename    : DoubleShot.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DOUBLE_SHOT_HANDLER_H__
#define __SKILL_DOUBLE_SHOT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DoubleShot;
//////////////////////////////////////////////////////////////////////////////

class DoubleShot : public SkillHandler 
{
public:
	DoubleShot() throw() {}
	~DoubleShot() throw() {}

public:
    string getSkillHandlerName() const throw() { return "DoubleShot"; }
	SkillType_t getSkillType() const throw() { return SKILL_DOUBLE_SHOT; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern DoubleShot g_DoubleShot;

#endif // __SKILL_DOUBLE_SHOT_HANDLER_H__
