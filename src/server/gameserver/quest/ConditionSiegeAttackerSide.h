////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionSiegeAttackerSide.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __SIEGE_ATTACKER_SIDE_H__
#define __SIEGE_ATTACKER_SIDE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionSiegeAttackerSide;
//////////////////////////////////////////////////////////////////////////////

class ConditionSiegeAttackerSide : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const  { return CONDITION_SIEGE_ATTACKER_SIDE; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual string toString() const ;

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionSiegeAttackerSideFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionSiegeAttackerSideFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_SIEGE_ATTACKER_SIDE; }
    virtual Condition* createCondition() const  { return new ConditionSiegeAttackerSide(); }
    virtual string getConditionName() const  { return "SiegeAttackerSide"; }
};

#endif
