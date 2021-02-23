//////////////////////////////////////////////////////////////////////////////
// Filename    : EnergyDrop.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ENERGY_DROP_HANDLER_H__
#define __SKILL_ENERGY_DROP_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class EnergyDrop;
//////////////////////////////////////////////////////////////////////////////

class EnergyDrop : public SkillHandler 
{
public:
	EnergyDrop() throw() {}
	~EnergyDrop() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "EnergyDrop"; }
	SkillType_t getSkillType() const throw() { return SKILL_ENERGY_DROP; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void execute(Monster* pMonster, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern EnergyDrop g_EnergyDrop;

#endif // __SKILL_ENERGY_DROP_HANDLER_H__
