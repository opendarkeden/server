//////////////////////////////////////////////////////////////////////////////
// Filename    : AuraBall.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_AURA_BALL_HANDLER_H__
#define __SKILL_AURA_BALL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AuraBall;
//////////////////////////////////////////////////////////////////////////////

class AuraBall : public SkillHandler 
{
public:
	AuraBall() throw() {}
	~AuraBall() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "AuraBall"; }

	SkillType_t getSkillType() const throw() { return SKILL_AURA_BALL; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern AuraBall g_AuraBall;

#endif // __SKILL_AURA_BALL_HANDLER_H__
