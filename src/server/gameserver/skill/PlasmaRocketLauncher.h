//////////////////////////////////////////////////////////////////////////////
// Filename    : PlasmaRocketLauncher.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_PLASMA_ROCKET_LAUNCHER_HANDLER_H__
#define __SKILL_PLASMA_ROCKET_LAUNCHER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class PlasmaRocketLauncher;
//////////////////////////////////////////////////////////////////////////////

class PlasmaRocketLauncher: public SkillHandler 
{
public:
	PlasmaRocketLauncher() throw() {}
	~PlasmaRocketLauncher() throw() {}

public:
    string getSkillHandlerName() const throw() { return "PlasmaRocketLauncher"; }
	SkillType_t getSkillType() const throw() { return SKILL_PLASMA_ROCKET_LAUNCHER; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern PlasmaRocketLauncher g_PlasmaRocketLauncher;

#endif // __SKILL_PLASMA_ROCKET_LAUNCHER_HANDLER_H__
