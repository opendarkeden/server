//////////////////////////////////////////////////////////////////////////////
// Filename    : HandsOfFire.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HANDS_OF_FIRE_HANDLER_H__
#define __SKILL_HANDS_OF_FIRE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class HandsOfFire;
//////////////////////////////////////////////////////////////////////////////

class HandsOfFire : public SkillHandler 
{
public:
	HandsOfFire() throw() {}
	~HandsOfFire() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "HandsOfFire"; }
	SkillType_t getSkillType() const throw() { return SKILL_HANDS_OF_FIRE; }

	void execute(Ousters* pOusters,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern HandsOfFire g_HandsOfFire;

#endif // __SKILL_HANDS_OF_FIRE_HANDLER_H__
