//////////////////////////////////////////////////////////////////////////////
// Filename    : AbsorbSoul.h 
// Written By  : crazydog
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ABSORB_SOUL_HANDLER_H__
#define __SKILL_ABSORB_SOUL_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////
// class AbsorbSoul;
//////////////////////////////////////////////////////////////////////

class AbsorbSoul : public SkillHandler 
{
public:
	AbsorbSoul() throw() {}
	~AbsorbSoul() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "AbsorbSoul"; }
	SkillType_t getSkillType() const throw() { return SKILL_ABSORB_SOUL; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID, ZoneCoord_t TargetZoneX, ZoneCoord_t TargetZoneY, ObjectID_t ItemObjectID, CoordInven_t InvenX, CoordInven_t InvenY, CoordInven_t TargetInvenX, CoordInven_t TargetInvenY ) throw(Error);
	
	void makeLarvaToPupa(Ousters* pOusters, int TargetLevel, ObjectID_t ItemObjectID, CoordInven_t InvenX, CoordInven_t InvenY, CoordInven_t TargetInvenX, CoordInven_t TargetInvenY ) throw();

	void computeOutput(const SkillInput& input, SkillOutput& output) {}
};

// global variable declaration
extern AbsorbSoul g_AbsorbSoul;

#endif // __SKILL_ABSORB_SOUL_HANDLER_H__
