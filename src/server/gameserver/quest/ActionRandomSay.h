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
	virtual ActionType_t getActionType() const  { return ACTION_RANDOM_SAY; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

public:
	ScriptID_t getStartScriptID() const  { return m_StartScriptID; }
	void setStartScriptID(ScriptID_t scriptID)  { m_StartScriptID = scriptID; }

	ScriptID_t getEndScriptID() const  { return m_EndScriptID; }
	void setEndScriptID(ScriptID_t scriptID)  { m_EndScriptID = scriptID; }

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
    virtual ActionType_t getActionType() const  { return Action::ACTION_RANDOM_SAY; }
	virtual string getActionName() const  { return "RandomSay"; }
    virtual Action* createAction() const  { return new ActionRandomSay(); }

};

#endif
