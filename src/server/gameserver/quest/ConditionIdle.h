//////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionIdle.h
// Written By  : 
// Description : 
// NPC 또는 몬스터가 평소에 하는 행위를 지정할 때 사용된다.
// 아무런 사건이 없을 경우, 관련된 액션이 실행된다. 
// 이 컨디션은 트리거의 가장 끝에 배치되어야 한다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __IDLE_H__
#define __IDLE_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionIdle;
//////////////////////////////////////////////////////////////////////////////

class ConditionIdle : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_IDLE; }

	virtual bool isActive() const throw() { return true; }

	virtual bool isSatisfied(Creature* pCreature1, Creature* pCreature2 = NULL, void* pParam = NULL) const throw() 
	{ 
		return pCreature1 != NULL && !pCreature1->isPC() && pCreature2 == NULL;
	}

	virtual void read(PropertyBuffer & propertyBuffer) throw(Error) {}

	virtual string toString() const throw() { return "ConditionIdle"; }

};


////////////////////////////////////////////////////////////////////////////////
// class ConditionIdleFactory;
////////////////////////////////////////////////////////////////////////////////

class ConditionIdleFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_IDLE; }
    virtual Condition* createCondition() const throw() { return new ConditionIdle(); }
    virtual string getConditionName() const throw() { return "Idle"; }
};

#endif
