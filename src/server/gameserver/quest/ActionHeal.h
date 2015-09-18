//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionHeal.h
// Written By  : excel96
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_HEAL_H__
#define __ACTION_HEAL_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionHeal
//////////////////////////////////////////////////////////////////////////////

class ActionHeal : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_HEAL; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

};


//////////////////////////////////////////////////////////////////////////////
// class ActionHealFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionHealFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_HEAL; }
	virtual string getActionName() const throw() { return "Heal"; }
	virtual Action* createAction() const throw() { return new ActionHeal(); }

};


#endif
