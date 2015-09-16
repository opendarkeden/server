//////////////////////////////////////////////////////////////////////////////
// Filename    : SwordRay.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SWORD_RAY_HANDLER_H__
#define __SKILL_SWORD_RAY_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SwordRay;
//////////////////////////////////////////////////////////////////////////////

class SwordRay : public SkillHandler 
{
public:
	SwordRay() throw() {}
	~SwordRay() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SwordRay"; }
	SkillType_t getSkillType() const throw() { return SKILL_SWORD_RAY; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SwordRay g_SwordRay;

#endif // __SKILL_SWORD_RAY_HANDLER_H__
