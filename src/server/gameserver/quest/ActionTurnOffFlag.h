//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTurnOffFlag.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_TURN_OFF_FLAG_H__
#define __ACTION_TURN_OFF_FLAG_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionTurnOffFlag
//////////////////////////////////////////////////////////////////////////////

class ActionTurnOffFlag : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_TURN_OFF_FLAG; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

private:
	uint m_Index;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionTurnOffFlagFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionTurnOffFlagFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_TURN_OFF_FLAG; }
	virtual string getActionName() const  { return "TurnOffFlag"; }
	virtual Action* createAction() const  { return new ActionTurnOffFlag(); }
};

#endif
