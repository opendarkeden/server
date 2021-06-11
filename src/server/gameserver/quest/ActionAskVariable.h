//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionAskVariable.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_ASK_VARIABLE_H__
#define __ACTION_ASK_VARIABLE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionAskVariable
//////////////////////////////////////////////////////////////////////////////

class VariableBuffer;

class ActionAskVariable : public Action 
{
public:
	ActionAskVariable() : m_pVariableBuffer(NULL) {}

public:
	virtual ActionType_t getActionType() const  { return ACTION_ASK_VARIABLE; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public:
	ScriptID_t getScriptID() const  { return m_ScriptID; }
	void setScriptID(ScriptID_t scriptID)  { m_ScriptID = scriptID; }

private:
	ScriptID_t m_ScriptID;   // 말할 대사 아이디
	VariableBuffer* m_pVariableBuffer;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionAskVariableFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionAskVariableFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_ASK_VARIABLE; }
	virtual string getActionName() const  { return "AskVariable"; }
	virtual Action* createAction() const  { return new ActionAskVariable(); }
};
#endif
