//////////////////////////////////////////////////////////////////////////////
// Filename    : Doom.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DOOM_HANDLER_H__
#define __SKILL_DOOM_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Doom;
//////////////////////////////////////////////////////////////////////////////

class Doom : public SkillHandler 
{
public:
	Doom() throw() {}
	~Doom() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Doom"; }
	SkillType_t getSkillType() const throw() { return SKILL_DOOM; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void executeMonster(Zone* pZone, Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Doom g_Doom;

#endif // __SKILL_DOOM_HANDLER_H__
