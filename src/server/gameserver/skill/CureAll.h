//////////////////////////////////////////////////////////////////////////////
// Filename    : CureAll.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CURE_ALL_HANDLER_H__
#define __SKILL_CURE_ALL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class CureAll;
//////////////////////////////////////////////////////////////////////////////

class CureAll: public SkillHandler 
{
public:
	CureAll() throw() {}
	~CureAll() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "CureAll"; }
	SkillType_t getSkillType() const throw() { return SKILL_CURE_ALL; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern CureAll g_CureAll;

#endif // __SKILL_CURE_ALL_HANDLER_H__
