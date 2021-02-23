//////////////////////////////////////////////////////////////////////////////
// Filename    : BombCrashWalk.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BOMB_CRASH_WALK_HANDLER_H__
#define __SKILL_BOMB_CRASH_WALK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BombCrashWalk;
//////////////////////////////////////////////////////////////////////////////

class BombCrashWalk : public SkillHandler 
{
public:
	BombCrashWalk() throw() {}
	~BombCrashWalk() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BombCrashWalk"; }
	SkillType_t getSkillType() const throw() { return SKILL_BOMB_CRASH_WALK; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BombCrashWalk g_BombCrashWalk;

#endif // __SKILL_BOMB_CRASH_WALK_HANDLER_H__
