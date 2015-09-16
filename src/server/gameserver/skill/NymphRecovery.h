//////////////////////////////////////////////////////////////////////////////
// Filename    : NymphRecovery.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_NYMPH_RECOVERY_HANDLER_H__
#define __SKILL_NYMPH_RECOVERY_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class NymphRecovery;
//////////////////////////////////////////////////////////////////////////////

class NymphRecovery : public SkillHandler 
{
public:
	NymphRecovery() throw() {}
	~NymphRecovery() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "NymphRecovery"; }
	SkillType_t getSkillType() const throw() { return SKILL_NYMPH_RECOVERY; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID, OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern NymphRecovery g_NymphRecovery;

#endif // __SKILL_NYMPH_RECOVERY_HANDLER_H__
