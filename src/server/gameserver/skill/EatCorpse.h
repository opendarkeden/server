//////////////////////////////////////////////////////////////////////////////
// Filename    : EatCorpse.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_EAT_CORPSE_HANDLER_H__
#define __SKILL_EAT_CORPSE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class EatCorpse;
//////////////////////////////////////////////////////////////////////////////

class EatCorpse : public SkillHandler 
{
public:
	EatCorpse() throw() {}
	~EatCorpse() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "EatCorpse"; }
	SkillType_t getSkillType() const throw() { return SKILL_EAT_CORPSE; }

	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output) {}
};

// global variable declaration
extern EatCorpse g_EatCorpse;

#endif // __SKILL_EAT_CORPSE_HANDLER_H__
