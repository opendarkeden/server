//////////////////////////////////////////////////////////////////////////////
// Filename    : IllusionOfAvenge.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ILLUSION_OF_AVENGE_HANDLER_H__
#define __SKILL_ILLUSION_OF_AVENGE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class IllusionOfAvenge;
//////////////////////////////////////////////////////////////////////////////

class IllusionOfAvenge : public SkillHandler 
{
public:
	IllusionOfAvenge() throw() {}
	~IllusionOfAvenge() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "IllusionOfAvenge"; }
	SkillType_t getSkillType() const throw() { return SKILL_ILLUSION_OF_AVENGE; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern IllusionOfAvenge g_IllusionOfAvenge;

#endif // __SKILL_ILLUSION_OF_AVENGE_HANDLER_H__
