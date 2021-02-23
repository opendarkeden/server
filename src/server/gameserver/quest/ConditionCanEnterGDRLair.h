////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanEnterGDRLair.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __CAN_ENTER_GDR_LAIR_H__
#define __CAN_ENTER_GDR_LAIR_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterGDRLair;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterGDRLair : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_CAN_ENTER_GDR_LAIR; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterGDRLairFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterGDRLairFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_CAN_ENTER_GDR_LAIR; }
    virtual Condition* createCondition() const throw() { return new ConditionCanEnterGDRLair(); }
    virtual string getConditionName() const throw() { return "CanEnterGDRLair"; }
};

#endif
