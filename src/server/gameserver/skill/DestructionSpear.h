//////////////////////////////////////////////////////////////////////////////
// Filename    : DestructionSpear.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_DESTRUCTION_SPEAR_HANDLER_H__
#define __SKILL_DESTRUCTION_SPEAR_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class DestructionSpear;
//////////////////////////////////////////////////////////////////////////////

class DestructionSpear: public SkillHandler 
{
public:
	DestructionSpear() throw() {}
	~DestructionSpear() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "DestructionSpear"; }

	SkillType_t getSkillType() const throw() { return SKILL_DESTRUCTION_SPEAR; }

	void execute(Ousters* pOusters, ObjectID_t targetObject, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern DestructionSpear g_DestructionSpear;

#endif // __SKILL_DESTRUCTION_SPEAR_HANDLER_H__
