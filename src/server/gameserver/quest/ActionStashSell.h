//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionStashSell.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_STASH_SELL_H__
#define __ACTION_STASH_SELL_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionStashSell;
//////////////////////////////////////////////////////////////////////////////

class ActionStashSell : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_STASH_SELL; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

};

//////////////////////////////////////////////////////////////////////////////
// class ActionStashSellFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionStashSellFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_STASH_SELL; }
	virtual string getActionName() const throw() { return "StashSell"; }
	virtual Action* createAction() const throw() { return new ActionStashSell(); }

};

#endif
