//////////////////////////////////////////////////////////////////////////////
// Filename    : AuraShield.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_AURA_SHIELD_HANDLER_H__
#define __SKILL_AURA_SHIELD_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AuraShield;
//////////////////////////////////////////////////////////////////////////////

class AuraShield : public SkillHandler 
{
public:
	AuraShield() throw() {}
	~AuraShield() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "AuraShield"; }
	SkillType_t getSkillType() const throw() { return SKILL_AURA_SHIELD; }

	void execute(Slayer* pSlayer,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

bool CheckAuraShield(Creature* pAttacker, Creature* pTargetCreature, Damage_t damage = 0, Range_t range = 1);
	
// global variable declaration
extern AuraShield g_AuraShield;

#endif // __SKILL_AURA_SHIELD_HANDLER_H__
