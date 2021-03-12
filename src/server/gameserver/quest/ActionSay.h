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
	virtual ActionType_t getActionType() const  { return ACTION_SAY; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public:
	ScriptID_t getScriptID() const  { return m_ScriptID; }
	void setScriptID(ScriptID_t scriptID)  { m_ScriptID = scriptID; }

private:
	ScriptID_t m_ScriptID; // 말할 대사 아이디
};

//////////////////////////////////////////////////////////////////////////////
// class ActionSayFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSayFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const  { return Action::ACTION_SAY; }
	virtual string getActionName() const  { return "Say"; }
    virtual Action* createAction() const  { return new ActionSay(); }
};

#endif
