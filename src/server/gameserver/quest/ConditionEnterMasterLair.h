////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionEnterMasterLair.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __ENTER_MASTER_LAIR_H__
#define __ENTER_MASTER_LAIR_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionEnterMasterLair;
//////////////////////////////////////////////////////////////////////////////

class ConditionEnterMasterLair : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_ENTER_MASTER_LAIR; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);

	ZoneID_t getTargetZoneID() const	{ return m_TargetZoneID; }

	virtual string toString() const throw();

public:
	ZoneID_t 	m_TargetZoneID;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionEnterMasterLairFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionEnterMasterLairFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_ENTER_MASTER_LAIR; }
    virtual Condition* createCondition() const throw() { return new ConditionEnterMasterLair(); }
    virtual string getConditionName() const throw() { return "EnterMasterLair"; }
};

#endif
