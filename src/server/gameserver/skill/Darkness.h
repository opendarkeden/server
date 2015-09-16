//////////////////////////////////////////////////////////////////////////////
// Filename    : Darkness.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DARKNESS_HANDLER_H__
#define __SKILL_DARKNESS_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Darkness;
//////////////////////////////////////////////////////////////////////////////

class Darkness : public SkillHandler 
{
public:
	Darkness() throw() {}
	~Darkness() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Darkness"; }
	SkillType_t getSkillType() const throw() { return SKILL_DARKNESS; }

	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ObjectID_t, VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);
	void execute(Monster*, ZoneCoord_t x, ZoneCoord_t y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Darkness g_Darkness;

#endif // __SKILL_DARKNESS_HANDLER_H__
