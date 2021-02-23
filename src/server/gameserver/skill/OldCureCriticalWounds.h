//////////////////////////////////////////////////////////////////////////////
// Filename    : CureCriticalWounds.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CURE_CRITICAL_WOUNDS_HANDLER_H__
#define __SKILL_CURE_CRITICAL_WOUNDS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class CureCriticalWounds;
//////////////////////////////////////////////////////////////////////////////

class CureCriticalWounds: public SkillHandler 
{
public:
	CureCriticalWounds() throw() {}
	~CureCriticalWounds() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "CureCriticalWounds"; }
	SkillType_t getSkillType() const throw() { return SKILL_CURE_CRITICAL_WOUNDS; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern CureCriticalWounds g_CureCriticalWounds;

#endif // __SKILL_CURE_CRITICAL_WOUNDS_HANDLER_H__
