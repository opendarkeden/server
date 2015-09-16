//////////////////////////////////////////////////////////////////////////////
// Filename    : Resurrect.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_RESURRECT_HANDLER_H__
#define __SKILL_RESURRECT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Resurrect;
//////////////////////////////////////////////////////////////////////////////

class Resurrect : public SkillHandler 
{
public:
	Resurrect() throw() {}
	~Resurrect() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Resurrect"; }

	SkillType_t getSkillType() const throw() { return SKILL_RESURRECT; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Resurrect g_Resurrect;

#endif // __SKILL_RESURRECT_HANDLER_H__
