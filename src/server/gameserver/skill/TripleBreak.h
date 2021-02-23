//////////////////////////////////////////////////////////////////////////////
// Filename    : TripleBreak.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TRIPLE_BREAK_HANDLER_H__
#define __SKILL_TRIPLE_BREAK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TripleBreak;
//////////////////////////////////////////////////////////////////////////////

class TripleBreak : public SkillHandler 
{
public:
	TripleBreak() throw() {}
	~TripleBreak() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "TripleBreak"; }
	SkillType_t getSkillType() const throw() { return SKILL_TRIPLE_BREAK; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TripleBreak g_TripleBreak;

#endif // __SKILL_TRIPLE_BREAK_HANDLER_H__
