//////////////////////////////////////////////////////////////////////////////
// Filename    : Evade.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_EVADE_HANDLER_H__
#define __SKILL_EVADE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Evade;
//////////////////////////////////////////////////////////////////////////////

class Evade : public SkillHandler 
{
public:
	Evade() throw() {}
	~Evade() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Evade"; }
	SkillType_t getSkillType() const throw() { return SKILL_EVADE; }

	void execute(Ousters* pOusters,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Evade g_Evade;

#endif // __SKILL_EVADE_HANDLER_H__
