//////////////////////////////////////////////////////////////////////////////
// Filename    : CutStorm.h 
// Written By  : rallser
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_Cut_Storm_HANDLER_H__
#define __SKILL_Cut_Storm_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class CutStorm;
//////////////////////////////////////////////////////////////////////////////

class CutStorm : public SkillHandler 
{
public:
	CutStorm() throw() {}
	~CutStorm() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "CutStorm"; }
	SkillType_t getSkillType() const throw() { return SKILL_Cut_Storm; }

	void execute(Slayer* pSlayer, ObjectID_t targetObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern CutStorm g_CutStorm;

#endif // __SKILL_SPIT_STREAM_H__
