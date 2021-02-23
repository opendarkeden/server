//////////////////////////////////////////////////////////////////////////////
// Filename    : UnterfeldwebelFire.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_UNTERFELDWEBEL_FIRE_HANDLER_H__
#define __SKILL_UNTERFELDWEBEL_FIRE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class UnterfeldwebelFire;
//////////////////////////////////////////////////////////////////////////////

class UnterfeldwebelFire : public SkillHandler 
{
public:
	UnterfeldwebelFire() throw() {}
	~UnterfeldwebelFire() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "UnterfeldwebelFire"; }
	SkillType_t getSkillType() const throw() { return SKILL_UNTERFELDWEBEL_FIRE; }

	void execute(Monster* pPlayer, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output) {}
};

// global variable declaration
extern UnterfeldwebelFire g_UnterfeldwebelFire;

#endif // __SKILL_UNTERFELDWEBEL_FIRE_HANDLER_H__
