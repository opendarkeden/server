//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveSpecialEventItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_GIVE_SPECIAL_EVENT_ITEM_H__
#define __ACTION_GIVE_SPECIAL_EVENT_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionGiveSpecialEventItem
//////////////////////////////////////////////////////////////////////////////

class ActionGiveSpecialEventItem : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_GIVE_SPECIAL_EVENT_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionGiveSpecialEventItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionGiveSpecialEventItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_GIVE_SPECIAL_EVENT_ITEM; }
	virtual string getActionName() const  { return "GiveSpecialEventItem"; }
	virtual Action* createAction() const  { return new ActionGiveSpecialEventItem(); }
};

#endif
