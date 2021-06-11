//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionAdvanceEventQuest.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ADVANCE_EVENT_QUEST_H__
#define __ACTION_ADVANCE_EVENT_QUEST_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionAdvanceEventQuest
//////////////////////////////////////////////////////////////////////////////

class ActionAdvanceEventQuest : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_ADVANCE_EVENT_QUEST; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public:
private:
	int		m_QuestLevel;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionAdvanceEventQuestFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionAdvanceEventQuestFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_ADVANCE_EVENT_QUEST; }
	virtual string getActionName() const  { return "AdvanceEventQuest"; }
	virtual Action* createAction() const  { return new ActionAdvanceEventQuest(); }
};
#endif
