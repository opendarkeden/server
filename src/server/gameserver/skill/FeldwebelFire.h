//////////////////////////////////////////////////////////////////////////////
// Filename    : UeldwebelFire.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_FELDWEBEL_FIRE_HANDLER_H__
#define __SKILL_FELDWEBEL_FIRE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class UeldwebelFire;
//////////////////////////////////////////////////////////////////////////////

class FeldwebelFire : public SkillHandler 
{
public:
	FeldwebelFire() throw() {}
	~FeldwebelFire() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "FeldwebelFire"; }
	SkillType_t getSkillType() const throw() { return SKILL_FELDWEBEL_FIRE; }

	void execute(Monster* pPlayer, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output) {}
};

// global variable declaration
extern FeldwebelFire g_FeldwebelFire;

#endif // __SKILL_FELDWEBEL_FIRE_HANDLER_H__
