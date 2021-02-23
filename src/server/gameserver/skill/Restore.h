//////////////////////////////////////////////////////////////////////////////
// Filename    : Restore.h 
// Written By  :
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_RESTORE_HANDLER_H__
#define __SKILL_RESTORE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Restore;
//////////////////////////////////////////////////////////////////////////////

class NPC;

class Restore: public SkillHandler 
{
public:
	Restore() throw() {}
	~Restore() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Restore"; }
	SkillType_t getSkillType() const throw() { return SKILL_RESTORE; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(NPC* pNPC, Creature* pTargetCreature) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output) {}
};

// global variable declaration
extern Restore g_Restore;

#endif // __SKILL_RESTORE_HANDLER_H__
