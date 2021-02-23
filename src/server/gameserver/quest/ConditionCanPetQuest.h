////////////////////////////////////////////////////////////////////////////////
// Filename    : ConditionCanPetQuest.h
// Written By  : 
// Description :
////////////////////////////////////////////////////////////////////////////////

#ifndef __CAN_PET_QUEST_H__
#define __CAN_PET_QUEST_H__

#include "Condition.h"
#include "ConditionFactory.h"
#include "Creature.h"

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanPetQuest;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanPetQuest : public Condition 
{
public:
	virtual ConditionType_t getConditionType() const throw() { return CONDITION_CAN_PET_QUEST; }
	virtual bool isPassive() const throw() { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const throw();
	virtual void read(PropertyBuffer & propertyBuffer) throw(Error);
	virtual string toString() const throw();

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanPetQuestFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanPetQuestFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const throw() { return Condition::CONDITION_CAN_PET_QUEST; }
    virtual Condition* createCondition() const throw() { return new ConditionCanPetQuest(); }
    virtual string getConditionName() const throw() { return "CanPetQuest"; }
};

#endif
