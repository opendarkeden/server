/////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __ACTION_GIVE_CHILDREN_EVENT_ITEM_H__
#define __ACTION_GIVE_CHILDREN_EVENT_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionGiveChildrenEvent
//////////////////////////////////////////////////////////////////////////////

class ActionGiveChildrenEvent : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_GIVE_CHILDREN_EVENT_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();
};


//////////////////////////////////////////////////////////////////////////////
// class ActionGiveChildrenEventFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionGiveChildrenEventFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_GIVE_CHILDREN_EVENT_ITEM; }
	virtual string getActionName() const throw() { return "GiveChildrenEventItem"; }
	virtual Action* createAction() const throw() { return new ActionGiveChildrenEvent(); }
};

#endif
