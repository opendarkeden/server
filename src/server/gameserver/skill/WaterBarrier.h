//////////////////////////////////////////////////////////////////////////////
// Filename    : WaterBarrier.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_WATER_BARRIER_HANDLER_H__
#define __SKILL_WATER_BARRIER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class WaterBarrier;
//////////////////////////////////////////////////////////////////////////////

class WaterBarrier : public SkillHandler 
{
public:
	WaterBarrier() throw() {}
	~WaterBarrier() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "WaterBarrier"; }
	SkillType_t getSkillType() const throw() { return SKILL_WATER_BARRIER; }

	void execute(Ousters* pOusters,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern WaterBarrier g_WaterBarrier;

#endif // __SKILL_WATER_BARRIER_HANDLER_H__
