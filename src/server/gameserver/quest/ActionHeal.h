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
	virtual ActionType_t getActionType() const  { return ACTION_HEAL; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

};


//////////////////////////////////////////////////////////////////////////////
// class ActionHealFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionHealFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_HEAL; }
	virtual string getActionName() const  { return "Heal"; }
	virtual Action* createAction() const  { return new ActionHeal(); }

};


#endif
