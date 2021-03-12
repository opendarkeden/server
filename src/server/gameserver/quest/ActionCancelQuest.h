//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionCancelQuest.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_CANCEL_QUEST_H__
#define __ACTION_CANCEL_QUEST_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionCancelQuest
//////////////////////////////////////////////////////////////////////////////

class ActionCancelQuest : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_CANCEL_QUEST; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public:
private:
	ScriptID_t	m_ScriptID;
	ScriptID_t	m_CounterScriptID;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionCancelQuestFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionCancelQuestFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_CANCEL_QUEST; }
	virtual string getActionName() const  { return "CancelQuest"; }
	virtual Action* createAction() const  { return new ActionCancelQuest(); }
};
#endif
