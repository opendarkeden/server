//////////////////////////////////////////////////////////////////////////////
// Filename    : WillOfLife.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////

#ifndef __SKILL_WILL_OF_LIFE_HANDLER_H__
#define __SKILL_WILL_OF_LIFE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class WillOfLife;
//////////////////////////////////////////////////////////////////////////////

class WillOfLife : public SkillHandler 
{
public:
	WillOfLife() throw() {}
	~WillOfLife() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "WillOfLife"; }
	SkillType_t getSkillType() const throw() { return SKILL_WILL_OF_LIFE; }

	void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern WillOfLife g_WillOfLife;

#endif // __SKILL_WILL_OF_LIFE_HANDLER_H__
