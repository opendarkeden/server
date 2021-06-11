////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionDownSkill.h
// Written By  : excel96
// Description :
// NPC를 통해 클라이언트로 하여금 길드 생성창을 띄우게 한다.
////////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_DOWN_SKILL_H__
#define __ACTION_DOWN_SKILL_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionDownSkill;
//////////////////////////////////////////////////////////////////////////////

class ActionDownSkill : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_DOWN_SKILL; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;
};

//////////////////////////////////////////////////////////////////////////////
// class ActionDownSkillFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionDownSkillFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const  { return Action::ACTION_DOWN_SKILL; }
	virtual string getActionName() const  { return "DownSkill"; }
    virtual Action* createAction() const  { return new ActionDownSkill(); }
};

#endif
