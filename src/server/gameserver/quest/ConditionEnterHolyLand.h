////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionEnterHolyLand.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __ENTER_HOLY_LAND_H__
#define __ENTER_HOLY_LAND_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionEnterHolyLand;
//////////////////////////////////////////////////////////////////////////////

class ConditionEnterHolyLand : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const  { return CONDITION_ENTER_HOLY_LAND; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;

	ZoneID_t getTargetZoneID() const	{ return m_TargetZoneID; }

	virtual string toString() const ;

public:
	ZoneID_t 	m_TargetZoneID;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionEnterHolyLandFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionEnterHolyLandFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_ENTER_HOLY_LAND; }
    virtual Condition* createCondition() const  { return new ConditionEnterHolyLand(); }
    virtual string getConditionName() const  { return "EnterHolyLand"; }
};

#endif
