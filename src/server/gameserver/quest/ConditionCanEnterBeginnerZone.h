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
	virtual ConditionType_t getConditionType() const  { return CONDITION_CAN_ENTER_BEGINNER_ZONE; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual string toString() const ;

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterBeginnerZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterBeginnerZoneFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_CAN_ENTER_BEGINNER_ZONE; }
    virtual Condition* createCondition() const  { return new ConditionCanEnterBeginnerZone(); }
    virtual string getConditionName() const  { return "CanEnterBeginnerZone"; }
};

#endif
