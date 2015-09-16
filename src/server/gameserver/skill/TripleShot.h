//////////////////////////////////////////////////////////////////////////////
// Filename    : TripleShot.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TRIPLE_SHOT_HANDLER_H__
#define __SKILL_TRIPLE_SHOT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TripleShot;
//////////////////////////////////////////////////////////////////////////////

class TripleShot : public SkillHandler 
{
public:
	TripleShot() throw() {}
	~TripleShot() throw() {}

public:
    string getSkillHandlerName() const throw() { return "TripleShot"; }
	SkillType_t getSkillType() const throw() { return SKILL_TRIPLE_SHOT; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TripleShot g_TripleShot;

#endif // __SKILL_TRIPLE_SHOT_HANDLER_H__
