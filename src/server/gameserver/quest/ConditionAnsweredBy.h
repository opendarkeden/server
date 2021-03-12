//////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionAnsweredBy.h
// Written By  : 
// Description :
// PC가 NPC의 질문에 대답했을 경우에 발생하는 컨디션이다.
//////////////////////////////////////////////////////////////////////////////

#ifndef __ANSWEREDBY_H__
#define __ANSWEREDBY_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionAnsweredBy;
//////////////////////////////////////////////////////////////////////////////

class ConditionAnsweredBy : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const  { return CONDITION_ANSWERED_BY; }

	virtual bool isActive() const  { return false;}
	virtual bool isPassive() const  { return true; } // 패킷에 반응을 하니까... passive condition이다.
	virtual bool isNeutral() const  { return false; }

	virtual bool isSatisfied(Creature* pCreature1, Creature* pCreature2 = NULL, void* pParam = NULL) const ;

	virtual void read(PropertyBuffer & propertyBuffer) ;

	virtual string toString() const ;

public :
	ScriptID_t getScriptID(void) const { return m_ScriptID;}
	AnswerID_t getAnswerID(void) const { return m_AnswerID;}
	
	void setScriptID(ScriptID_t scriptID) { m_ScriptID = scriptID;}
	void setAnswerID(ScriptID_t answerID) { m_AnswerID = answerID;}

private :
	ScriptID_t m_ScriptID;
	AnswerID_t m_AnswerID;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionAnsweredByFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionAnsweredByFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_ANSWERED_BY; }
    virtual Condition* createCondition() const  { return new ConditionAnsweredBy(); }
    virtual string getConditionName() const  { return "AnsweredBy"; }
};

#endif
