//////////////////////////////////////////////////////////////////////////////
// Filename    : CurePoison.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CURE_POISON_HANDLER_H__
#define __SKILL_CURE_POISON_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class CurePoison;
//////////////////////////////////////////////////////////////////////////////

class CurePoison: public SkillHandler 
{
public:
	CurePoison() throw() {}
	~CurePoison() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "CurePoison"; }
	SkillType_t getSkillType() const throw() { return SKILL_CURE_POISON; }

	void execute(Slayer* pSlayer, ObjectID_t TargetObjectID, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Slayer* pSlayer, SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern CurePoison g_CurePoison;

#endif // __SKILL_CURE_POISON_HANDLER_H__
