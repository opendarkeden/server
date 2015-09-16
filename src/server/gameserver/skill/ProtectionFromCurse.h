//////////////////////////////////////////////////////////////////////////////
// Filename    : ProtectionFromCurse.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PROTECTION_FROM_CURSE_HANDLER_H__
#define __SKILL_PROTECTION_FROM_CURSE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ProtectionFromCurse;
//////////////////////////////////////////////////////////////////////////////

class ProtectionFromCurse: public SkillHandler 
{
public:
	ProtectionFromCurse() throw() {}
	~ProtectionFromCurse() throw() {}

public:
    string getSkillHandlerName() const throw() { return "ProtectionFromCurse"; }
	SkillType_t getSkillType() const throw() { return SKILL_PROTECTION_FROM_CURSE; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ProtectionFromCurse g_ProtectionFromCurse;

#endif // __SKILL_PROTECTION_FROM_CURSE_HANDLER_H__
