//////////////////////////////////////////////////////////////////////////////
// Filename    : SkyFire.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_Sky_Fire_HANDLER_H__
#define __SKILL_Sky_Fire_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SkyFire;
//////////////////////////////////////////////////////////////////////////////

class SkyFire : public SkillHandler 
{
public:
	SkyFire() throw() {}
	~SkyFire() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SkyFire"; }
	SkillType_t getSkillType() const throw() { return SKILL_Sky_Fire; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SkyFire g_SkyFire;

#endif // __SKILL_Sky_Fire_HANDLER_H__
