//////////////////////////////////////////////////////////////////////////////
// Filename    : BackStab.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BACK_STAB_HANDLER_H__
#define __SKILL_BACK_STAB_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BackStab;
//////////////////////////////////////////////////////////////////////////////

class BackStab: public SkillHandler 
{
public:
	BackStab() throw() {}
	~BackStab() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BackStab"; }

	SkillType_t getSkillType() const throw() { return SKILL_BACK_STAB; }

	void execute(Ousters* pOusters, ObjectID_t targetObject, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BackStab g_BackStab;

#endif // __SKILL_BACK_STAB_HANDLER_H__
