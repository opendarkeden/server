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
	virtual ActionType_t getActionType() const throw() { return ACTION_TURN_OFF_FLAG; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

private:
	uint m_Index;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionTurnOffFlagFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionTurnOffFlagFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_TURN_OFF_FLAG; }
	virtual string getActionName() const throw() { return "TurnOffFlag"; }
	virtual Action* createAction() const throw() { return new ActionTurnOffFlag(); }
};

#endif
