//////////////////////////////////////////////////////////////////////////////
// Filename    : RemoveCurse.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_REMOVE_CURSE_HANDLER_H__
#define __SKILL_REMOVE_CURSE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class RemoveCurse;
//////////////////////////////////////////////////////////////////////////////

class RemoveCurse: public SkillHandler 
{
public:
	RemoveCurse() throw() {}
	~RemoveCurse() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "RemoveCurse"; }
	SkillType_t getSkillType() const throw() { return SKILL_REMOVE_CURSE; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern RemoveCurse g_RemoveCurse;

#endif // __SKILL_REMOVE_CURSE_HANDLER_H__
