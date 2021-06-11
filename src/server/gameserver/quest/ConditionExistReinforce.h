////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionExistReinforce.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __EXIST_REINFORCE_H__
#define __EXIST_REINFORCE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionExistReinforce;
//////////////////////////////////////////////////////////////////////////////

class ConditionExistReinforce : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const  { return CONDITION_EXIST_REINFORCE; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual string toString() const ;

public:

private:
	ZoneID_t	m_ZoneID;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionExistReinforceFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionExistReinforceFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_EXIST_REINFORCE; }
    virtual Condition* createCondition() const  { return new ConditionExistReinforce(); }
    virtual string getConditionName() const  { return "ExistReinforce"; }
};

#endif
