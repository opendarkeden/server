//////////////////////////////////////////////////////////////////////////////
// Filename    : FierceFlame.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_FIERCE_FLAME_HANDLER_H__
#define __SKILL_FIERCE_FLAME_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class FierceFlame;
//////////////////////////////////////////////////////////////////////////////

class FierceFlame: public SkillHandler 
{
public:
	FierceFlame() throw() {}
	~FierceFlame() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "FierceFlame"; }

	SkillType_t getSkillType() const throw() { return SKILL_FIERCE_FLAME; }

	void execute(Ousters* pOusters, ObjectID_t targetObject, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern FierceFlame g_FierceFlame;

#endif // __SKILL_FIERCE_FLAME_HANDLER_H__
