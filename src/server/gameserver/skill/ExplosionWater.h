//////////////////////////////////////////////////////////////////////////////
// Filename    : ExplosionWater.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_EXPLOSION_WATER_HANDLER_H__
#define __SKILL_EXPLOSION_WATER_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class ExplosionWater;
//////////////////////////////////////////////////////////////////////////////

class ExplosionWater : public SkillHandler 
{
public:
	ExplosionWater() throw() {}
	~ExplosionWater() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "ExplosionWater"; }
	SkillType_t getSkillType() const throw() { return SKILL_EXPLOSION_WATER; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern ExplosionWater g_ExplosionWater;

#endif // __SKILL_EXPLOSION_WATER_HANDLER_H__
