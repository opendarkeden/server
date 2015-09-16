//////////////////////////////////////////////////////////////////////////////
// Filename    : ChargingPower.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CHARGING_POWER_HANDLER_H__
#define __SKILL_CHARGING_POWER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ChargingPower;
//////////////////////////////////////////////////////////////////////////////

class ChargingPower : public SkillHandler 
{
public:
	ChargingPower() throw() {}
	~ChargingPower() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "ChargingPower"; }
	SkillType_t getSkillType() const throw() { return SKILL_CHARGING_POWER; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ChargingPower g_ChargingPower;

#endif // __SKILL_CHARGING_POWER_HANDLER_H__
