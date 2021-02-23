//////////////////////////////////////////////////////////////////////////////
// Filename    : ShadowDancing.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SHADOW_DANCING_HANDLER_H__
#define __SKILL_SHADOW_DANCING_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ShadowDancing;
//////////////////////////////////////////////////////////////////////////////

class ShadowDancing : public SkillHandler 
{
public:
	ShadowDancing() throw() {}
	~ShadowDancing() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "ShadowDancing"; }
	SkillType_t getSkillType() const throw() { return SKILL_SHADOW_DANCING; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ShadowDancing g_ShadowDancing;

#endif // __SKILL_SHADOW_DANCING_HANDLER_H__
