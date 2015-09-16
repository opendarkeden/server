//////////////////////////////////////////////////////////////////////////////
// Filename    : Purify.h 
// Written By  : elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PURIFY_HANDLER_H__
#define __SKILL_PURIFY_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Purify;
//////////////////////////////////////////////////////////////////////////////

class Purify: public SkillHandler 
{
public:
	Purify() throw() {}
	~Purify() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Purify"; }
	SkillType_t getSkillType() const throw() { return SKILL_PURIFY; }

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Purify g_Purify;

#endif // __SKILL_PURIFY_HANDLER_H__
