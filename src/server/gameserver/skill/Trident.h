//////////////////////////////////////////////////////////////////////////////
// Filename    : Trident.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TRIDENT_HANDLER_H__
#define __SKILL_TRIDENT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Trident;
//////////////////////////////////////////////////////////////////////////////

class Trident : public SkillHandler 
{
public:
	Trident() throw() {}
	~Trident() throw() {}

public:
    string getSkillHandlerName() const throw() { return "Trident"; }
	SkillType_t getSkillType() const throw() { return SKILL_TRIDENT; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);
	void execute(Monster* pMonster, Creature* pEnemy) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Trident g_Trident;

#endif // __SKILL_TRIDENT_HANDLER_H__
