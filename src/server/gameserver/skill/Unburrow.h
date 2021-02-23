//////////////////////////////////////////////////////////////////////////////
// Filename    : Unburrow.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_UN_BURROW_HANDLER_H__
#define __SKILL_UN_BURROW_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Unburrow;
//////////////////////////////////////////////////////////////////////////////

class Unburrow: public SkillHandler 
{
public:
	Unburrow() throw() {}
	~Unburrow() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Unburrow"; }
	SkillType_t getSkillType() const throw() { return SKILL_UN_BURROW; }

	void execute(Vampire* pVampire) throw(Error);
	void execute(Monster* pMonster) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output) {}
};

// global variable declaration
extern Unburrow g_Unburrow;

#endif // __SKILL_UN_BURROW_HANDLER_H__
