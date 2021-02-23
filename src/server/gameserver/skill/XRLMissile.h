//////////////////////////////////////////////////////////////////////////////
// Filename    : XRL Missile.h 
// Written By  : rallser
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_XRL_Missile_HANDLER_H__
#define __SKILL_XRL_Missile_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class XRLMissile;
//////////////////////////////////////////////////////////////////////////////

class XRLMissile: public SkillHandler 
{
public:
	XRLMissile() throw() {}
	~XRLMissile() throw() {}

public:
    string getSkillHandlerName() const throw() { return "XRLMissile"; }
	SkillType_t getSkillType() const throw() { return SKILL_XRL_Missile; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern XRLMissile g_XRLMissile;

#endif // __SKILL_XRL_Missile_HANDLER_H__
