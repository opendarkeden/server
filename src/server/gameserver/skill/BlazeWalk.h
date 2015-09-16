//////////////////////////////////////////////////////////////////////////////
// Filename    : BlazeWalk.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLAZE_WALK_HANDLER_H__
#define __SKILL_BLAZE_WALK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BlazeWalk;
//////////////////////////////////////////////////////////////////////////////

class BlazeWalk : public SkillHandler 
{
public:
	BlazeWalk() throw() {}
	~BlazeWalk() throw() {}

public :
    string getSkillHandlerName() const throw() { return "BlazeWalk"; }
	SkillType_t getSkillType() const throw() { return SKILL_BLAZE_WALK; }

	void execute(Slayer* pSlayer,ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BlazeWalk g_BlazeWalk;

#endif // __SKILL_BLAZE_WALK_HANDLER_H__
