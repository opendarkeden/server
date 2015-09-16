//////////////////////////////////////////////////////////////////////////////
// Filename    : ProtectionFromPoison.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PROTECTION_FROM_POISON_HANDLER_H__
#define __SKILL_PROTECTION_FROM_POISON_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ProtectionFromPoison;
//////////////////////////////////////////////////////////////////////////////

class ProtectionFromPoison: public SkillHandler 
{
public:
	ProtectionFromPoison() throw() {}
	~ProtectionFromPoison() throw() {}

public:
    string getSkillHandlerName() const throw() { return "ProtectionFromPoison"; }
	SkillType_t getSkillType() const throw() { return SKILL_PROTECTION_FROM_POISON; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ProtectionFromPoison g_ProtectionFromPoison;

#endif // __SKILL_PROTECTION_FROM_POISON_HANDLER_H__
