//////////////////////////////////////////////////////////////////////////////
// Filename    : YellowPoison.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_YELLOW_POISON_HANDLER_H__
#define __SKILL_YELLOW_POISON_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class YellowPoison;
//////////////////////////////////////////////////////////////////////////////

class YellowPoison : public SkillHandler 
{
public:
	YellowPoison() throw() {}
	~YellowPoison() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "YellowPoison"; }
	SkillType_t getSkillType() const throw() { return SKILL_YELLOW_POISON; }

	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ObjectID_t,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);
	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern YellowPoison g_YellowPoison;

#endif // __SKILL_YELLOW_POISON_HANDLER_H__
