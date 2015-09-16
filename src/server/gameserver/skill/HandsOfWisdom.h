//////////////////////////////////////////////////////////////////////////////
// Filename    : HandsOfWisdom.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HANDS_OF_WISDOM_HANDLER_H__
#define __SKILL_HANDS_OF_WISDOM_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class HandsOfWisdom;
//////////////////////////////////////////////////////////////////////////////

class HandsOfWisdom: public SkillHandler 
{
public:
	HandsOfWisdom() throw() {}
	~HandsOfWisdom() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "HandsOfWisdom"; }

	SkillType_t getSkillType() const throw() { return SKILL_HANDS_OF_WISDOM; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern HandsOfWisdom g_HandsOfWisdom;

#endif // __SKILL_HANDS_OF_WISDOM_HANDLER_H__
