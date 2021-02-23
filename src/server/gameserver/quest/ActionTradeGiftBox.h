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

	virtual ActionType_t getActionType() const throw() { return ACTION_TRADE_GIFT_BOX; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

	void						load() throw (Error);

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
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_TRADE_GIFT_BOX; }
	virtual string getActionName() const throw() { return "TradeGiftBox"; }
	virtual Action* createAction() const throw() { return new ActionTradeGiftBox(); }
};

#endif
