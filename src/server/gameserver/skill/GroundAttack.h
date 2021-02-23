//////////////////////////////////////////////////////////////////////////////
// Filename    : GroundAttack.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GROUND_ATTACK_HANDLER_H__
#define __SKILL_GROUND_ATTACK_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class GroundAttack;
//////////////////////////////////////////////////////////////////////////////

class GroundAttack : public SkillHandler 
{
public:
	GroundAttack() throw() {}
	~GroundAttack() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "GroundAttack"; }
	SkillType_t getSkillType() const throw() { return SKILL_GROUND_ATTACK; }

	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ObjectID_t,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern GroundAttack g_GroundAttack;

#endif // __SKILL_GROUND_ATTACK_HANDLER_H__
