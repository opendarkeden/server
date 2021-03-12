//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSearchMotorcycle.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SEARCH_MOTORCYCLE_H__
#define __ACTION_SEARCH_MOTORCYCLE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSearchMotorcycle;
//////////////////////////////////////////////////////////////////////////////

class ActionSearchMotorcycle : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_SEARCH_MOTORCYCLE; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2=NULL) ;
	virtual string toString() const ;

protected:
	bool search(Item* pItem, uint& zoneid, uint& x, uint& y) const ;
};


////////////////////////////////////////////////////////////////////////////////
// class ActionSearchMotorcycleFactory;
////////////////////////////////////////////////////////////////////////////////

class ActionSearchMotorcycleFactory : public ActionFactory 
{
public :
	virtual ActionType_t getActionType() const  { return Action::ACTION_SEARCH_MOTORCYCLE; }
	virtual string getActionName() const  { return "SearchMotorcycle"; }
	virtual Action* createAction() const  { return new ActionSearchMotorcycle(); }
};



#endif
