//////////////////////////////////////////////////////////////////////////////
// Filename    : PoisonousHands.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_POISONOUS_HANDS_HANDLER_H__
#define __SKILL_POISONOUS_HANDS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class PoisonousHands;
//////////////////////////////////////////////////////////////////////////////

class PoisonousHands: public SkillHandler 
{
public:
	PoisonousHands() throw() {}
	~PoisonousHands() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "PoisonousHands"; }
	SkillType_t getSkillType() const throw() { return SKILL_POISONOUS_HANDS; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern PoisonousHands g_PoisonousHands;

#endif // __SKILL_POISONOUS_HANDS_HANDLER_H__
