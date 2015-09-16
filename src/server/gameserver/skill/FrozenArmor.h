//////////////////////////////////////////////////////////////////////////////
// Filename    : FrozenArmor.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_FROZEN_ARMOR_HANDLER_H__
#define __SKILL_FROZEN_ARMOR_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class FrozenArmor;
//////////////////////////////////////////////////////////////////////////////

class FrozenArmor : public SkillHandler 
{
public:
	FrozenArmor() throw() {}
	~FrozenArmor() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "FrozenArmor"; }
	SkillType_t getSkillType() const throw() { return SKILL_FROZEN_ARMOR; }

	void execute(Ousters* pOusters,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern FrozenArmor g_FrozenArmor;

#endif // __SKILL_FROZEN_ARMOR_HANDLER_H__
