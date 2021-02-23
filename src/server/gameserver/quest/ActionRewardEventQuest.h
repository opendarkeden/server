//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRewardEventQuest.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_REWARD_EVENT_QUEST_H__
#define __ACTION_REWARD_EVENT_QUEST_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionRewardEventQuest
//////////////////////////////////////////////////////////////////////////////

class ActionRewardEventQuest : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_REWARD_EVENT_QUEST; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	ScriptID_t getScriptID( int index ) const throw() { return m_ScriptID[index]; }
	void setScriptID( int index, ScriptID_t scriptID ) throw() { m_ScriptID[index] = scriptID; }

private:
	ScriptID_t m_ScriptID[5];   // 말할 대사 아이디
	ScriptID_t m_CounterScriptID;	// 퀘스트가 완료되지 않았을 때
	ScriptID_t m_CancelScriptID;	// 이전 단계 퀘스트의 보상을 받을 때
};


//////////////////////////////////////////////////////////////////////////////
// class ActionRewardEventQuestFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionRewardEventQuestFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_REWARD_EVENT_QUEST; }
	virtual string getActionName() const throw() { return "RewardEventQuest"; }
	virtual Action* createAction() const throw() { return new ActionRewardEventQuest(); }
};
#endif
