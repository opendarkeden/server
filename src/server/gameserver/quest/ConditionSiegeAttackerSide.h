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
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_SIEGE_ATTACKER_SIDE; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionSiegeAttackerSideFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionSiegeAttackerSideFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_SIEGE_ATTACKER_SIDE; }
    virtual Condition* createCondition() const throw() { return new ConditionSiegeAttackerSide(); }
    virtual string getConditionName() const throw() { return "SiegeAttackerSide"; }
};

#endif
