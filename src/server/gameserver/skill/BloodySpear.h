//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodySpear.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_SPEAR_HANDLER_H__
#define __SKILL_BLOODY_SPEAR_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodySpear;
//////////////////////////////////////////////////////////////////////////////

class BloodySpear : public SkillHandler 
{
public:
	BloodySpear() throw() {}
	~BloodySpear() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BloodySpear"; }
	SkillType_t getSkillType() const throw() { return SKILL_BLOODY_SPEAR; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BloodySpear g_BloodySpear;

#endif // __SKILL_BLOODY_SPEAR_HANDLER_H__
