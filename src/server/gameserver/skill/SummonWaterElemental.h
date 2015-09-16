//////////////////////////////////////////////////////////////////////////////
// Filename    : SummonWaterElemental.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SUMMON_WATER_ELEMENTAL_HANDLER_H__
#define __SKILL_SUMMON_WATER_ELEMENTAL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SummonWaterElemental;
//////////////////////////////////////////////////////////////////////////////

class SummonWaterElemental : public SkillHandler 
{
public:
	SummonWaterElemental() throw() {}
	~SummonWaterElemental() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SummonWaterElemental"; }
	SkillType_t getSkillType() const throw() { return SKILL_SUMMON_WATER_ELEMENTAL; }

	void execute(Ousters* pOusters,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SummonWaterElemental g_SummonWaterElemental;

#endif // __SKILL_SUMMON_WATER_ELEMENTAL_HANDLER_H__
