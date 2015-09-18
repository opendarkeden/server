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
	virtual ActionType_t getActionType() const throw() { return ACTION_SYSTEM_MESSAGE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

private:
	int m_Content;
};

//////////////////////////////////////////////////////////////////////////////
// class ActionSystemMessageFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSystemMessageFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const throw() { return Action::ACTION_SYSTEM_MESSAGE; }
	virtual string getActionName() const throw() { return "SystemMessage"; }
    virtual Action* createAction() const throw() { return new ActionSystemMessage(); }
};

#endif
