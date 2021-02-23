//////////////////////////////////////////////////////////////////////////////
// Filename    : BurningSolLaunch.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BURNING_SOL_LAUNCH_HANDLER_H__
#define __SKILL_BURNING_SOL_LAUNCH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BurningSolLaunch;
//////////////////////////////////////////////////////////////////////////////

class BurningSolLaunch : public SkillHandler 
{
public:
	BurningSolLaunch() throw() {}
	~BurningSolLaunch() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BurningSolLaunch"; }
	SkillType_t getSkillType() const throw() { return SKILL_BURNING_SOL_LAUNCH; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BurningSolLaunch g_BurningSolLaunch;

#endif // __SKILL_BURNING_SOL_LAUNCH_HANDLER_H__
