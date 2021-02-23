//////////////////////////////////////////////////////////////////////////////
// Filename    : GreenStalker.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GREEN_STALKER_HANDLER_H__
#define __SKILL_GREEN_STALKER_HANDLER_H__

#include "SkillHandler.h"

#define PER_DAMAGE_GREEN_STALKER	10

//////////////////////////////////////////////////////////////////////////////
// class GreenStalker;
//////////////////////////////////////////////////////////////////////////////

class GreenStalker: public SkillHandler 
{
public:
	GreenStalker() throw() {}
	~GreenStalker() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "GreenStalker"; }
	SkillType_t getSkillType() const throw() { return SKILL_GREEN_STALKER; }

	void execute(Vampire* pVampire, ObjectID_t targetObject, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern GreenStalker g_GreenStalker;

#endif // __SKILL_GREEN_STALKER_HANDLER_H__
