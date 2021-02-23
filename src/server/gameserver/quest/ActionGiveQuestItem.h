//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionGiveQuestItem.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_GIVE_QUEST_ITEM_H__
#define __ACTION_GIVE_QUEST_ITEM_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionGiveQuestItem
//////////////////////////////////////////////////////////////////////////////

class ActionGiveQuestItem : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_GIVE_QUEST_ITEM; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:

private:
	ScriptID_t	m_CounterScriptID;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionGiveQuestItemFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionGiveQuestItemFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_GIVE_QUEST_ITEM; }
	virtual string getActionName() const throw() { return "GiveQuestItem"; }
	virtual Action* createAction() const throw() { return new ActionGiveQuestItem(); }
};
#endif
