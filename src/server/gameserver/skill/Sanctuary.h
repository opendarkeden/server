//////////////////////////////////////////////////////////////////////////////
// Filename    : Sanctuary.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_SANCTUARY_HANDLER_H__
#define __SKILL_SANCTUARY_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Sanctuary;
//////////////////////////////////////////////////////////////////////////////

class Sanctuary : public SkillHandler 
{
public:
	Sanctuary() throw() {}
	~Sanctuary() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Sanctuary"; }
	SkillType_t getSkillType() const throw() { return SKILL_SANCTUARY; }

	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ObjectID_t, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
 	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Sanctuary g_Sanctuary;

#endif // __SKILL_SANCTUARY_HANDLER_H__
