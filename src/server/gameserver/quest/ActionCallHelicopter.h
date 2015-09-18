//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionCallHelicopter.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_CALL_HELICOPTER_H__
#define __ACTION_CALL_HELICOPTER_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionCallHelicopter;
//////////////////////////////////////////////////////////////////////////////

class ActionCallHelicopter : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_CALL_HELICOPTER; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();
};

//////////////////////////////////////////////////////////////////////////////
// class ActionCallHelicopterFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionCallHelicopterFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const throw() { return Action::ACTION_CALL_HELICOPTER; }
	virtual string getActionName() const throw() { return "CallHelicopter"; }
    virtual Action* createAction() const throw() { return new ActionCallHelicopter(); }
};

#endif
