//////////////////////////////////////////////////////////////////////////////
// Filename    : MagnumSpear.h 
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_MAGNUM_SPEAR_HANDLER_H__
#define __SKILL_MAGNUM_SPEAR_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class MagnumSpear;
//////////////////////////////////////////////////////////////////////////////

class MagnumSpear : public SkillHandler 
{
public:
	MagnumSpear() throw() {}
	~MagnumSpear() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "MagnumSpear"; }
	SkillType_t getSkillType() const throw() { return SKILL_MAGNUM_SPEAR; }

	void execute(Ousters* pOusters, ObjectID_t ObjectID,  OustersSkillSlot* pOustersSkillSlot, CEffectID_t CEffectID) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);
};

// global variable declaration
extern MagnumSpear g_MagnumSpear;

#endif // __SKILL_MAGNUM_SPEAR_HANDLER_H__
