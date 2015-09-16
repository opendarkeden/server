//////////////////////////////////////////////////////////////////////////////
// Filename    : Sacrifice.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SACRIFICE_HANDLER_H__
#define __SKILL_SACRIFICE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Sacrifice;
//////////////////////////////////////////////////////////////////////////////

class Sacrifice : public SkillHandler 
{
public:
	Sacrifice() throw() {}
	~Sacrifice() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Sacrifice"; }
	SkillType_t getSkillType() const throw() { return SKILL_SACRIFICE; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Sacrifice g_Sacrifice;

#endif // __SKILL_SACRIFICE_HANDLER_H__
