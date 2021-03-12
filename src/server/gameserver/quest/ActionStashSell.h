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
	virtual ActionType_t getActionType() const  { return ACTION_STASH_SELL; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

};

//////////////////////////////////////////////////////////////////////////////
// class ActionStashSellFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionStashSellFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_STASH_SELL; }
	virtual string getActionName() const  { return "StashSell"; }
	virtual Action* createAction() const  { return new ActionStashSell(); }

};

#endif
