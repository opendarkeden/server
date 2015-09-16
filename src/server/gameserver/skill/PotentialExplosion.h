//////////////////////////////////////////////////////////////////////////////
// Filename    : PotentialExplosion.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_POTENTIAL_EXPLOSION_HANDLER_H__
#define __SKILL_POTENTIAL_EXPLOSION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class PotentialExplosion;
//////////////////////////////////////////////////////////////////////////////

class PotentialExplosion : public SkillHandler 
{
public:
	PotentialExplosion() throw() {}
	~PotentialExplosion() throw() {}

public:
    string getSkillHandlerName() const throw() { return "PotentialExplosion"; }
	SkillType_t getSkillType() const throw() { return SKILL_POTENTIAL_EXPLOSION; }

	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern PotentialExplosion g_PotentialExplosion;

#endif // __SKILL_POTENTIAL_EXPLOSION_HANDLER_H__
