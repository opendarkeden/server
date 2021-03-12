//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSystemMessage.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SYSTEM_MESSAGE_H__
#define __ACTION_SYSTEM_MESSAGE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSystemMessage;
//////////////////////////////////////////////////////////////////////////////

class ActionSystemMessage : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_SYSTEM_MESSAGE; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

private:
	int m_Content;
};

//////////////////////////////////////////////////////////////////////////////
// class ActionSystemMessageFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSystemMessageFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const  { return Action::ACTION_SYSTEM_MESSAGE; }
	virtual string getActionName() const  { return "SystemMessage"; }
    virtual Action* createAction() const  { return new ActionSystemMessage(); }
};

#endif
