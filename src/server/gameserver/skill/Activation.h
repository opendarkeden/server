//////////////////////////////////////////////////////////////////////////////
// Filename    : Activation.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ACTIVATION_HANDLER_H__
#define __SKILL_ACTIVATION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Activation;
//////////////////////////////////////////////////////////////////////////////

class Activation: public SkillHandler 
{
public:
	Activation() throw() {}
	~Activation() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Activation"; }
	SkillType_t getSkillType() const throw() { return SKILL_ACTIVATION; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Activation g_Activation;

#endif // __SKILL_ACTIVATION_HANDLER_H__
