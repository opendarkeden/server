//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidBolt.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ACID_BOLT_HANDLER_H__
#define __SKILL_ACID_BOLT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidBolt;
//////////////////////////////////////////////////////////////////////////////

class AcidBolt : public SkillHandler 
{
public:
	AcidBolt() throw() {}
	~AcidBolt() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "AcidBolt"; }
	SkillType_t getSkillType() const throw() { return SKILL_ACID_BOLT; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern AcidBolt g_AcidBolt;

#endif // __SKILL_ACID_BOLT_HANDLER_H__
