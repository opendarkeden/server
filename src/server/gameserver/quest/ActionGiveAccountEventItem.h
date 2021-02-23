//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveAccountEventItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_GIVE_ACCOUNT_EVENT_ITEM_H__
#define __ACTION_GIVE_ACCOUNT_EVENT_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "LuaTradeEventSlayerItem.h"
#include "LuaTradeEventVampireItem.h"
#include "SpecialEventFlag.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionGiveAccountEventItem
//////////////////////////////////////////////////////////////////////////////

class ActionGiveAccountEventItem : public Action 
{
public:
	ActionGiveAccountEventItem();
	~ActionGiveAccountEventItem();

	virtual ActionType_t getActionType() const throw() { return ACTION_GIVE_ACCOUNT_EVENT_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

	void						load() throw (Error);

private :
	SpecialEventFlag			m_SpecialEventFlag;

	LuaState*					m_pLuaState;
	LuaTradeEventSlayerItem*	m_pLuaSlayerItem;
	LuaTradeEventVampireItem*	m_pLuaVampireItem;

	string						m_CommonFilename;
	string						m_SlayerFilename;
	string						m_VampireFilename;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionGiveAccountEventItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionGiveAccountEventItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_GIVE_ACCOUNT_EVENT_ITEM; }
	virtual string getActionName() const throw() { return "GiveAccountEventItem"; }
	virtual Action* createAction() const throw() { return new ActionGiveAccountEventItem(); }
};

#endif
