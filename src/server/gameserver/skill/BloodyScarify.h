//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyScarify.h 
// Written By  : Coffee  
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_SCARIFY_HANDLER_H__
#define __SKILL_BLOODY_SCARIFY_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodyScarify;
//////////////////////////////////////////////////////////////////////////////

class BloodyScarify: public SkillHandler 
{
public:
	BloodyScarify() throw() {}
	~BloodyScarify() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BloodyScarify"; }

	SkillType_t getSkillType() const throw() { return SKILL_BLLODY_SCARIFY; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);

	void eatCorpse(Vampire* pVampire, Item* pCorpse, VampireSkillSlot* pVampireSkillSlot);
	void eatComaCreature(Vampire* pVampire, Creature* pComaCreature);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BloodyScarify g_BloodyScarify;

#endif // __SKILL_BLOODY_SCARIFY_HANDLER_H__
