//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionBuy.h
// Written By  : excel96
// Description : 
// NPC가 플레이어로부터 아이템을 사들이는 액션이다. Sell 액션과 마찬가지로 
// 특별히 하는 일은 없고, 단지 플레이어에게 현재 상점의 버전을 패킷으로 
// 보내주는 역할을 한다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_BUY_H__
#define __ACTION_BUY_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionBuy
//////////////////////////////////////////////////////////////////////////////

class ActionBuy : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_BUY; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;
};


//////////////////////////////////////////////////////////////////////////////
// class AskFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionBuyFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_BUY; }
	virtual string getActionName() const  { return "Buy"; }
	virtual Action* createAction() const  { return new ActionBuy(); }
};


#endif
