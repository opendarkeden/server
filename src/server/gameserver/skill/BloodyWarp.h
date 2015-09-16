//////////////////////////////////////////////////////////////////////////////
// Filename    : BloodyWarp.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_BLOODY_WARP_HANDLER_H__
#define __SKILL_BLOODY_WARP_HANDLER_H__

#include "SkillHandler.h"

class VampireSkillSlot;
//////////////////////////////////////////////////////////////////////////////
// class BloodyWarp;
//////////////////////////////////////////////////////////////////////////////

class BloodyWarp : public SkillHandler 
{
public:
	BloodyWarp() throw() {}
	~BloodyWarp() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "BloodyWarp"; }
	SkillType_t getSkillType() const throw() { return SKILL_BLOODY_WARP; }

	void execute(Vampire* pVampire, ObjectID_t ObjectID, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

	POINT getWarpPosition(int myX, int myY, int targetX, int targetY) throw();
};

// global variable declaration
extern BloodyWarp g_BloodyWarp;

#endif // __SKILL_BLOODY_WARP_HANDLER_H__
