//////////////////////////////////////////////////////////////////////////////
// Filename    : Tendril.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TENDRIL_HANDLER_H__
#define __SKILL_TENDRIL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Tendril;
//////////////////////////////////////////////////////////////////////////////

class Tendril : public SkillHandler 
{
public:
	Tendril() throw() {}
	~Tendril() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Tendril"; }
	SkillType_t getSkillType() const throw() { return SKILL_TENDRIL; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID, OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Tendril g_Tendril;

#endif // __SKILL_TENDRIL_HANDLER_H__
