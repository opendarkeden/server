//////////////////////////////////////////////////////////////////////////////
// Filename    : Hide.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HIDE_HANDLER_H__
#define __SKILL_HIDE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Hide;
//////////////////////////////////////////////////////////////////////////////

class Hide: public SkillHandler 
{
public:
	Hide() throw() {}
	~Hide() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Hide"; }
	SkillType_t getSkillType() const throw() { return SKILL_HIDE; }

	void execute(Vampire* pVampire, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) ;
	void execute(Monster* pMonster) ;

	void computeOutput(const SkillInput& input, SkillOutput& output) {}
};

// global variable declaration
extern Hide g_Hide;

#endif // __SKILL_HIDE_HANDLER_H__
