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
	virtual ConditionType_t getConditionType() const  { return CONDITION_CAN_PET_QUEST; }
	virtual bool isPassive() const  { return true; }
	virtual bool isSatisfied(Creature* pNPC, Creature* pPC = NULL, void* pParam = NULL) const ;
	virtual void read(PropertyBuffer & propertyBuffer) ;
	virtual string toString() const ;

public:

};

//////////////////////////////////////////////////////////////////////////////
// class ConditionCanPetQuestFactory;
//////////////////////////////////////////////////////////////////////////////

class ConditionCanPetQuestFactory : public ConditionFactory 
{
public:
    virtual ConditionType_t getConditionType() const  { return Condition::CONDITION_CAN_PET_QUEST; }
    virtual Condition* createCondition() const  { return new ConditionCanPetQuest(); }
    virtual string getConditionName() const  { return "CanPetQuest"; }
};

#endif
