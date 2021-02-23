//////////////////////////////////////////////////////////////////////////////
// Filename    : Requital.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_REQUITAL_HANDLER_H__
#define __SKILL_REQUITAL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Requital;
//////////////////////////////////////////////////////////////////////////////

class Requital: public SkillHandler 
{
public:
	Requital() throw() {}
	~Requital() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Requital"; }
	SkillType_t getSkillType() const throw() { return SKILL_REQUITAL; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Requital g_Requital;

#endif // __SKILL_REQUITAL_HANDLER_H__
