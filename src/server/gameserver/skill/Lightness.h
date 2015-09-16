//////////////////////////////////////////////////////////////////////////////
// Filename    : Lightness.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_LIGHTNESS_HANDLER_H__
#define __SKILL_LIGHTNESS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Lightness;
//////////////////////////////////////////////////////////////////////////////

class Lightness: public SkillHandler 
{
public:
	Lightness() throw() {}
	~Lightness() throw() {}

public:
    string getSkillHandlerName() const throw() { return "Lightness"; }
	SkillType_t getSkillType() const throw() { return SKILL_LIGHTNESS; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Lightness g_Lightness;

#endif // __SKILL_LIGHTNESS_HANDLER_H__
