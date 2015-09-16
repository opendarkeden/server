//////////////////////////////////////////////////////////////////////////////
// Filename    : Expansion.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_EXPANSION_HANDLER_H__
#define __SKILL_EXPANSION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Expansion;
//////////////////////////////////////////////////////////////////////////////

class Expansion : public SkillHandler 
{
public:
	Expansion() throw() {}
	~Expansion() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Expansion"; }
	SkillType_t getSkillType() const throw() { return SKILL_EXPANSION; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Expansion g_Expansion;

#endif // __SKILL_EXPANSION_HANDLER_H__
