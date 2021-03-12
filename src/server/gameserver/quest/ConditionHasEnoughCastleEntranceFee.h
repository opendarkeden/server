////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionHasEnoughCastleEntranceFee.h
// Written By  : 
// Description : 사용되지 않음.
////////////////////////////////////////////////////////////////////////////////

#ifndef __HAS_ENOUGH_CASTLE_ENTRANCE_FEE_H__
#define __HAS_ENOUGH_CASTLE_ENTRANCE_FEE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasEnoughCastleEntranceFee;
//////////////////////////////////////////////////////////////////////////////

class ConditionHasEnoughCastleEntranceFee : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const  { return CONDITION_HAS_ENOUGH_CASTLE_ENTRANCE_FEE; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual string toString() const ;

public:
	ZoneID_t m_ZoneID;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasEnoughCastleEntranceFeeFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionHasEnoughCastleEntranceFeeFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_HAS_ENOUGH_CASTLE_ENTRANCE_FEE; }
    virtual Condition* createCondition() const  { return new ConditionHasEnoughCastleEntranceFee(); }
    virtual string getConditionName() const  { return "HasEnoughCastleEntranceFee"; }
};

#endif
