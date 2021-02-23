//////////////////////////////////////////////////////////////////////////////
// Filename    : HurricaneCombo.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HURRICANE_COMBO_HANDLER_H__
#define __SKILL_HURRICANE_COMBO_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class HurricaneCombo;
//////////////////////////////////////////////////////////////////////////////

class HurricaneCombo : public SkillHandler 
{
public:
	HurricaneCombo() throw() {}
	~HurricaneCombo() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "HurricaneCombo"; }
	SkillType_t getSkillType() const throw() { return SKILL_HURRICANE_COMBO; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern HurricaneCombo g_HurricaneCombo;

#endif // __SKILL_HURRICANE_COMBO_HANDLER_H__
