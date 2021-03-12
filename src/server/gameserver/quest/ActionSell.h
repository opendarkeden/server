//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSell.h
// Written By  : 
// Description : 
// NPC가 아이템을 플레이어에게 파는 액션이다. 실제로는 거래를
// 시작하게 만드는 액션이며, 하는 일은 플레이어에게 현재 NPC의
// 상점 버전을 패킷으로 보내주는 일 뿐이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SELL_H__
#define __ACTION_SELL_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSell
//////////////////////////////////////////////////////////////////////////////

class ActionSell : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_SELL; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;
};

//////////////////////////////////////////////////////////////////////////////
// class AskFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSellFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_SELL; }
	virtual string getActionName() const  { return "Sell"; }
	virtual Action* createAction() const  { return new ActionSell(); }
};

#endif
