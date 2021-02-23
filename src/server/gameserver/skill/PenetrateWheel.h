//////////////////////////////////////////////////////////////////////////////
// Filename    : PenetrateWheel.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_Penetrate_Wheel_HANDLER_H__
#define __SKILL_Penetrate_Wheel_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class PenetrateWheel;
//////////////////////////////////////////////////////////////////////////////

class PenetrateWheel : public SkillHandler 
{
public:
	PenetrateWheel() throw() {}
	~PenetrateWheel() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "PenetrateWheel"; }
	SkillType_t getSkillType() const throw() { return SKILL_Penetrate_Wheel; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ObjectID_t, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern PenetrateWheel g_PenetrateWheel;

#endif // __SKILL_Penetrate_Wheel_HANDLER_H__
