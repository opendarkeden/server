//////////////////////////////////////////////////////////////////////////////
// Filename    : SummonGroundElemental.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SUMMON_GROUND_ELEMENTAL_HANDLER_H__
#define __SKILL_SUMMON_GROUND_ELEMENTAL_HANDLER_H__

#include "SkillHandler.h"

#define GROUND_ELEMENTAL_TYPE 698

//////////////////////////////////////////////////////////////////////////////
// class SummonGroundElemental;
//////////////////////////////////////////////////////////////////////////////

class SummonGroundElemental : public SkillHandler 
{
public:
	SummonGroundElemental() throw();
	~SummonGroundElemental() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SummonGroundElemental"; }
	SkillType_t getSkillType() const throw() { return SKILL_SUMMON_GROUND_ELEMENTAL; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ObjectID_t, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void computeOutput(const SkillInput& input, SkillOutput& output);

private:
	POINT m_ElementalMask[4][25];
	int m_MaskIndex[4];
};

// global variable declaration
extern SummonGroundElemental g_SummonGroundElemental;

#endif // __SKILL_SUMMON_GROUND_ELEMENTAL_HANDLER_H__
