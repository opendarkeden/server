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

	virtual ActionType_t getActionType() const  { return ACTION_GIVE_COMMON_EVENT_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

private :
	string m_Type;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionGiveCommonEventItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionGiveCommonEventItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_GIVE_COMMON_EVENT_ITEM; }
	virtual string getActionName() const  { return "GiveCommonEventItem"; }
	virtual Action* createAction() const  { return new ActionGiveCommonEventItem(); }
};

#endif
