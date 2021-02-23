//////////////////////////////////////////////////////////////////////////////
// Filename    : LightningHand.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_LIGHTNING_HAND_HANDLER_H__
#define __SKILL_LIGHTNING_HAND_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class LightningHand;
//////////////////////////////////////////////////////////////////////////////

class LightningHand : public SkillHandler 
{
public:
	LightningHand() throw() {}
	~LightningHand() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "LightningHand"; }
	SkillType_t getSkillType() const throw() { return SKILL_LIGHTNING_HAND; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern LightningHand g_LightningHand;

#endif // __SKILL_LIGHTNING_HAND_HANDLER_H__
