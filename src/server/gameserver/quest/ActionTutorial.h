//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionTutorial.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_TUTORIAL_H__
#define __ACTION_TUTORIAL_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionTutorial
//////////////////////////////////////////////////////////////////////////////

class ActionTutorial : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_TUTORIAL; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
	string getInterface(void) const throw() { return m_Interface; }
	void setInterface(string interface) throw() { m_Interface = interface; }

private:
	string m_Interface;

};


//////////////////////////////////////////////////////////////////////////////
// class ActionTutorialFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionTutorialFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_TUTORIAL; }
	virtual string getActionName() const throw() { return "Tutorial"; }
	virtual Action* createAction() const throw() { return new ActionTutorial(); }
};
#endif
