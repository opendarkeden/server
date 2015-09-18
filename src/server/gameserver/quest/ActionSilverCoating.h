//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSilverCoating.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SILVER_COATING_H__
#define __ACTION_SILVER_COATING_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSilverCoating;
//////////////////////////////////////////////////////////////////////////////

class ActionSilverCoating : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_SILVER_COATING; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();
};

//////////////////////////////////////////////////////////////////////////////
// class ActionSilverCoatingFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSilverCoatingFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_SILVER_COATING; }
	virtual string getActionName() const throw() { return "SilverCoating"; }
	virtual Action* createAction() const throw() { return new ActionSilverCoating(); }
};

#endif
