//////////////////////////////////////////////////////////////////////////////
// Filename    : Reflection.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_REFLECTION_HANDLER_H__
#define __SKILL_REFLECTION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Reflection;
//////////////////////////////////////////////////////////////////////////////

class Reflection : public SkillHandler 
{
public:
	Reflection() throw() {}
	~Reflection() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Reflection"; }
	SkillType_t getSkillType() const throw() { return SKILL_REFLECTION; }

	void execute(Slayer* pSlayer,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

bool CheckReflection(Creature* pAttacker, Creature* pTargetCreature, SkillType_t SkillType);
	
// global variable declaration
extern Reflection g_Reflection;

#endif // __SKILL_REFLECTION_HANDLER_H__
