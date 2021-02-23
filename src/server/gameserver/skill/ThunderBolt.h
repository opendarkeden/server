//////////////////////////////////////////////////////////////////////////////
// Filename    : ThunderBolt.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_THUNDER_BOLT_HANDLER_H__
#define __SKILL_THUNDER_BOLT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ThunderBolt;
//////////////////////////////////////////////////////////////////////////////

class ThunderBolt : public SkillHandler 
{
public:
	ThunderBolt() throw() {}
	~ThunderBolt() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "ThunderBolt"; }
	SkillType_t getSkillType() const throw() { return SKILL_THUNDER_BOLT; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ThunderBolt g_ThunderBolt;

#endif // __SKILL_THUNDER_BOLT_HANDLER_H__
