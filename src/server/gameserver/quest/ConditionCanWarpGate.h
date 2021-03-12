////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanWarpGate.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __CAN_WARP_GATE_H__
#define __CAN_WARP_GATE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanWarpGate;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanWarpGate : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const  { return CONDITION_CAN_WARP_GATE; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual string toString() const ;

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanWarpGateFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanWarpGateFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_CAN_WARP_GATE; }
    virtual Condition* createCondition() const  { return new ConditionCanWarpGate(); }
    virtual string getConditionName() const  { return "CanWarpGate"; }
};

#endif
