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
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_EXIST_REINFORCE; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();

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
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_EXIST_REINFORCE; }
    virtual Condition* createCondition() const throw() { return new ConditionExistReinforce(); }
    virtual string getConditionName() const throw() { return "ExistReinforce"; }
};

#endif
