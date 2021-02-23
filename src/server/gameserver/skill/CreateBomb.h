//////////////////////////////////////////////////////////////////////////////
// Filename    : CreateBomb.h 
// Written By  : elca@ewestsoft.com
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __SKILL_CREATE_BOMB_HANDLER_H__
#define __SKILL_CREATE_BOMB_HANDLER_H__

#include "SkillHandler.h"

//////////////////////////////////////////////////////////////////////////////
// class CreateBomb;
//////////////////////////////////////////////////////////////////////////////

class CreateBomb : public SkillHandler 
{
public:
	CreateBomb() throw() {}
	~CreateBomb() throw() {}
	
public:
    string getSkillHandlerName() const throw() { return "CreateBomb"; }
	SkillType_t getSkillType() const throw() { return SKILL_CREATE_BOMB; }

	void execute(Slayer* pSlayer, ObjectID_t, CoordInven_t X, CoordInven_t Y, CoordInven_t TargetX, CoordInven_t TargetY, SkillSlot* pSkillSlot) throw(Error);

	void computeOutput(const SkillInput& input, SkillOutput& output);

protected:
	bool canMake(ItemType_t waterType, int DomainLevel, int SkillLevel) throw();
};

// global variable declaration
extern CreateBomb g_CreateBomb;

#endif // __SKILL_CREATE_BOMB_HANDLER_H__
