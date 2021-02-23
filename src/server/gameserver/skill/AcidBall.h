//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidBall.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ACID_BALL_HANDLER_H__
#define __SKILL_ACID_BALL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidBall
//////////////////////////////////////////////////////////////////////////////

class AcidBall : public SkillHandler 
{
public:
	AcidBall() throw() {}
	~AcidBall() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "AcidBall"; }
	SkillType_t getSkillType() const throw() { return SKILL_ACID_BALL; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern AcidBall g_AcidBall;

#endif // __SKILL_ACID_BALL_HANDLER_H__
