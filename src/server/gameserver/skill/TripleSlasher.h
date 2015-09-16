//////////////////////////////////////////////////////////////////////////////
// Filename    : TripleSlasher.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TRIPLE_SLASHER_HANDLER_H__
#define __SKILL_TRIPLE_SLASHER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TripleSlasher;
//////////////////////////////////////////////////////////////////////////////

class TripleSlasher : public SkillHandler 
{
public:
	TripleSlasher() throw() {}
	~TripleSlasher() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "TripleSlasher"; }
	SkillType_t getSkillType() const throw() { return SKILL_TRIPLE_SLASHER; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TripleSlasher g_TripleSlasher;

#endif // __SKILL_TRIPLE_SLASHER_HANDLER_H__
