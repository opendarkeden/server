//////////////////////////////////////////////////////////////////////////////
// Filename    : ThrowHolyWater.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_THROW_HOLY_WATER_HANDLER_H__
#define __SKILL_THROW_HOLY_WATER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ThrowHolyWater;
//////////////////////////////////////////////////////////////////////////////

class ThrowHolyWater : public SkillHandler 
{
public:
	ThrowHolyWater() throw() {}
	~ThrowHolyWater() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "ThrowHolyWater"; }
	SkillType_t getSkillType() const throw() { return SKILL_THROW_HOLY_WATER; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, ObjectID_t ItemObjectID, CoordInven_t X, CoordInven_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output) {}
};

// global variable declaration
extern ThrowHolyWater g_ThrowHolyWater;

#endif // __SKILL_THROW_HOLY_WATER_HANDLER_H__
