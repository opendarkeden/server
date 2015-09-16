//////////////////////////////////////////////////////////////////////////////
// Filename    : Glacier1.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GLACIER_1_HANDLER_H__
#define __SKILL_GLACIER_1_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Glacier1;
//////////////////////////////////////////////////////////////////////////////

class Glacier1: public SkillHandler 
{
public:
	Glacier1() throw() {}
	~Glacier1() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Glacier1"; }
	SkillType_t getSkillType() const throw() { return SKILL_GLACIER_1; }

	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Glacier1 g_Glacier1;

#endif // __SKILL_GLACIER_1_HANDLER_H__
