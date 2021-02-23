//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionJoinRaceWar.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_JOIN_RACE_WAR_H__
#define __ACTION_JOIN_RACE_WAR_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionJoinRaceWar
//////////////////////////////////////////////////////////////////////////////

class ActionJoinRaceWar : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_JOIN_RACE_WAR; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2) throw(Error);
	virtual string toString() const throw();

private:
};


//////////////////////////////////////////////////////////////////////////////
// class ActionJoinRaceWarFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionJoinRaceWarFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_JOIN_RACE_WAR; }
	virtual string getActionName() const throw() { return "JoinRaceWar"; }
	virtual Action* createAction() const throw() { return new ActionJoinRaceWar(); }
};

#endif
