//////////////////////////////////////////////////////////////////////////////
// Filename    : MeteorStrike.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_METEOR_STRIKE_HANDLER_H__
#define __SKILL_METEOR_STRIKE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MeteorStrike;
//////////////////////////////////////////////////////////////////////////////

class MeteorStrike : public SkillHandler 
{
public:
	MeteorStrike() throw() {}
	~MeteorStrike() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "MeteorStrike"; }
	SkillType_t getSkillType() const throw() { return SKILL_METEOR_STRIKE; }

	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ObjectID_t,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MeteorStrike g_MeteorStrike;

#endif // __SKILL_METEOR_STRIKE_HANDLER_H__
