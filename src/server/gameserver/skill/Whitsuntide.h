//////////////////////////////////////////////////////////////////////////////
// Filename    : Whitsuntide.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_WHITSUNTIDE_HANDLER_H__
#define __SKILL_WHITSUNTIDE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Whitsuntide;
//////////////////////////////////////////////////////////////////////////////

class Whitsuntide : public SkillHandler 
{
public:
	Whitsuntide() throw() {}
	~Whitsuntide() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Whitsuntide"; }
	SkillType_t getSkillType() const throw() { return SKILL_WHITSUNTIDE; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, ZoneCoord_t X, ZoneCoord_t Y, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Whitsuntide g_Whitsuntide;

#endif // __SKILL_WHITSUNTIDE_HANDLER_H__
