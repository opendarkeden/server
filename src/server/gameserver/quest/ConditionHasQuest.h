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
	ConditionHasQuest() ;
	virtual ~ConditionHasQuest() ;

public:
	virtual ConditionType_t getConditionType() const  { return CONDITION_HAS_QUEST; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual string toString() const ;

private:
	QuestID_t m_QuestID;
};

//////////////////////////////////////////////////////////////////////////////
// class ConditionHasQuestFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionHasQuestFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_HAS_QUEST; }
    virtual Condition* createCondition() const  { return new ConditionHasQuest(); }
    virtual string getConditionName() const  { return "HasQuest"; }
};

#endif
