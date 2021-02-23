//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyZenith.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_ZENITH_HANDLER_H__
#define __SKILL_BLOODY_ZENITH_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodyZenith;
//////////////////////////////////////////////////////////////////////////////

class BloodyZenith: public SkillHandler 
{
public:
	BloodyZenith() throw() {}
	~BloodyZenith() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BloodyZenith"; }

	SkillType_t getSkillType() const throw() { return SKILL_BLOODY_ZENITH; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BloodyZenith g_BloodyZenith;

#endif // __SKILL_BLOODY_ZENITH_HANDLER_H__
