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
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_RACE_COMP; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();

private:
	Creature::CreatureClass m_CClass; // 크리쳐 클래스

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionRaceCompFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionRaceCompFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_RACE_COMP; }
    virtual Condition* createCondition() const throw() { return new ConditionRaceComp(); }
    virtual string getConditionName() const throw() { return "RaceComp"; }
};

#endif
