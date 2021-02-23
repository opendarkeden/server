//////////////////////////////////////////////////////////////////////////////
// Filename    : CureLightWounds.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CURE_LIGHT_WOUNDS_HANDLER_H__
#define __SKILL_CURE_LIGHT_WOUNDS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class CureLightWounds;
//////////////////////////////////////////////////////////////////////////////

class CureLightWounds: public SkillHandler 
{
public:
	CureLightWounds() throw() {}
	~CureLightWounds() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "CureLightWounds"; }
	SkillType_t getSkillType() const throw() { return SKILL_CURE_LIGHT_WOUNDS; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern CureLightWounds g_CureLightWounds;

#endif // __SKILL_CURE_LIGHT_WOUNDS_HANDLER_H__
