//////////////////////////////////////////////////////////////////////////////
// Filename    : GammaChop.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GAMMA_CHOP_HANDLER_H__
#define __SKILL_GAMMA_CHOP_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class GammaChop;
//////////////////////////////////////////////////////////////////////////////

class GammaChop: public SkillHandler 
{
public:
	GammaChop() throw() {}
	~GammaChop() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "GammaChop"; }

	SkillType_t getSkillType() const throw() { return SKILL_GAMMA_CHOP; }

	void execute(Ousters* pOusters, ObjectID_t targetObject, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern GammaChop g_GammaChop;

#endif // __SKILL_GAMMA_CHOP_HANDLER_H__
