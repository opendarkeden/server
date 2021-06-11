////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionHasEnoughFamilyCoin.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __CONDITION_HAS_ENOUGH_FAMILY_COIN_H__
#define __CONDITION_HAS_ENOUGH_FAMILY_COIN_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasEnoughFamilyCoin;
//////////////////////////////////////////////////////////////////////////////

class ConditionHasEnoughFamilyCoin : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const  { return CONDITION_HAS_ENOUGH_FAMILY_COIN; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual string toString() const ;
private:
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasEnoughFamilyCoinFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionHasEnoughFamilyCoinFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_HAS_ENOUGH_FAMILY_COIN; }
    virtual Condition* createCondition() const  { return new ConditionHasEnoughFamilyCoin(); }
    virtual string getConditionName() const  { return "HasEnoughFamilyCoin"; }
};

#endif
