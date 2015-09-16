//////////////////////////////////////////////////////////////////////////////
// Filename    : ShadowOfStorm.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SHADOW_OF_STORM_HANDLER_H__
#define __SKILL_SHADOW_OF_STORM_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ShadowOfStorm;
//////////////////////////////////////////////////////////////////////////////

class ShadowOfStorm : public SkillHandler 
{
public:
	ShadowOfStorm() throw() {}
	~ShadowOfStorm() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "ShadowOfStorm"; }
	SkillType_t getSkillType() const throw() { return SKILL_SHADOW_OF_STORM; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ShadowOfStorm g_ShadowOfStorm;

#endif // __SKILL_SHADOW_OF_STORM_HANDLER_H__
