//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRepair.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_REPAIR_H__
#define __ACTION_REPAIR_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionRepair;
//////////////////////////////////////////////////////////////////////////////

class ActionRepair : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_REPAIR; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();
};


//////////////////////////////////////////////////////////////////////////////
// class ActionRepairFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionRepairFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_REPAIR; }
	virtual string getActionName() const throw() { return "Repair"; }
	virtual Action* createAction() const throw() { return new ActionRepair(); }
};

#endif
