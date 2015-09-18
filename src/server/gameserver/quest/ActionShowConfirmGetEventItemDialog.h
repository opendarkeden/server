//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionShowConfirmGetEventItemDialog.h
// Written By  : 
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG_H__
#define __ACTION_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"


//////////////////////////////////////////////////////////////////////////////
// class ActionShowConfirmGetEventItemDialog;
//////////////////////////////////////////////////////////////////////////////

class ActionShowConfirmGetEventItemDialog : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

private:
	string m_Type;
};

//////////////////////////////////////////////////////////////////////////////
// class ActionShowConfirmGetEventItemDialogFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionShowConfirmGetEventItemDialogFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const throw() { return Action::ACTION_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG; }
	virtual string getActionName() const throw() { return "ShowConfirmGetEventItemDialog"; }
    virtual Action* createAction() const throw() { return new ActionShowConfirmGetEventItemDialog(); }
};

#endif

