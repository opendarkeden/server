//////////////////////////////////////////////////////////////////////////////
// Filename    : CrossCounter.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CROSS_COUNTER_HANDLER_H__
#define __SKILL_CROSS_COUNTER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class CrossCounter;
//////////////////////////////////////////////////////////////////////////////

class CrossCounter : public SkillHandler 
{
public:
	CrossCounter() throw() {}
	~CrossCounter() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "CrossCounter"; }
	SkillType_t getSkillType() const throw() { return SKILL_CROSS_COUNTER; }

	void execute(Slayer* pSlayer,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

bool CheckCrossCounter(Creature* pAttacker, Creature* pTargetCreature, Damage_t damage = 0, Range_t range = 1);
	
// global variable declaration
extern CrossCounter g_CrossCounter;

#endif // __SKILL_CROSS_COUNTER_HANDLER_H__
