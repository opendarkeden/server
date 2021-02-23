//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionInitPartnerWaitingManager.h
// Description : NPC가 초기화될때 특정 NPC는 커플 등록 매니저를 초기화시켜줘야 된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_INIT_PARTNER_WAITING_MANAGER_H__
#define __ACTION_INIT_PARTNER_WAITING_MANAGER_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionInitPartnerWaitingManager
//////////////////////////////////////////////////////////////////////////////

class ActionInitPartnerWaitingManager : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_INIT_PARTNER_WAITING_MANAGER; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:

private:
};


//////////////////////////////////////////////////////////////////////////////
// class ActionInitPartnerWaitingManagerFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionInitPartnerWaitingManagerFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_INIT_PARTNER_WAITING_MANAGER; }
	virtual string getActionName() const throw() { return "InitPartnerWaitingManager"; }
	virtual Action* createAction() const throw() { return new ActionInitPartnerWaitingManager(); }
};
#endif
