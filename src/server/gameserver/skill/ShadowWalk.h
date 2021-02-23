//////////////////////////////////////////////////////////////////////////////
// Filename    : ShadowWalk.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SHADOW_WALK_HANDLER_H__
#define __SKILL_SHADOW_WALK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ShadowWalk;
//////////////////////////////////////////////////////////////////////////////

class ShadowWalk : public SkillHandler 
{
public:
	ShadowWalk() throw() {}
	~ShadowWalk() throw() {}

public :
    string getSkillHandlerName() const throw() { return "ShadowWalk"; }
	SkillType_t getSkillType() const throw() { return SKILL_SHADOW_WALK; }

	void execute(Slayer* pSlayer,ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ShadowWalk g_ShadowWalk;

#endif // __SKILL_SHADOW_WALK_HANDLER_H__
