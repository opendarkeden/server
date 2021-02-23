//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRandomSay.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_RANDOM_SAY_H__
#define __ACTION_RANDOM_SAY_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionRandomSay;
//////////////////////////////////////////////////////////////////////////////

class ActionRandomSay : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_RANDOM_SAY; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	ScriptID_t getStartScriptID() const throw() { return m_StartScriptID; }
	void setStartScriptID(ScriptID_t scriptID) throw() { m_StartScriptID = scriptID; }

	ScriptID_t getEndScriptID() const throw() { return m_EndScriptID; }
	void setEndScriptID(ScriptID_t scriptID) throw() { m_EndScriptID = scriptID; }

private:
	ScriptID_t m_StartScriptID; // 말할 대사 아이디 시작 ID
	ScriptID_t m_EndScriptID;   // 말할 대사 아이디 끝 ID
};


////////////////////////////////////////////////////////////////////////////////
// class ActionRandomSayFactory;
////////////////////////////////////////////////////////////////////////////////

class ActionRandomSayFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const throw() { return Action::ACTION_RANDOM_SAY; }
	virtual string getActionName() const throw() { return "RandomSay"; }
    virtual Action* createAction() const throw() { return new ActionRandomSay(); }

};

#endif
