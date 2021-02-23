//////////////////////////////////////////////////////////////////////////////
// Filename    : BigRockfall.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_Big_Rockfall_HANDLER_H__
#define __SKILL_Big_Rockfall_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BigRockfall;
//////////////////////////////////////////////////////////////////////////////

class BigRockfall : public SkillHandler 
{
public:
	BigRockfall() throw() {}
	~BigRockfall() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BigRockfall"; }
	SkillType_t getSkillType() const throw() { return SKILL_Big_Rockfall; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BigRockfall g_BigRockfall;

#endif // __SKILL_Big_Rockfall_HANDLER_H__
