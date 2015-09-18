//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionShowTaxBalance.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SHOW_TAX_BALANCE_H__
#define __ACTION_SHOW_TAX_BALANCE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionShowTaxBalance
//////////////////////////////////////////////////////////////////////////////

class ActionShowTaxBalance : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_SHOW_TAX_BALANCE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();
};


//////////////////////////////////////////////////////////////////////////////
// class ActionShowTaxBalanceFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionShowTaxBalanceFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_SHOW_TAX_BALANCE; }
	virtual string getActionName() const throw() { return "ShowTaxBalance"; }
	virtual Action* createAction() const throw() { return new ActionShowTaxBalance(); }
};
#endif
