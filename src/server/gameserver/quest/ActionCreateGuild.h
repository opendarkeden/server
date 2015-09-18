////////////////////////////////////////////////////////////////////////////////
// Filename    : ActionCreateGuild.h
// Written By  : excel96
// Description :
// NPC를 통해 클라이언트로 하여금 길드 생성창을 띄우게 한다.
////////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_CREATE_GUILD_H__
#define __ACTION_CREATE_GUILD_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionCreateGuild;
//////////////////////////////////////////////////////////////////////////////

class ActionCreateGuild : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_CREATE_GUILD; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();
};

//////////////////////////////////////////////////////////////////////////////
// class ActionCreateGuildFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionCreateGuildFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const throw() { return Action::ACTION_CREATE_GUILD; }
	virtual string getActionName() const throw() { return "CreateGuild"; }
    virtual Action* createAction() const throw() { return new ActionCreateGuild(); }
};

#endif
