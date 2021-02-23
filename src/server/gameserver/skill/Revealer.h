//////////////////////////////////////////////////////////////////////////////
// Filename    : Revealer.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_REVEALER_HANDLER_H__
#define __SKILL_REVEALER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Revealer;
//////////////////////////////////////////////////////////////////////////////

class Revealer: public SkillHandler 
{
public:
	Revealer() throw() {}
	~Revealer() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Revealer"; }
	SkillType_t getSkillType() const throw() { return SKILL_REVEALER; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Revealer g_Revealer;

#endif // __SKILL_REVEALER_HANDLER_H__
