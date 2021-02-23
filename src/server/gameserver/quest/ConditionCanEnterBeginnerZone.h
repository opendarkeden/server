////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanEnterBeginnerZone.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __CAN_ENTER_BEGINNER_ZONE_H__
#define __CAN_ENTER_BEGINNER_ZONE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterBeginnerZone;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterBeginnerZone : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_CAN_ENTER_BEGINNER_ZONE; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterBeginnerZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterBeginnerZoneFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_CAN_ENTER_BEGINNER_ZONE; }
    virtual Condition* createCondition() const throw() { return new ConditionCanEnterBeginnerZone(); }
    virtual string getConditionName() const throw() { return "CanEnterBeginnerZone"; }
};

#endif
