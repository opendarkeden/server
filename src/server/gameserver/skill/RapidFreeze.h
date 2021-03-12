//////////////////////////////////////////////////////////////////////////////
// Filename    : RapidFreeze.h 
// Written By  : rallser
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_Rapid_Freeze_HANDLER_H__
#define __SKILL_Rapid_Freeze_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class RapidFreeze;
//////////////////////////////////////////////////////////////////////////////

class RapidFreeze : public SkillHandler 
{
public:
	RapidFreeze() throw() {}
	~RapidFreeze() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "RapidFreeze"; }
	SkillType_t getSkillType() const throw() { return SKILL_Rapid_Freeze; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) ;
	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) ;

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern RapidFreeze g_RapidFreeze;

#endif // __SKILL_Rapid_Freeze_HANDLER_H__
