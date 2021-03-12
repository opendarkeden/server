//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTradeGiftBox.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_TRADE_GIFT_BOX_H__
#define __ACTION_TRADE_GIFT_BOX_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "LuaTradeEventSlayerItem.h"
#include "LuaTradeEventVampireItem.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionTradeGiftBox
//////////////////////////////////////////////////////////////////////////////

class ActionTradeGiftBox : public Action 
{
public:
	ActionTradeGiftBox();
	~ActionTradeGiftBox();

	virtual ActionType_t getActionType() const  { return ACTION_TRADE_GIFT_BOX; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

	void						load() ;

private :
	LuaState*					m_pLuaState;
	LuaTradeEventSlayerItem*	m_pLuaSlayerItem;
	LuaTradeEventVampireItem*	m_pLuaVampireItem;

	string						m_CommonFilename;
	string						m_SlayerFilename;
	string						m_VampireFilename;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionTradeGiftBoxFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionTradeGiftBoxFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_TRADE_GIFT_BOX; }
	virtual string getActionName() const  { return "TradeGiftBox"; }
	virtual Action* createAction() const  { return new ActionTradeGiftBox(); }
};

#endif
