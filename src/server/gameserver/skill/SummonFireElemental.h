//////////////////////////////////////////////////////////////////////////////
// Filename    : SummonFireElemental.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SUMMON_FIRE_ELEMENTAL_HANDLER_H__
#define __SKILL_SUMMON_FIRE_ELEMENTAL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SummonFireElemental;
//////////////////////////////////////////////////////////////////////////////

class SummonFireElemental : public SkillHandler 
{
public:
	SummonFireElemental() throw() {}
	~SummonFireElemental() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SummonFireElemental"; }
	SkillType_t getSkillType() const throw() { return SKILL_SUMMON_FIRE_ELEMENTAL; }

	void execute(Ousters* pOusters,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SummonFireElemental g_SummonFireElemental;

#endif // __SKILL_SUMMON_FIRE_ELEMENTAL_HANDLER_H__
