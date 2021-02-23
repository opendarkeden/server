//////////////////////////////////////////////////////////////////////////////
// Filename    : Aberration.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ABERRATION_HANDLER_H__
#define __SKILL_ABERRATION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Aberration;
//////////////////////////////////////////////////////////////////////////////

class Aberration : public SkillHandler 
{
public:
	Aberration() throw() {}
	~Aberration() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Aberration"; }
	SkillType_t getSkillType() const throw() { return SKILL_ABERRATION; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Aberration g_Aberration;

#endif // __SKILL_ABERRATION_HANDLER_H__
