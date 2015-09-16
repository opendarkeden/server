//////////////////////////////////////////////////////////////////////////////
// Filename    : CauseCriticalWounds.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CAUSE_CRITICAL_WOUNDS_HANDLER_H__
#define __SKILL_CAUSE_CRITICAL_WOUNDS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class CauseCriticalWounds;
//////////////////////////////////////////////////////////////////////////////

class CauseCriticalWounds : public SkillHandler 
{
public:
	CauseCriticalWounds() throw() {}
	~CauseCriticalWounds() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "CauseCriticalWounds"; }
	SkillType_t getSkillType() const throw() { return SKILL_CAUSE_CRITICAL_WOUNDS; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern CauseCriticalWounds g_CauseCriticalWounds;

#endif // __SKILL_CAUSE_CRITICAL_WOUNDS_HANDLER_H__
