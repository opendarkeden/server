//////////////////////////////////////////////////////////////////////////////
// Filename    : Berserker.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BERSERKER_HANDLER_H__
#define __SKILL_BERSERKER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Berserker;
//////////////////////////////////////////////////////////////////////////////

class Berserker : public SkillHandler 
{
public:
	Berserker() throw() {}
	~Berserker() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Berserker"; }
	SkillType_t getSkillType() const throw() { return SKILL_BERSERKER; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Berserker g_Berserker;

#endif // __SKILL_BERSERKER_HANDLER_H__
