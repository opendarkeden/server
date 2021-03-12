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
	virtual ConditionType_t getConditionType() const  { return CONDITION_CAN_ENTER_GDR_LAIR; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual string toString() const ;

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanEnterGDRLairFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanEnterGDRLairFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_CAN_ENTER_GDR_LAIR; }
    virtual Condition* createCondition() const  { return new ConditionCanEnterGDRLair(); }
    virtual string getConditionName() const  { return "CanEnterGDRLair"; }
};

#endif
