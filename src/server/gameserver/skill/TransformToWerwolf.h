//////////////////////////////////////////////////////////////////////////////
// Filename    : TransformToWerwolf.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_TRANSFORM_TO_WERWOLF_HANDLER_H__
#define __SKILL_TRANSFORM_TO_WERWOLF_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class TransformToWerwolf;
//////////////////////////////////////////////////////////////////////////////

class TransformToWerwolf: public SkillHandler 
{
public:
	TransformToWerwolf() throw() {}
	~TransformToWerwolf() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "TransformToWerwolf"; }
	SkillType_t getSkillType() const throw() { return SKILL_TRANSFORM_TO_WERWOLF; }

	void execute(Vampire* pVampire, ObjectID_t TargetObjectID, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, VampireSkillSlot* pVampireSkillSlot) throw(Error);
	void execute(Monster* pMonster) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern TransformToWerwolf g_TransformToWerwolf;

#endif // __SKILL_TRANSFORM_TO_WERWOLF_HANDLER_H__
