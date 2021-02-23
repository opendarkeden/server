//////////////////////////////////////////////////////////////////////////////
// Filename    : UltimateBlow.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ULTIMATE_BLOW_HANDLER_H__
#define __SKILL_ULTIMATE_BLOW_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class UltimateBlow;
//////////////////////////////////////////////////////////////////////////////

class UltimateBlow : public SkillHandler 
{
public:
	UltimateBlow() throw() {}
	~UltimateBlow() throw() {}

public:
    string getSkillHandlerName() const throw() { return "UltimateBlow"; }
	SkillType_t getSkillType() const throw() { return SKILL_ULTIMATE_BLOW; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern UltimateBlow g_UltimateBlow;

#endif // __SKILL_ULTIMATE_BLOW_HANDLER_H__
