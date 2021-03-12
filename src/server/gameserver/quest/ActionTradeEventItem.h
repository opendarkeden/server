//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTradeEventItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_TRADE_EVENT_ITEM_H__
#define __ACTION_TRADE_EVENT_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionTradeEventItem
//////////////////////////////////////////////////////////////////////////////

class ActionTradeEventItem : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_TRADE_EVENT_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;
public:
	int getAmount(void) const { return m_GoalAmount; }
	void setAmount(int amount) { m_GoalAmount = amount; }

private:
	int m_GoalAmount; // 받을 축구공의 수
}
;


//////////////////////////////////////////////////////////////////////////////
// class ActionTradeEventItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionTradeEventItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_TRADE_EVENT_ITEM; }
	virtual string getActionName() const  { return "TradeEventItem"; }
	virtual Action* createAction() const  { return new ActionTradeEventItem(); }
};

#endif
