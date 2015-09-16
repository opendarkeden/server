//////////////////////////////////////////////////////////////////////////////
// Filename    : Rediance.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_REDIANCE_HANDLER_H__
#define __SKILL_REDIANCE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Rediance;
//////////////////////////////////////////////////////////////////////////////

class Rediance : public SkillHandler 
{
public:
	Rediance() throw() {}
	~Rediance() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Rediance"; }
	SkillType_t getSkillType() const throw() { return SKILL_REDIANCE; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Rediance g_Rediance;

#endif // __SKILL_REDIANCE_HANDLER_H__
