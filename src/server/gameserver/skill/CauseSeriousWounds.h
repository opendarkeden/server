//////////////////////////////////////////////////////////////////////////////
// Filename    : CauseSeriousWounds.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CAUSE_SERIOUS_WOUNDS_HANDLER_H__
#define __SKILL_CAUSE_SERIOUS_WOUNDS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class CauseSeriousWounds;
//////////////////////////////////////////////////////////////////////////////

class CauseSeriousWounds : public SkillHandler 
{
public:
	CauseSeriousWounds() throw() {}
	~CauseSeriousWounds() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "CauseSeriousWounds"; }
	SkillType_t getSkillType() const throw() { return SKILL_CAUSE_SERIOUS_WOUNDS; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern CauseSeriousWounds g_CauseSeriousWounds;

#endif // __SKILL_CAUSE_SERIOUS_WOUNDS_HANDLER_H__
