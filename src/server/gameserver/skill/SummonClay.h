//////////////////////////////////////////////////////////////////////////////
// Filename    : SummonClay.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SUMMON_CLAY_HANDLER_H__
#define __SKILL_SUMMON_CLAY_HANDLER_H__

#include "SkillHandler.h"

#define GROUND_ELEMENTAL_TYPE 698

//////////////////////////////////////////////////////////////////////////////
// class SummonClay;
//////////////////////////////////////////////////////////////////////////////

class SummonClay : public SkillHandler 
{
public:
	SummonClay() throw();
	~SummonClay() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SummonClay"; }
	SkillType_t getSkillType() const throw() { return SKILL_SUMMON_CLAY; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ObjectID_t, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void computeOutput(const SkillInput& input, SkillOutput& output);

private:
	POINT m_ElementalMask[4][25];
	int m_MaskIndex[4];
};

// global variable declaration
extern SummonClay g_SummonClay;

#endif // __SKILL_SUMMON_CLAY_HANDLER_H__
