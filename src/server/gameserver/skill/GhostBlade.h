//////////////////////////////////////////////////////////////////////////////
// Filename    : GhostBlade.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GHOST_BLADE_HANDLER_H__
#define __SKILL_GHOST_BLADE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class GhostBlade;
//////////////////////////////////////////////////////////////////////////////

class GhostBlade : public SkillHandler 
{
public:
	GhostBlade() throw() {}
	~GhostBlade() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "GhostBlade"; }
	SkillType_t getSkillType() const throw() { return SKILL_GHOST_BLADE; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern GhostBlade g_GhostBlade;

#endif // __SKILL_GHOST_BLADE_HANDLER_H__
