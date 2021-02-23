//////////////////////////////////////////////////////////////////////////////
// Filename    : SummonMiga.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SUMMON_MIGA_HANDLER_H__
#define __SKILL_SUMMON_MIGA_HANDLER_H__

#include "SkillHandler.h"

#define MIGA_TYPE 768

//////////////////////////////////////////////////////////////////////////////
// class SummonMiga;
//////////////////////////////////////////////////////////////////////////////

class SummonMiga : public SkillHandler 
{
public:
	SummonMiga() throw();
	~SummonMiga() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "SummonMiga"; }
	SkillType_t getSkillType() const throw() { return SKILL_SUMMON_MIGA; }

	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ObjectID_t, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void computeOutput(const SkillInput& input, SkillOutput& output);

private:
	POINT m_ElementalMask[4][25];
	int m_MaskIndex[4];
};

// global variable declaration
extern SummonMiga g_SummonMiga;

#endif // __SKILL_SUMMON_MIGA_HANDLER_H__
