//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveTestServerReward.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_GIVE_TEST_SERVER_REWARD_H__
#define __ACTION_GIVE_TEST_SERVER_REWARD_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "LuaTradeEventSlayerItem.h"
#include "LuaTradeEventVampireItem.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionGiveTestServerReward
//////////////////////////////////////////////////////////////////////////////

class ActionGiveTestServerReward : public Action 
{
public:
	ActionGiveTestServerReward();
	~ActionGiveTestServerReward();

	virtual ActionType_t getActionType() const throw() { return ACTION_GIVE_TEST_SERVER_REWARD; }
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
// class ActionGiveTestServerRewardFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionGiveTestServerRewardFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_GIVE_TEST_SERVER_REWARD; }
	virtual string getActionName() const throw() { return "GiveTestServerReward"; }
	virtual Action* createAction() const throw() { return new ActionGiveTestServerReward(); }
};

#endif
