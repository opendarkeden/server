//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRedistributeAttr.h
// Written By  : excel96
// Description : 
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_REDISTRIBUTE_ATTR_H__
#define __ACTION_REDISTRIBUTE_ATTR_H__

#include "Types.h"
#include "Exception.h"
#include "Action.h"
#include "ActionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionRedistributeAttr
//////////////////////////////////////////////////////////////////////////////

class ActionRedistributeAttr : public Action 
{
public:
	virtual ActionType_t getActionType() const throw() { return ACTION_REDISTRIBUTE_ATTR; }
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) throw(Error);
	virtual string toString() const throw();

private:
	int m_AttrType;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionRedistributeAttrFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionRedistributeAttrFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const throw() { return Action::ACTION_REDISTRIBUTE_ATTR; }
	virtual string getActionName() const throw() { return "RedistributeAttr"; }
	virtual Action* createAction() const throw() { return new ActionRedistributeAttr(); }
};

#endif
