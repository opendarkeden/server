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
	virtual ActionType_t getActionType() const  { return ACTION_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

private:
	string m_Type;
};

//////////////////////////////////////////////////////////////////////////////
// class ActionShowConfirmGetEventItemDialogFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionShowConfirmGetEventItemDialogFactory : public ActionFactory 
{
public:
    virtual ActionType_t getActionType() const  { return Action::ACTION_SHOW_CONFIRM_GET_EVENT_ITEM_DIALOG; }
	virtual string getActionName() const  { return "ShowConfirmGetEventItemDialog"; }
    virtual Action* createAction() const  { return new ActionShowConfirmGetEventItemDialog(); }
};

#endif

