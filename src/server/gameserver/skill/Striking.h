//////////////////////////////////////////////////////////////////////////////
// Filename    : Striking.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_STRIKING_HANDLER_H__
#define __SKILL_STRIKING_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Striking;
//////////////////////////////////////////////////////////////////////////////

class Striking : public SkillHandler 
{
public:
	Striking() throw() {}
	~Striking() throw() {}

public:
    string getSkillHandlerName() const throw() { return "Striking"; }
	SkillType_t getSkillType() const throw() { return SKILL_STRIKING; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Striking g_Striking;

#endif // __SKILL_STRIKING_HANDLER_H__
