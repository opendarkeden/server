//////////////////////////////////////////////////////////////////////////////
// Filename    : TransformToBat.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TRANSFORM_TO_BAT_HANDLER_H__
#define __SKILL_TRANSFORM_TO_BAT_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TransformToBat;
//////////////////////////////////////////////////////////////////////////////

class TransformToBat: public SkillHandler 
{
public:
	TransformToBat() throw() {}
	~TransformToBat() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "TransformToBat"; }
	SkillType_t getSkillType() const throw() { return SKILL_TRANSFORM_TO_BAT; }

	void execute(Vampire* pVampire, ObjectID_t TargetObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, VampireSkillSlot* pVampireSkillSlot) throw(Error);
	void execute(Monster* pMonster) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TransformToBat g_TransformToBat;

#endif // __SKILL_TRANSFORM_TO_BAT_HANDLER_H__
