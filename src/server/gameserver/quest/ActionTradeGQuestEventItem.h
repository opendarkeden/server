//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTradeGQuestEventItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_TRADE_GQUEST_EVENT_ITEM_H__
#define __ACTION_TRADE_GQUEST_EVENT_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionTradeGQuestEventItem
//////////////////////////////////////////////////////////////////////////////

class ActionTradeGQuestEventItem : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_TRADE_GQUEST_EVENT_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();
};


//////////////////////////////////////////////////////////////////////////////
// class ActionTradeGQuestEventItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionTradeGQuestEventItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_TRADE_GQUEST_EVENT_ITEM; }
	virtual string getActionName() const throw() { return "TradeGQuestEventItem"; }
	virtual Action* createAction() const throw() { return new ActionTradeGQuestEventItem(); }
};

#endif
