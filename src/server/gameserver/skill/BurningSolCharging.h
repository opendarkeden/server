//////////////////////////////////////////////////////////////////////////////
// Filename    : BurningSolCharging.h 
// Written By  : Sequoia
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BURNING_SOL_CHARGING_HANDLER_H__
#define __SKILL_BURNING_SOL_CHARGING_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BurningSolCharging;
//////////////////////////////////////////////////////////////////////////////

class BurningSolCharging : public SkillHandler 
{
public:
	BurningSolCharging() throw() {}
	~BurningSolCharging() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BurningSolCharging"; }
	SkillType_t getSkillType() const throw() { return SKILL_BURNING_SOL_CHARGING; }

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
//	void execute(Slayer* pSlayer,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BurningSolCharging g_BurningSolCharging;

#endif // __SKILL_BURNING_SOL_CHARGING_HANDLER_H__
