//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionStashOpen.h
// Written By  : 
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_STASH_OPEN_H__
#define __ACTION_STASH_OPEN_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionStashOpen;
//////////////////////////////////////////////////////////////////////////////

class ActionStashOpen : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_STASH_OPEN; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();
};


//////////////////////////////////////////////////////////////////////////////
// class ActionStashOpenFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionStashOpenFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_STASH_OPEN; }
	virtual string getActionName() const throw() { return "StashOpen"; }
	virtual Action* createAction() const throw() { return new ActionStashOpen(); }
};

#endif
