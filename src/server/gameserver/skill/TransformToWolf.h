//////////////////////////////////////////////////////////////////////////////
// Filename    : TransformToWolf.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TRANSFORM_TO_WOLF_HANDLER_H__
#define __SKILL_TRANSFORM_TO_WOLF_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TransformToWolf;
//////////////////////////////////////////////////////////////////////////////

class TransformToWolf: public SkillHandler 
{
public:
	TransformToWolf() throw() {}
	~TransformToWolf() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "TransformToWolf"; }
	SkillType_t getSkillType() const throw() { return SKILL_TRANSFORM_TO_WOLF; }

	void execute(Vampire* pVampire, ObjectID_t TargetObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, VampireSkillSlot* pVampireSkillSlot) throw(Error);
	void execute(Monster* pMonster) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TransformToWolf g_TransformToWolf;

#endif // __SKILL_TRANSFORM_TO_WOLF_HANDLER_H__
