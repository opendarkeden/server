//////////////////////////////////////////////////////////////////////////////
// Filename    : SharpChakram.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SHARP_CHAKRAM_HANDLER_H__
#define __SKILL_SHARP_CHAKRAM_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SharpChakram;
//////////////////////////////////////////////////////////////////////////////

class SharpChakram : public SkillHandler 
{
public:
	SharpChakram() throw() {}
	~SharpChakram() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SharpChakram"; }
	SkillType_t getSkillType() const throw() { return SKILL_SHARP_CHAKRAM; }

	void execute(Ousters* pOusters,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SharpChakram g_SharpChakram;

#endif // __SKILL_SHARP_CHAKRAM_HANDLER_H__
