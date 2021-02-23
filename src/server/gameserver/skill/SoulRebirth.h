//////////////////////////////////////////////////////////////////////////////
// Filename    : SoulRebirth.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SOUL_REBIRTH_HANDLER_H__
#define __SKILL_SOUL_REBIRTH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SoulRebirth;
//////////////////////////////////////////////////////////////////////////////

class SoulRebirth : public SkillHandler 
{
public:
	SoulRebirth() throw() {}
	~SoulRebirth() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SoulRebirth"; }

	SkillType_t getSkillType() const throw() { return SKILL_SOUL_REBIRTH; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SoulRebirth g_SoulRebirth;

#endif // __SKILL_SOUL_REBIRTH_HANDLER_H__
