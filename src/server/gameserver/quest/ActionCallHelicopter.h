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
	virtual ActionType_t getActionType() const  { return ACTION_CALL_HELICOPTER; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;
};

//////////////////////////////////////////////////////////////////////////////
// class ActionCallHelicopterFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionCallHelicopterFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const  { return Action::ACTION_CALL_HELICOPTER; }
	virtual string getActionName() const  { return "CallHelicopter"; }
    virtual Action* createAction() const  { return new ActionCallHelicopter(); }
};

#endif
