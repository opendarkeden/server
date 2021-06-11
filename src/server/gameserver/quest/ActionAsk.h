//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionAsk.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ASK_H__
#define __ACTION_ASK_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionAsk
//////////////////////////////////////////////////////////////////////////////

class ActionAsk : public Action 
{
public:
	virtual ActionType_t getActionType() const  { return ACTION_ASK; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public:
	ScriptID_t getScriptID() const  { return m_ScriptID; }
	void setScriptID(ScriptID_t scriptID)  { m_ScriptID = scriptID; }

private:
	ScriptID_t m_ScriptID;   // 말할 대사 아이디
};


//////////////////////////////////////////////////////////////////////////////
// class ActionAskFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionAskFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_ASK; }
	virtual string getActionName() const  { return "Ask"; }
	virtual Action* createAction() const  { return new ActionAsk(); }
};
#endif
