//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSystemMessagePerRace.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SYSTEM_MESSAGE_PER_RACE_H__
#define __ACTION_SYSTEM_MESSAGE_PER_RACE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSystemMessagePerRace;
//////////////////////////////////////////////////////////////////////////////

class ActionSystemMessagePerRace : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_SYSTEM_MESSAGE_PER_RACE; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

};

//////////////////////////////////////////////////////////////////////////////
// class ActionSystemMessagePerRaceFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSystemMessagePerRaceFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const  { return Action::ACTION_SYSTEM_MESSAGE_PER_RACE; }
	virtual string getActionName() const  { return "SystemMessagePerRace"; }
    virtual Action* createAction() const  { return new ActionSystemMessagePerRace(); }
};

#endif
