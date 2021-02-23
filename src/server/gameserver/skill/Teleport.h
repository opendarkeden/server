//////////////////////////////////////////////////////////////////////////////
// Filename    : Teleport.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TELEPORT_HANDLER_H__
#define __SKILL_TELEPORT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Teleport;
//////////////////////////////////////////////////////////////////////////////

class Teleport : public SkillHandler 
{
public:
	Teleport() throw() {}
	~Teleport() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Teleport"; }
	SkillType_t getSkillType() const throw() { return SKILL_TELEPORT; }

	void execute(Ousters* pOusters, ObjectID_t TargetObjectID, OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Ousters* pOusters, ZoneCoord_t X, ZoneCoord_t Y,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Teleport g_Teleport;

#endif // __SKILL_TELEPORT_HANDLER_H__
