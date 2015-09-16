//////////////////////////////////////////////////////////////////////////////
// Filename    : Hallucination.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HALLUCINATION_HANDLER_H__
#define __SKILL_HALLUCINATION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Hallucination;
//////////////////////////////////////////////////////////////////////////////

class Hallucination : public SkillHandler 
{
public:
	Hallucination() throw() {}
	~Hallucination() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Hallucination"; }
	SkillType_t getSkillType() const throw() { return SKILL_HALLUCINATION; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);
	void executeMonster(Zone* pZone, Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Hallucination g_Hallucination;

#endif // __SKILL_HALLUCINATION_HANDLER_H__
