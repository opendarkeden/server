////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionRaceComp.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __RACE_COMP_H__
#define __RACE_COMP_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionRaceComp;
//////////////////////////////////////////////////////////////////////////////

class ConditionRaceComp : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const  { return CONDITION_RACE_COMP; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual string toString() const ;

private:
	Creature::CreatureClass m_CClass; // 크리쳐 클래스

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionRaceCompFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionRaceCompFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_RACE_COMP; }
    virtual Condition* createCondition() const  { return new ConditionRaceComp(); }
    virtual string getConditionName() const  { return "RaceComp"; }
};

#endif
