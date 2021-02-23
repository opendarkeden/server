////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanEnterLevelWarZone.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __CAN_ENTER_LEVEL_WAR_ZONE_H__
#define __CAN_ENTER_LEVEL_WAR_ZONE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterLevelWarZone;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterLevelWarZone : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_CAN_ENTER_LEVEL_WAR_ZONE; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterLevelWarZoneFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterLevelWarZoneFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_CAN_ENTER_LEVEL_WAR_ZONE; }
    virtual Condition* createCondition() const throw() { return new ConditionCanEnterLevelWarZone(); }
    virtual string getConditionName() const throw() { return "CanEnterLevelWarZone"; }
};

#endif
