////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionSiegeDefenderSide.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __SIEGE_DEFENDER_SIDE_H__
#define __SIEGE_DEFENDER_SIDE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionSiegeDefenderSide;
//////////////////////////////////////////////////////////////////////////////

class ConditionSiegeDefenderSide : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_SIEGE_DEFENDER_SIDE; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionSiegeDefenderSideFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionSiegeDefenderSideFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_SIEGE_DEFENDER_SIDE; }
    virtual Condition* createCondition() const throw() { return new ConditionSiegeDefenderSide(); }
    virtual string getConditionName() const throw() { return "SiegeDefenderSide"; }
};

#endif
