//////////////////////////////////////////////////////////////////////////////
// Filename    : Liberty.h 
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_LIBERTY_HANDLER_H__
#define __SKILL_LIBERTY_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class Liberty;
//////////////////////////////////////////////////////////////////////////////

class Liberty : public SkillHandler 
{
public:
	Liberty() throw() {}
	~Liberty() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "Liberty"; }
	SkillType_t getSkillType() const throw() { return SKILL_LIBERTY; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID, OustersSkillSlot* pSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern Liberty g_Liberty;

#endif // __SKILL_LIBERTY_HANDLER_H__
