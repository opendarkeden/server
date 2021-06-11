////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionEnterCastle.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __ENTER_CASTLE_H__
#define __ENTER_CASTLE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionEnterCastle;
//////////////////////////////////////////////////////////////////////////////

class ConditionEnterCastle : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const  { return CONDITION_ENTER_CASTLE; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;

	ZoneID_t getTargetZoneID() const	{ return m_TargetZoneID; }

	virtual string toString() const ;

public:
	ZoneID_t 	m_TargetZoneID;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionEnterCastleFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionEnterCastleFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_ENTER_CASTLE; }
    virtual Condition* createCondition() const  { return new ConditionEnterCastle(); }
    virtual string getConditionName() const  { return "EnterCastle"; }
};

#endif
