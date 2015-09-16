//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyNail.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_NAIL_HANDLER_H__
#define __SKILL_BLOODY_NAIL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodyNail;
//////////////////////////////////////////////////////////////////////////////

class BloodyNail: public SkillHandler 
{
public:
	BloodyNail() throw() {}
	~BloodyNail() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BloodyNail"; }

	SkillType_t getSkillType() const throw() { return SKILL_BLOODY_NAIL; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BloodyNail g_BloodyNail;

#endif // __SKILL_BLOODY_NAIL_HANDLER_H__
