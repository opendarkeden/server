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
	virtual ActionType_t getActionType() const  { return ACTION_TRADE_GQUEST_EVENT_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionTradeGQuestEventItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionTradeGQuestEventItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_TRADE_GQUEST_EVENT_ITEM; }
	virtual string getActionName() const  { return "TradeGQuestEventItem"; }
	virtual Action* createAction() const  { return new ActionTradeGQuestEventItem(); }
};

#endif
