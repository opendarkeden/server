//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveItem.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_GIVE_ITEM_H__
#define __ACTION_GIVE_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionGiveItem
//////////////////////////////////////////////////////////////////////////////

class ActionGiveItem : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_GIVE_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
private:
	Item::ItemClass m_ItemClass;
	ItemType_t		m_ItemType;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionGiveItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionGiveItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_GIVE_ITEM; }
	virtual string getActionName() const throw() { return "GiveItem"; }
	virtual Action* createAction() const throw() { return new ActionGiveItem(); }
};
#endif
