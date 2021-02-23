//////////////////////////////////////////////////////////////////////////////
// Filename    : RottenApple.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_ROTTEN_APPLE_HANDLER_H__
#define __SKILL_ROTTEN_APPLE_HANDLER_H__

#include "SkillHandler.h"
#include "Creature.h"
//////////////////////////////////////////////////////////////////////////////
// class RottenApple;
//////////////////////////////////////////////////////////////////////////////

class RottenApple : public SkillHandler 
{
public:
	RottenApple() throw() {}
	~RottenApple() throw() {}
	
public :
    string getSkillHandlerName() const throw() { return "RottenApple"; }
	SkillType_t getSkillType() const throw() { return SKILL_ROTTEN_APPLE; }

	void execute(Slayer* pSlayer, ObjectID_t ObjectID,  SkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern RottenApple g_RottenApple;

#endif // __SKILL_ROTTEN_APPLE_HANDLER_H__
