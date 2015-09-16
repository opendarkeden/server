//////////////////////////////////////////////////////////////////////////////
// Filename    : Paralyze.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PARALYZE_HANDLER_H__
#define __SKILL_PARALYZE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Paralyze;
//////////////////////////////////////////////////////////////////////////////

class Paralyze: public SkillHandler 
{
public:
	Paralyze() throw() {}
	~Paralyze() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Paralyze"; }
	SkillType_t getSkillType() const throw() { return SKILL_PARALYZE; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void executeMonster(Zone* pZone, Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Paralyze g_Paralyze;

#endif // __SKILL_PARALYZE_HANDLER_H__
