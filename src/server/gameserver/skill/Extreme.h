//////////////////////////////////////////////////////////////////////////////
// Filename    : Extreme.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////

#ifndef __SKILL_EXTREME_HANDLER_H__
#define __SKILL_EXTREME_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Extreme;
//////////////////////////////////////////////////////////////////////////////

class Extreme : public SkillHandler 
{
public:
	Extreme() throw() {}
	~Extreme() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Extreme"; }
	SkillType_t getSkillType() const throw() { return SKILL_EXTREME; }

	void execute(Vampire* pVampire ) throw(Error);
	void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ObjectID_t ObjectID,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);


	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Extreme g_Extreme;

#endif // __SKILL_EXTREME_HANDLER_H__
