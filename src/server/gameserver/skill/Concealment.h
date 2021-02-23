//////////////////////////////////////////////////////////////////////////////
// Filename    : Concealment.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CONCEALMENT_HANDLER_H__
#define __SKILL_CONCEALMENT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Concealment;
//////////////////////////////////////////////////////////////////////////////

class Concealment : public SkillHandler 
{
public:
	Concealment() throw() {}
	~Concealment() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Concealment"; }
	SkillType_t getSkillType() const throw() { return SKILL_CONCEALMENT; }

	void execute(Slayer* pSlayer,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Concealment g_Concealment;

#endif // __SKILL_CONCEALMENT_HANDLER_H__
