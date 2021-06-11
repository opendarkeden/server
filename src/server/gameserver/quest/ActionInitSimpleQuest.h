//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionInitSimpleQuest.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_INIT_SIMPLE_QUEST_H__
#define __ACTION_INIT_SIMPLE_QUEST_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionInitSimpleQuest
//////////////////////////////////////////////////////////////////////////////

class ActionInitSimpleQuest : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_INIT_SIMPLE_QUEST; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public:
private:
	Race_t		m_Race;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionInitSimpleQuestFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionInitSimpleQuestFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_INIT_SIMPLE_QUEST; }
	virtual string getActionName() const  { return "InitSimpleQuest"; }
	virtual Action* createAction() const  { return new ActionInitSimpleQuest(); }
};
#endif
