//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSay.h
// Written By  : 
// Description :
// Creature가 주어진 대사를 말한다. 이 대사는 크리처의 머리 위의 말풍선으로
// 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SAY_H__
#define __ACTION_SAY_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSay;
//////////////////////////////////////////////////////////////////////////////

class ActionSay : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_SAY; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	ScriptID_t getScriptID() const throw() { return m_ScriptID; }
	void setScriptID(ScriptID_t scriptID) throw() { m_ScriptID = scriptID; }

private:
	ScriptID_t m_ScriptID; // 말할 대사 아이디
};

//////////////////////////////////////////////////////////////////////////////
// class ActionSayFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSayFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const throw() { return Action::ACTION_SAY; }
	virtual string getActionName() const throw() { return "Say"; }
    virtual Action* createAction() const throw() { return new ActionSay(); }
};

#endif
