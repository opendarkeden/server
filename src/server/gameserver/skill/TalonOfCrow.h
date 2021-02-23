//////////////////////////////////////////////////////////////////////////////
// Filename    : TalonOfCrow.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TALON_OF_CROW_HANDLER_H__
#define __SKILL_TALON_OF_CROW_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TalonOfCrow;
//////////////////////////////////////////////////////////////////////////////

class TalonOfCrow: public SkillHandler 
{
public:
	TalonOfCrow() throw() {}
	~TalonOfCrow() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "TalonOfCrow"; }

	SkillType_t getSkillType() const throw() { return SKILL_TALON_OF_CROW; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TalonOfCrow g_TalonOfCrow;

#endif // __SKILL_TALON_OF_CROW_HANDLER_H__
