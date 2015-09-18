////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionSameClan.h
// Written By  : excel96
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __SAME_CLAN_H__
#define __SAME_CLAN_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionSameClan;
//////////////////////////////////////////////////////////////////////////////

class ConditionSameClan : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_SAME_CLAN; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionSameClanFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionSameClanFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_SAME_CLAN; }
    virtual Condition* createCondition() const throw() { return new ConditionSameClan(); }
    virtual string getConditionName() const throw() { return "SameClan"; }
};

#endif
