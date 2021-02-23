//////////////////////////////////////////////////////////////////////////////
// Filename    : Glacier2.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GLACIER_2_HANDLER_H__
#define __SKILL_GLACIER_2_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Glacier2;
//////////////////////////////////////////////////////////////////////////////

class Glacier2: public SkillHandler 
{
public:
	Glacier2() throw() {}
	~Glacier2() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Glacier2"; }
	SkillType_t getSkillType() const throw() { return SKILL_GLACIER_2; }

	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Glacier2 g_Glacier2;

#endif // __SKILL_GLACIER_2_HANDLER_H__
