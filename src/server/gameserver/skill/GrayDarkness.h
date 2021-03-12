
//////////////////////////////////////////////////////////////////////////////
// Filename    : GrayDarkness.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_GRAY_DARKNESS_HANDLER_H__
#define __SKILL_GRAY_DARKNESS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class GrayDarkness;
//////////////////////////////////////////////////////////////////////////////

class GrayDarkness : public SkillHandler 
{
public:
	GrayDarkness() throw() {}
	~GrayDarkness() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "GrayDarkness"; }
	SkillType_t getSkillType() const throw() { return SKILL_GRAY_DARKNESS; }

	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) ;
	void execute(Vampire* pVampire, ObjectID_t, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) ;
	void execute(Monster* pMonster, Creature* pEnemy) ;
	void execute(Monster*, ZoneCoord_t x, ZoneCoord_t y) ;

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern GrayDarkness g_GrayDarkness;

#endif // __SKILL_GRAY_DARKNESS_HANDLER_H__
