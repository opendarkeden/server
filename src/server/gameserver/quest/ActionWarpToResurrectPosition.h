// Filename    : ActionWarpToResurrectPosition.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_WARP_TO_RESURRECT_POSITION_H__
#define __ACTION_WARP_TO_RESURRECT_POSITION_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionWarpToResurrectPosition
//////////////////////////////////////////////////////////////////////////////

class ActionWarpToResurrectPosition : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_WARP_TO_RESURRECT_POSITION; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public:

private:
};


//////////////////////////////////////////////////////////////////////////////
// class ActionWarpToResurrectPositionFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionWarpToResurrectPositionFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_WARP_TO_RESURRECT_POSITION; }
	virtual string getActionName() const  { return "WarpToResurrectPosition"; }
	virtual Action* createAction() const  { return new ActionWarpToResurrectPosition(); }
};
#endif
