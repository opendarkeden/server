//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveNewbieItem.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_GIVE_NEWBIE_ITEM_H__
#define __ACTION_GIVE_NEWBIE_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionGiveNewbieItem
//////////////////////////////////////////////////////////////////////////////

class ActionGiveNewbieItem : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_GIVE_NEWBIE_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public:
	uint getItemClass(void) const  { return m_ItemClass; }
	void setItemClass(uint IClass)  { m_ItemClass = IClass; }

private:
	uint m_ItemClass;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionGiveNewbieItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionGiveNewbieItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_GIVE_NEWBIE_ITEM; }
	virtual string getActionName() const  { return "GiveNewbieItem"; }
	virtual Action* createAction() const  { return new ActionGiveNewbieItem(); }
};

#endif
