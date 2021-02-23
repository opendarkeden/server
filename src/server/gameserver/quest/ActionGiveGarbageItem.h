//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveGarbageEventItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_GIVE_GARBAGE_EVENT_ITEM_H__
#define __ACTION_GIVE_GARBAGE_EVENT_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionGiveGarbageEventItem
//////////////////////////////////////////////////////////////////////////////

class ActionGiveGarbageEventItem : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_GIVE_GARBAGE_EVENT_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();
};


//////////////////////////////////////////////////////////////////////////////
// class ActionGiveGarbageEventItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionGiveGarbageEventItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_GIVE_GARBAGE_EVENT_ITEM; }
	virtual string getActionName() const throw() { return "GiveGarbageEventItem"; }
	virtual Action* createAction() const throw() { return new ActionGiveGarbageEventItem(); }
};

#endif
