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
	virtual ActionType_t getActionType() const  { return ACTION_REDISTRIBUTE_ATTR; }
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL) ;
	virtual string toString() const ;

private:
	int m_AttrType;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionRedistributeAttrFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionRedistributeAttrFactory : public ActionFactory 
{
public:
	virtual ActionType_t getActionType() const  { return Action::ACTION_REDISTRIBUTE_ATTR; }
	virtual string getActionName() const  { return "RedistributeAttr"; }
	virtual Action* createAction() const  { return new ActionRedistributeAttr(); }
};

#endif
