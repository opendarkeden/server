//////////////////////////////////////////////////////////////////////////////
// Filename    : SelfDestruction.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SELF_DESTRUCTION_HANDLER_H__
#define __SKILL_SELF_DESTRUCTION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SelfDestruction;
//////////////////////////////////////////////////////////////////////////////

class SelfDestruction: public SkillHandler 
{
public:
	SelfDestruction() throw();
	~SelfDestruction() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SelfDestruction"; }
	SkillType_t getSkillType() const throw() { return SKILL_SELF_DESTRUCTION; }

	void execute(Monster* pMonster) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private :
};

// global variable declaration
extern SelfDestruction g_SelfDestruction;

#endif // __SKILL_HIDE_HANDLER_H__
