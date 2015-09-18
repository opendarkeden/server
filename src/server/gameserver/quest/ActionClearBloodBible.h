//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionClearBloodBible.h
// Written By  : excel96
// Description : 
// Creature가 PC에게 질문을 던진다. 이 대사는 NPC 대화창에 출력된다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_CLEAR_BLOOD_BIBLE_H__
#define __ACTION_CLEAR_BLOOD_BIBLE_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionClearBloodBible
//////////////////////////////////////////////////////////////////////////////

class ActionClearBloodBible : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_CLEAR_BLOOD_BIBLE; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

public:
private:
};


//////////////////////////////////////////////////////////////////////////////
// class ActionClearBloodBibleFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionClearBloodBibleFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_CLEAR_BLOOD_BIBLE; }
	virtual string getActionName() const throw() { return "ClearBloodBible"; }
	virtual Action* createAction() const throw() { return new ActionClearBloodBible(); }
};
#endif
