//////////////////////////////////////////////////////////////////////////////
// Filename    : HitConvert.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_HIT_CONVERT_HANDLER_H__
#define __SKILL_HIT_CONVERT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class HitConvert;
//////////////////////////////////////////////////////////////////////////////

class HitConvert : public SkillHandler 
{
public:
	HitConvert() throw() {}
	~HitConvert() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "HitConvert"; }

	SkillType_t getSkillType() const throw() { return SKILL_HIT_CONVERT; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern HitConvert g_HitConvert;

#endif // __SKILL_HIT_CONVERT_HANDLER_H__
