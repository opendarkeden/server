//////////////////////////////////////////////////////////////////////////////
// Filename    : GreenPoison.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GREEN_POISON_HANDLER_H__
#define __SKILL_GREEN_POISON_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class GreenPoison;
//////////////////////////////////////////////////////////////////////////////

class GreenPoison : public SkillHandler 
{
public:
	GreenPoison() throw() {}
	~GreenPoison() throw() {}

public:
    string getSkillHandlerName() const throw() { return "GreenPoison"; }
	SkillType_t getSkillType() const throw() { return SKILL_GREEN_POISON; }

	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ObjectID_t,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);
	void execute(Monster* pMonster, ZoneCoord_t, ZoneCoord_t) throw(Error);

	void execute(Monster* pMonster) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern GreenPoison g_GreenPoison;

#endif // __SKILL_GREEN_POISON_HANDLER_H__
