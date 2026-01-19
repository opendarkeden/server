//////////////////////////////////////////////////////////////////////////////
// Filename    : ActionRepair.h
// Written By  :
// Description :
//////////////////////////////////////////////////////////////////////////////

#ifndef __ACTION_REPAIR_H__
#define __ACTION_REPAIR_H__

#include "Action.h"
#include "ActionFactory.h"
#include "Exception.h"
#include "Types.h"

//////////////////////////////////////////////////////////////////////////////
// class ActionRepair;
//////////////////////////////////////////////////////////////////////////////

class ActionRepair : public Action {
public:
    virtual ActionType_t getActionType() const {
        return ACTION_REPAIR;
    }
    virtual void read(PropertyBuffer& propertyBuffer);
    virtual void execute(Creature* pCreature1, Creature* pCreature2 = NULL);
    virtual string toString() const;
};


//////////////////////////////////////////////////////////////////////////////
// class ActionRepairFactory;
//////////////////////////////////////////////////////////////////////////////

class ActionRepairFactory : public ActionFactory {
public:
    virtual ActionType_t getActionType() const {
        return Action::ACTION_REPAIR;
    }
    virtual string getActionName() const {
        return "Repair";
    }
    virtual Action* createAction() const {
        return new ActionRepair();
    }
};

#endif
