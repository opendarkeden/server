//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTradeLairItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_TRADE_LAIR_ITEM_H__
#define __ACTION_TRADE_LAIR_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionTradeLairItem
//////////////////////////////////////////////////////////////////////////////

const int BATORI_TYPE = 432;
const int TEPEZ_TYPE  = 433;
const int GDR_TYPE  = 717;

class ActionTradeLairItem : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_TRADE_LAIR_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;
public:
	int getType(void) const { return m_Type; }
	void setType(int type) { m_Type = type; }

private:
	ItemType_t m_Type; // 받을 축구공의 수
}
;


//////////////////////////////////////////////////////////////////////////////
// class ActionTradeLairItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionTradeLairItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_TRADE_LAIR_ITEM; }
	virtual string getActionName() const  { return "TradeLairItem"; }
	virtual Action* createAction() const  { return new ActionTradeLairItem(); }
};

#endif
