//////////////////////////////////////////////////////////////////////////////
// Filename    : CauseLightWounds.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CAUSE_LIGHT_WOUNDS_HANDLER_H__
#define __SKILL_CAUSE_LIGHT_WOUNDS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class CauseLightWounds;
//////////////////////////////////////////////////////////////////////////////

class CauseLightWounds : public SkillHandler 
{
public:
	CauseLightWounds() throw() {}
	~CauseLightWounds() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "CauseLightWounds"; }
	SkillType_t getSkillType() const throw() { return SKILL_CAUSE_LIGHT_WOUNDS; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern CauseLightWounds g_CauseLightWounds;

#endif // __SKILL_CAUSE_LIGHT_WOUNDS_HANDLER_H__
