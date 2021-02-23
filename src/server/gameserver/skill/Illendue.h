//////////////////////////////////////////////////////////////////////////////
// Filename    : Illendue.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ILLENDUE_HANDLER_H__
#define __SKILL_ILLENDUE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Illendue;
//////////////////////////////////////////////////////////////////////////////

class Illendue : public SkillHandler 
{
public:
	Illendue() throw() {}
	~Illendue() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Illendue"; }

	SkillType_t getSkillType() const throw() { return SKILL_ILLENDUE; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Illendue g_Illendue;

#endif // __SKILL_ILLENDUE_HANDLER_H__
