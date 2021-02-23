//////////////////////////////////////////////////////////////////////////////
// Filename    : CreateMine.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CREATE_MINE_HANDLER_H__
#define __SKILL_CREATE_MINE_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class CreateMine;
//////////////////////////////////////////////////////////////////////////////

class CreateMine : public SkillHandler 
{
public:
	CreateMine() throw() {}
	~CreateMine() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "CreateMine"; }
	SkillType_t getSkillType() const throw() { return SKILL_CREATE_MINE; }

	void execute(Slayer* pSlayer, ObjectID_t, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, SkillSlot* pSkillSlot) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	bool canMake(ItemType_t waterType, int DomainLevel, int SkillLevel) throw();
};

// global variable declaration
extern CreateMine g_CreateMine;

#endif // __SKILL_CREATE_MINE_HANDLER_H__
