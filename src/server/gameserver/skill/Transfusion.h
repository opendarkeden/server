//////////////////////////////////////////////////////////////////////////////
// Filename    : Transfusion.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TRANSFUSION_HANDLER_H__
#define __SKILL_TRANSFUSION_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Transfusion;
//////////////////////////////////////////////////////////////////////////////

class Transfusion : public SkillHandler 
{
public:
	Transfusion() throw() {}
	~Transfusion() throw() {}

public:
    string getSkillHandlerName() const throw() { return "Transfusion"; }
	SkillType_t getSkillType() const throw() { return SKILL_TRANSFUSION; }

	void execute(Vampire* pVampire, ZoneCoord_t X, ZoneCoord_t Y,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Vampire* pVampire, ObjectID_t,  VampireSkillSlot* pVampireSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Transfusion g_Transfusion;

#endif // __SKILL_TRANSFUSION_HANDLER_H__
