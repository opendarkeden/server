//////////////////////////////////////////////////////////////////////////////
// Filename    : BombingStar.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BOMBING_STAR_HANDLER_H__
#define __SKILL_BOMBING_STAR_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BombingStar;
//////////////////////////////////////////////////////////////////////////////

class BombingStar : public SkillHandler 
{
public:
	BombingStar() throw() {}
	~BombingStar() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BombingStar"; }

	SkillType_t getSkillType() const throw() { return SKILL_BOMBING_STAR; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BombingStar g_BombingStar;

#endif // __SKILL_BOMBING_STAR_HANDLER_H__
