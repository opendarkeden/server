//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionSayDynamic.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SAY_DYNAMIC_H__
#define __ACTION_SAY_DYNAMIC_H__

#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionSayDynamic
//////////////////////////////////////////////////////////////////////////////

class ActionSayDynamic : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_SAY_DYNAMIC; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	ScriptID_t getScriptID() const throw() { return m_ScriptID; }
	void setScriptID(ScriptID_t scriptID) throw() { m_ScriptID = scriptID; }

private:
	ScriptID_t m_ScriptID;   // 말할 대사 아이디
};


//////////////////////////////////////////////////////////////////////////////
// class ActionSayDynamicFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionSayDynamicFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_SAY_DYNAMIC; }
	virtual string getActionName() const throw() { return "SayDynamic"; }
	virtual Action* createAction() const throw() { return new ActionSayDynamic(); }
};

#endif
