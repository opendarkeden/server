////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionEveryTime.h
// Written By  : 
// Description :
// 매 주기마다 특정 액션을 실행하도록 한다.
////////////////////////////////////////////////////////////////////////////////

#ifndef __EVERY_TIME_H__
#define __EVERY_TIME_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionEveryTime;
//////////////////////////////////////////////////////////////////////////////

class ConditionEveryTime : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const  { return CONDITION_EVERY_TIME; }
	virtual bool isActive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual string toString() const ;

public:
	Turn_t getTurn() const  { return m_Turn; }
	void setTurn(Turn_t turn)  { m_Turn = turn; }

	Timeval & getNextTurn()  { return m_NextTurn; }
	const Timeval & getNextTurn() const  { return m_NextTurn; }
	void setNextTurn(Timeval tv)  { m_NextTurn = tv; }	

private:
	Turn_t m_Turn;

	// 다음 실행시간
	// isSatisfied() 가 const method 이지만, 내부에서 값을 변경해야
	// 하기 때문에 mutable 로 설정했다.
	mutable Timeval m_NextTurn;	

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionEveryTimeFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionEveryTimeFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_EVERY_TIME; }
    virtual Condition* createCondition() const  { return new ConditionEveryTime(); }
    virtual string getConditionName() const  { return "EveryTime"; }
};

#endif
