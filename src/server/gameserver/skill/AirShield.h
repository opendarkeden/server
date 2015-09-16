//////////////////////////////////////////////////////////////////////////////
// Filename    : AirShield.h 
// Written By  : Sequoia
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_AIR_SHIELD_HANDLER_H__
#define __SKILL_AIR_SHIELD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AirShield;
//////////////////////////////////////////////////////////////////////////////

class AirShield : public SkillHandler 
{
public:
	AirShield() throw() {}
	~AirShield() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "AirShield"; }
	SkillType_t getSkillType() const throw() { return SKILL_AIR_SHIELD; }

	void execute(Slayer* pSlayer,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern AirShield g_AirShield;

#endif // __SKILL_AIR_SHIELD_HANDLER_H__
