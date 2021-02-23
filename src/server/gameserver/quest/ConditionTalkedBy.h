//////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionTalkedBy.h
// Written By  : 
// Description :
// NPC가 PC로부터 대화를 받았을 경우, 특별히 이 컨디션이 참이 아닐 가능성은 없다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __TALKED_BY_H__
#define __TALKED_BY_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionTalkedBy;
//////////////////////////////////////////////////////////////////////////////

class ConditionTalkedBy : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_TALKED_BY; }

	virtual bool isPassive() const throw() { return true; }

	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw() 
	{ 
		return pNPC != NULL && pNPC->isNPC() && pPC != NULL && pPC->isPC(); 
	}

	virtual void read(PropertyBuffer & propertyBuffer) throw(Error) { }

	virtual string toString() const throw() { return "ConditionTalkedBy"; }

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionTalkedByFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionTalkedByFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_TALKED_BY; }
    virtual Condition* createCondition() const throw() { return new ConditionTalkedBy(); }
    virtual string getConditionName() const throw() { return "TalkedBy"; }
};

#endif
