////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanEnterPayZone.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __CAN_ENTER_PAY_ZONE_H__
#define __CAN_ENTER_PAY_ZONE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterPayZone;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterPayZone : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_CAN_ENTER_PAY_ZONE; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterPayZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterPayZoneFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_CAN_ENTER_PAY_ZONE; }
    virtual Condition* createCondition() const throw() { return new ConditionCanEnterPayZone(); }
    virtual string getConditionName() const throw() { return "CanEnterPayZone"; }
};

#endif
