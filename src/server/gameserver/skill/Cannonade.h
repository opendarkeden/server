
//////////////////////////////////////////////////////////////////////////////
// Filename    : Cannonade.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CANNONADE_HANDLER_H__
#define __SKILL_CANNONADE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Cannonade;
//////////////////////////////////////////////////////////////////////////////

class Cannonade : public SkillHandler 
{
public:
	Cannonade() throw() {}
	~Cannonade() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Cannonade"; }
	SkillType_t getSkillType() const throw() { return SKILL_CANNONADE; }

	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Cannonade g_Cannonade;

#endif // __SKILL_CANNONADE_HANDLER_H__
