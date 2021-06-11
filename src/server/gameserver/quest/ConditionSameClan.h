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
	virtual ConditionType_t getConditionType() const  { return CONDITION_SAME_CLAN; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual string toString() const ;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionSameClanFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionSameClanFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_SAME_CLAN; }
    virtual Condition* createCondition() const  { return new ConditionSameClan(); }
    virtual string getConditionName() const  { return "SameClan"; }
};

#endif
