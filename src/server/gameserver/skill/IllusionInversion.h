//////////////////////////////////////////////////////////////////////////////
// Filename    : IllusionInversion.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ILLUSION_INVERSION_HANDLER_H__
#define __SKILL_ILLUSION_INVERSION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class IllusionInversion;
//////////////////////////////////////////////////////////////////////////////

class IllusionInversion : public SkillHandler 
{
public:
	IllusionInversion() throw() {}
	~IllusionInversion() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "IllusionInversion"; }

	SkillType_t getSkillType() const throw() { return SKILL_ILLUSION_INVERSION; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern IllusionInversion g_IllusionInversion;

#endif // __SKILL_ILLUSION_INVERSION_HANDLER_H__
