//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyBreaker.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_BREAKER_HANDLER_H__
#define __SKILL_BLOODY_BREAKER_HANDLER_H__

#include "SkillHandler.h"

class VampireSkillSlot;
//////////////////////////////////////////////////////////////////////////////
// class BloodyBreaker;
//////////////////////////////////////////////////////////////////////////////

class BloodyBreaker : public SkillHandler 
{
public:
	BloodyBreaker() throw();
	~BloodyBreaker() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BloodyBreaker"; }
	SkillType_t getSkillType() const throw() { return SKILL_BLOODY_BREAKER; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

private:
	POINT m_pBloodyBreakerMask[8][22];
};

// global variable declaration
extern BloodyBreaker g_BloodyBreaker;

#endif // __SKILL_BLOODY_BREAKER_HANDLER_H__
