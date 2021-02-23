//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveCommonEventItem.h
// Written By  : bezz
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_GIVE_COMMON_EVENT_ITEM_H__
#define __ACTION_GIVE_COMMON_EVENT_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionGiveCommonEventItem
//////////////////////////////////////////////////////////////////////////////

class ActionGiveCommonEventItem : public Action 
{
public:
	ActionGiveCommonEventItem();
	~ActionGiveCommonEventItem();

	virtual ActionType_t getActionType() const throw() { return ACTION_GIVE_COMMON_EVENT_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

private :
	string m_Type;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionGiveCommonEventItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionGiveCommonEventItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_GIVE_COMMON_EVENT_ITEM; }
	virtual string getActionName() const throw() { return "GiveCommonEventItem"; }
	virtual Action* createAction() const throw() { return new ActionGiveCommonEventItem(); }
};

#endif
