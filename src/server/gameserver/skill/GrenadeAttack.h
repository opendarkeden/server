//////////////////////////////////////////////////////////////////////////////
// Filename    : GrenadeAttack.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GRENADE_ATTACK_HANDLER_H__
#define __SKILL_GRENADE_ATTACK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class GrenadeAttack;
//////////////////////////////////////////////////////////////////////////////

class GrenadeAttack : public SkillHandler 
{
public:
	GrenadeAttack() throw() {}
	~GrenadeAttack() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "GrenadeAttack"; }
	SkillType_t getSkillType() const throw() { return SKILL_GRENADE_ATTACK; }

	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern GrenadeAttack g_GrenadeAttack;

#endif // __SKILL_GRENADE_ATTACK_HANDLER_H__
