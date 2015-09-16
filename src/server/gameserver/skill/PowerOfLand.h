//////////////////////////////////////////////////////////////////////////////
// Filename    : PowerOfLand.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_POWER_OF_LAND_HANDLER_H__
#define __SKILL_POWER_OF_LAND_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class PowerOfLand;
//////////////////////////////////////////////////////////////////////////////

class PowerOfLand : public SkillHandler 
{
public:
	PowerOfLand() throw() {}
	~PowerOfLand() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "PowerOfLand"; }
	SkillType_t getSkillType() const throw() { return SKILL_POWER_OF_LAND; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern PowerOfLand g_PowerOfLand;

#endif // __SKILL_POWER_OF_LAND_HANDLER_H__
