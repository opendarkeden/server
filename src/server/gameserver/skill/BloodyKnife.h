//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyKnife.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_KNIFE_HANDLER_H__
#define __SKILL_BLOODY_KNIFE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodyKnife;
//////////////////////////////////////////////////////////////////////////////

class BloodyKnife : public SkillHandler 
{
public:
	BloodyKnife() throw() {}
	~BloodyKnife() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BloodyKnife"; }
	SkillType_t getSkillType() const throw() { return SKILL_BLOODY_KNIFE; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BloodyKnife g_BloodyKnife;

#endif // __SKILL_BLOODY_KNIFE_HANDLER_H__
