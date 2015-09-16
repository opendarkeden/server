//////////////////////////////////////////////////////////////////////////////
// Filename    : WildWolf.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_WILD_WOLF_HANDLER_H__
#define __SKILL_WILD_WOLF_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class WildWolf;
//////////////////////////////////////////////////////////////////////////////

class WildWolf: public SkillHandler 
{
public:
	WildWolf() throw() {}
	~WildWolf() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "WildWolf"; }

	SkillType_t getSkillType() const throw() { return SKILL_WILD_WOLF; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);

	void eatCorpse(Vampire* pVampire, Item* pCorpse, VampireSkillSlot* pVampireSkillSlot);
	void eatComaCreature(Vampire* pVampire, Creature* pComaCreature);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern WildWolf g_WildWolf;

#endif // __SKILL_WILD_WOLF_HANDLER_H__
