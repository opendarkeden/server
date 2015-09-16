//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyStorm.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_STORM_HANDLER_H__
#define __SKILL_BLOODY_STORM_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class BloodyStorm;
//////////////////////////////////////////////////////////////////////////////

class BloodyStorm : public SkillHandler 
{
public:
	BloodyStorm() throw() {}
	~BloodyStorm() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BloodyStorm"; }
	SkillType_t getSkillType() const throw() { return SKILL_BLOODY_STORM; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern BloodyStorm g_BloodyStorm;

#endif // __SKILL_BLOODY_STORM_HANDLER_H__
