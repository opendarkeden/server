//////////////////////////////////////////////////////////////////////////////
// Filename    : SacredStamp.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_Sacred_Stamp_HANDLER_H__
#define __SKILL_Sacred_Stamp_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class SacredStamp;
//////////////////////////////////////////////////////////////////////////////

class SacredStamp : public SkillHandler 
{
public:
	SacredStamp() throw() {}
	~SacredStamp() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SacredStamp"; }

	SkillType_t getSkillType() const throw() { return SKILL_Sacred_Stamp; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) ;
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) ;

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern SacredStamp g_SacredStamp;

#endif // __SKILL_Sacred_Stamp_HANDLER_H__
