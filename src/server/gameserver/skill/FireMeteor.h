//////////////////////////////////////////////////////////////////////////////
// Filename    : FireMeteor.h 
// Written By  : rallser
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_Fire_Meteor_HANDLER_H__
#define __SKILL_Fire_Meteor_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class FireMeteor;
//////////////////////////////////////////////////////////////////////////////

class FireMeteor : public SkillHandler 
{
public:
	FireMeteor() throw() {}
	~FireMeteor() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "FireMeteor"; }
	SkillType_t getSkillType() const throw() { return SKILL_Fire_Meteor; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) ;
	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID) ;

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern FireMeteor g_FireMeteor;

#endif // __SKILL_Fire_Meteor_HANDLER_H__
