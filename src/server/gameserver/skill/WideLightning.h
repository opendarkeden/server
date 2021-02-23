//////////////////////////////////////////////////////////////////////////////
// Filename    : WideLightning.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_WIDE_LIGHTNING_HANDLER_H__
#define __SKILL_WIDE_LIGHTNING_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class WideLightning;
//////////////////////////////////////////////////////////////////////////////

class WideLightning : public SkillHandler 
{
public:
	WideLightning() throw() {}
	~WideLightning() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "WideLightning"; }
	SkillType_t getSkillType() const throw() { return SKILL_WIDE_LIGHTNING; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern WideLightning g_WideLightning;

#endif // __SKILL_WIDE_LIGHTNING_HANDLER_H__
