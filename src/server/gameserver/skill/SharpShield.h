//////////////////////////////////////////////////////////////////////////////
// Filename    : SharpShield.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SHARP_SHIELD_HANDLER_H__
#define __SKILL_SHARP_SHIELD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SharpShield;
//////////////////////////////////////////////////////////////////////////////

class SharpShield : public SkillHandler 
{
public:
	SharpShield() throw() {}
	~SharpShield() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SharpShield"; }
	SkillType_t getSkillType() const throw() { return SKILL_SHARP_SHIELD; }

	void execute(Slayer* pSlayer,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SharpShield g_SharpShield;

#endif // __SKILL_SHARP_SHIELD_HANDLER_H__
