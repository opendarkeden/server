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
	virtual ActionType_t getActionType() const throw() { return ACTION_SEARCH_MOTORCYCLE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2=NULL) throw(Error);
	virtual string toString() const throw();

protected:
	bool search(Item* pItem, uint& zoneid, uint& x, uint& y) const throw();
};


////////////////////////////////////////////////////////////////////////////////
// class ActionSearchMotorcycleFactory;
////////////////////////////////////////////////////////////////////////////////

class ActionSearchMotorcycleFactory : public ActionFactory 
{
public :
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_SEARCH_MOTORCYCLE; }
	virtual string getActionName() const throw() { return "SearchMotorcycle"; }
	virtual Action* createAction() const throw() { return new ActionSearchMotorcycle(); }
};



#endif
