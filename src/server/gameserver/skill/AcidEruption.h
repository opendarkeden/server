//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidEruption.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ACID_ERUPTION_HANDLER_H__
#define __SKILL_ACID_ERUPTION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidEruption;
//////////////////////////////////////////////////////////////////////////////

class AcidEruption : public SkillHandler 
{
public:
	AcidEruption() throw() {}
	~AcidEruption() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "AcidEruption"; }
	SkillType_t getSkillType() const throw() { return SKILL_ACID_ERUPTION; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern AcidEruption g_AcidEruption;

#endif // __SKILL_ACID_ERUPTION_HANDLER_H__
