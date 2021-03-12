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
	virtual ActionType_t getActionType() const  { return ACTION_SILVER_COATING; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;
};

//////////////////////////////////////////////////////////////////////////////
// class ActionSilverCoatingFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSilverCoatingFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_SILVER_COATING; }
	virtual string getActionName() const  { return "SilverCoating"; }
	virtual Action* createAction() const  { return new ActionSilverCoating(); }
};

#endif
