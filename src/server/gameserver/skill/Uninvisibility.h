//////////////////////////////////////////////////////////////////////////////
// Filename    : Uninvisibility.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_UN_INVISIBILITY_HANDLER_H__
#define __SKILL_UN_INVISIBILITY_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Uninvisibility;
//////////////////////////////////////////////////////////////////////////////

class Uninvisibility: public SkillHandler 
{
public:
	Uninvisibility() throw() {}
	~Uninvisibility() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Uninvisibility"; }
	SkillType_t getSkillType() const throw() { return SKILL_UN_INVISIBILITY; }

	void execute(Vampire* pVampire) throw(Error);
	void execute(Monster* pMonster) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output) {}
};

// global variable declaration
extern Uninvisibility g_Uninvisibility;

#endif // __SKILL_UN_INVISIBILITY_HANDLER_H__
