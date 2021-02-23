//////////////////////////////////////////////////////////////////////////////
// Filename    : HeterChakram.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HETER_CHAKRAM_HANDLER_H__
#define __SKILL_HETER_CHAKRAM_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class HeterChakram;
//////////////////////////////////////////////////////////////////////////////

class HeterChakram: public SkillHandler 
{
public:
	HeterChakram() throw() {}
	~HeterChakram() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "HeterChakram"; }

	SkillType_t getSkillType() const throw() { return SKILL_HETER_CHAKRAM; }

	void execute(Ousters* pOusters, ObjectID_t targetObject, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern HeterChakram g_HeterChakram;

#endif // __SKILL_HETER_CHAKRAM_HANDLER_H__
