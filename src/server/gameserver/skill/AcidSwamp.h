//////////////////////////////////////////////////////////////////////////////
// Filename    : AcidSwamp.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ACID_SWAMP_HANDLER_H__
#define __SKILL_ACID_SWAMP_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class AcidSwamp;
//////////////////////////////////////////////////////////////////////////////

class AcidSwamp : public SkillHandler 
{
public:
	AcidSwamp() throw() {}
	~AcidSwamp() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "AcidSwamp"; }
	SkillType_t getSkillType() const throw() { return SKILL_ACID_SWAMP; }

	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ObjectID_t,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster*, ZoneCoord_t X, ZoneCoord_t Y) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern AcidSwamp g_AcidSwamp;

#endif // __SKILL_ACID_SWAMP_HANDLER_H__
