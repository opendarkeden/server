////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionHasQuest.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __HAS_QUEST_H__
#define __HAS_QUEST_H__

#include "Condition.h"
#include "ConditionFactory.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasQuest;
//////////////////////////////////////////////////////////////////////////////

class ConditionHasQuest : public Condition 
{
public:
	ConditionHasQuest() throw();
	virtual ~ConditionHasQuest() throw();

public:
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_HAS_QUEST; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();

private:
	QuestID_t m_QuestID;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasQuestFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionHasQuestFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_HAS_QUEST; }
    virtual Condition* createCondition() const throw() { return new ConditionHasQuest(); }
    virtual string getConditionName() const throw() { return "HasQuest"; }
};

#endif
