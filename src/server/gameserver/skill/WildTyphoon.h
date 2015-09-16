//////////////////////////////////////////////////////////////////////////////
// Filename    : WildTyphoon.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_WILD_TYPHOON_HANDLER_H__
#define __SKILL_WILD_TYPHOON_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class WildTyphoon;
//////////////////////////////////////////////////////////////////////////////

class WildTyphoon : public SkillHandler 
{
public:
	WildTyphoon() throw() {}
	~WildTyphoon() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "WildTyphoon"; }
	SkillType_t getSkillType() const throw() { return SKILL_WILD_TYPHOON; }

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ObjectID_t targetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern WildTyphoon g_WildTyphoon;

#endif // __SKILL_WILD_TYPHOON_HANDLER_H__
